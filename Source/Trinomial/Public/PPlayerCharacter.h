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

public:
	APPlayerCharacter();

protected:
	/** First person camera */
	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent* FirstPersonCameraComponent;

	void Tick(float DeltaTime);
};
