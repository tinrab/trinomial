#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacter.h"
#include "PPlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class TRINOMIAL_API APPlayerCharacter : public APCharacter
{
	GENERATED_BODY()

	APPlayerCharacter();

	/** First person camera */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCameraComponent;
};
