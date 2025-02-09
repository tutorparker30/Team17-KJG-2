#include "JGameMode.h"
#include "JPawn.h"
#include "JPlayerController.h"

AJGameMode::AJGameMode()
{
	DefaultPawnClass = AJPawn::StaticClass();
	PlayerControllerClass = AJPlayerController::StaticClass();
}

