#include "JPlayerController.h"
#include "EnhancedInputSubsystems.h"

AJPlayerController::AJPlayerController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{
}

void AJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}