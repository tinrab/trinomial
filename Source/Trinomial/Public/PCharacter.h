#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class UPCharacterMovementComponent;

UCLASS()
class TRINOMIAL_API APCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* Set a pending launch velocity on the Character. This velocity will be processed on the next
	* CharacterMovementComponent tick, and will set it to the "falling" state. Triggers the OnLaunched event.
	* @note This version has a different behavior for the boolean parameters that take into account the Character's orientation.
	* @param LaunchVelocity is the velocity to impart to the Character.
	* @param bHorizontalOverride if true replace the horizontal part of the Character's velocity instead of adding to it.
	* @param bVerticalOverride if true replace the vertical part of the Character's velocity instead of adding to it.
	*/
	void LaunchCharacterRotated(FVector LaunchVelocity, bool bHorizontalOverride, bool bVerticalOverride);

	/**
	* Add horizontal movement in character's local space.
	* @param Amount to move
	*/
	void AddHorizontalMovement(float Amount);

	/**
	* Add vertical movement in character's local space.
	* @param Amount to move
	*/
	void AddVerticalMovement(float Amount);

	/**
	* Return custom movement component.
	*/
	FORCEINLINE UPCharacterMovementComponent* GetCustomCharacterMovementComponent() const { return CharacterMovementComponent; };

	void Tick(float DeltaTime) override;

	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser) override;
	virtual FVector GetPawnViewLocation() const override;
	virtual void PostNetReceiveLocationAndRotation() override;

protected:
	UPCharacterMovementComponent* CharacterMovementComponent;
};
