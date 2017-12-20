#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPlayerController.generated.h"

UCLASS()
class TRINOMIAL_API APPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Setup input handlers */
	virtual void SetupInputComponent() override;

	/** Handles horizontal movement input */
	UFUNCTION()
	void MoveHorizontal(float AxisValue);

	/** Handles vertical movement input */
	UFUNCTION()
	void MoveVertical(float AxisValue);

	/** Handles horizontal look input */
	UFUNCTION()
	void LookHorizontal(float AxisValue);

	/** Handles vertical look input */
	UFUNCTION()
	void LookVertical(float AxisValue);

	/** Begin the jump */
	UFUNCTION()
	void BeginJump();

	/** End the jump */
	UFUNCTION()
	void EndJump();
};
