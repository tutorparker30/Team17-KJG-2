#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PAWNCLASS_API AJPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	virtual void BeginPlay() override;

	
};
