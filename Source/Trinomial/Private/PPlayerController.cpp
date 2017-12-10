#include "PPlayerController.h"
#include "GameFramework/Character.h"

void APPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent != nullptr)
	{
		// Setup axes
		InputComponent->BindAxis("MoveHorizontal", this, &APPlayerController::MoveHorizontal);
		InputComponent->BindAxis("MoveVertical", this, &APPlayerController::MoveVertical);
		InputComponent->BindAxis("LookHorizontal", this, &APPlayerController::LookHorizontal);
		InputComponent->BindAxis("LookVertical", this, &APPlayerController::LookVertical);

		// Setup actions
		InputComponent->BindAction("Jump", IE_Pressed, this, &APPlayerController::BeginJump);
		InputComponent->BindAction("Jump", IE_Released, this, &APPlayerController::BeginJump);
	}
}

void APPlayerController::MoveHorizontal(float AxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	ACharacter* Character = GetCharacter();
	if (Character != nullptr)
	{
		Character->AddMovementInput(Direction, AxisValue);
	}
}

void APPlayerController::MoveVertical(float AxisValue)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	ACharacter* Character = GetCharacter();

	if (Character != nullptr)
	{
		Character->AddMovementInput(Direction, AxisValue);
	}
}

void APPlayerController::LookHorizontal(float AxisValue)
{
	ACharacter* Character = GetCharacter();
	if (Character != nullptr)
	{
		Character->AddControllerYawInput(AxisValue);
	}
}

void APPlayerController::LookVertical(float AxisValue)
{
	ACharacter* Character = GetCharacter();
	if (Character != nullptr)
	{
		Character->AddControllerPitchInput(AxisValue);
	}
}

void APPlayerController::BeginJump()
{
	ACharacter* Character = GetCharacter();
	if (Character != nullptr)
	{
		Character->Jump();
	}
}

void APPlayerController::EndJump()
{
	ACharacter* Character = GetCharacter();
	if (Character != nullptr)
	{
		Character->StopJumping();
	}
}
