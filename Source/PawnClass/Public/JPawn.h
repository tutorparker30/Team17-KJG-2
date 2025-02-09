#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "JPawn.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class PAWNCLASS_API AJPawn : public APawn
{
	GENERATED_BODY()

public:

	AJPawn();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UArrowComponent* ArrowComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookUpRate = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinPitch = -80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxPitch = 80.f;

	FVector2D LookInput;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	
	UFUNCTION()
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void StopLook(const FInputActionValue& value);

};
