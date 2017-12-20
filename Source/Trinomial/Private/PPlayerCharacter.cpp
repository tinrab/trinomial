#include "PPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

APPlayerCharacter::APPlayerCharacter()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
}

void APPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	FRotator Rotation = GetActorRotation();
	const FRotator ControlRotation = GetControlRotation();
	Rotation.SetComponentForAxis(EAxis::Z, ControlRotation.GetComponentForAxis(EAxis::Z));
	FirstPersonCameraComponent->SetWorldRotation(Rotation);
	*/

	FRotator Rotation = GetControlRotation();
	Rotation.SetComponentForAxis(EAxis::X, 0.0f);
	FirstPersonCameraComponent->SetRelativeRotation(Rotation);
}
