#include "JPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "JPlayerController.h"

AJPawn::AJPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComp;
	CapsuleComp->SetSimulatePhysics(false);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComp->SetupAttachment(RootComponent);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	LookInput = FVector2D::ZeroVector;

}

void AJPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator CameraRotation = CameraComp->GetComponentRotation();
	const FRotator YawOnlyRotation(0.f, CameraRotation.Yaw, 0.f);

	if (!FMath::IsNearlyZero(LookInput.X))
	{
		const float YawRotation = LookInput.X * TurnRate * DeltaTime;
		AddActorLocalRotation(FRotator(0.f, YawRotation, 0.f));
	}

	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		FRotator CurrentArmRotation = SpringArmComp->GetRelativeRotation();
		float NewPitch = CurrentArmRotation.Pitch - (LookInput.Y * LookUpRate * DeltaTime);
		NewPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);
		CurrentArmRotation.Pitch = NewPitch;
		SpringArmComp->SetRelativeRotation(CurrentArmRotation);
	}
}

void AJPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AJPlayerController* PlayerController = Cast<AJPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AJPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AJPawn::Look
				);

				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Completed,
					this,
					&AJPawn::StopLook
				);
			}
		}
	}
}

void AJPawn::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (MovementVector.IsNearlyZero()) return;

	// 컨트롤러의 회전 값 가져오기
	FRotator ControlRotation = GetControlRotation();

	//카메라 기준의 이동 방향 계산 (Z축 회전값만 사용)
	FVector Forward = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::X);
	FVector Right = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	// 이동 방향을 카메라 기준으로 변환
	FVector Movement = (Forward * MovementVector.X) + (Right * MovementVector.Y);
	Movement.Normalize();

	// 최종 이동 벡터 계산
	FVector FinalMovement = Movement * MoveSpeed * GetWorld()->GetDeltaSeconds();

	// 이동 적용 (충돌 감지 활성화)
	AddActorLocalOffset(FinalMovement, true);

}

void AJPawn::Look(const FInputActionValue& value)
{
	LookInput = value.Get<FVector2D>();
}

void AJPawn::StopLook(const FInputActionValue& value)
{
	LookInput = FVector2D::ZeroVector;
}
