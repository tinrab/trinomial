#include "PCharacter.h"
#include "PCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PGravityManager.h"
#include "DrawDebugHelpers.h"

APCharacter::APCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterMovementComponent = Cast<UPCharacterMovementComponent>(GetMovementComponent());
}

void APCharacter::LaunchCharacterRotated(FVector LaunchVelocity, bool bHorizontalOverride, bool bVerticalOverride)
{
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (CharacterMovement)
	{
		if (!bHorizontalOverride && !bVerticalOverride)
		{
			CharacterMovement->Launch(GetVelocity() + LaunchVelocity);
		} else if (bHorizontalOverride && bVerticalOverride)
		{
			CharacterMovement->Launch(LaunchVelocity);
		} else
		{
			FVector FinalVel;
			const FVector Velocity = GetVelocity();
			const FVector AxisZ = GetActorQuat().GetAxisZ();

			if (bHorizontalOverride)
			{
				FinalVel = FVector::VectorPlaneProject(LaunchVelocity, AxisZ) + AxisZ * (Velocity | AxisZ);
			} else // if (bVerticalOverride)
			{
				FinalVel = FVector::VectorPlaneProject(Velocity, AxisZ) + AxisZ * (LaunchVelocity | AxisZ);
			}

			CharacterMovement->Launch(FinalVel);
		}

		OnLaunched(LaunchVelocity, bHorizontalOverride, bVerticalOverride);
	}
}

void APCharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	const UDamageType* DmgTypeCDO = DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>();
	const float ImpulseScale = DmgTypeCDO->DamageImpulse;

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (ImpulseScale > 3.0f && CharacterMovement != NULL)
	{
		FHitResult HitInfo;
		FVector ImpulseDir;
		DamageEvent.GetBestHitInfo(this, PawnInstigator, HitInfo, ImpulseDir);

		FVector Impulse = ImpulseDir * ImpulseScale;
		const bool bMassIndependentImpulse = !DmgTypeCDO->bScaleMomentumByMass;

		// Limit Z momentum added if already going up faster than jump (to avoid blowing character way up into the sky).
		{
			FVector MassScaledImpulse = Impulse;
			if (!bMassIndependentImpulse && CharacterMovement->Mass > SMALL_NUMBER)
			{
				MassScaledImpulse = MassScaledImpulse / CharacterMovement->Mass;
			}

			const FVector AxisZ = GetActorQuat().GetAxisZ();
			if ((CharacterMovement->Velocity | AxisZ) > GetDefault<UCharacterMovementComponent>(CharacterMovement->GetClass())->JumpZVelocity && (MassScaledImpulse | AxisZ) > 0.0f)
			{
				Impulse = FVector::VectorPlaneProject(Impulse, AxisZ) + AxisZ * ((Impulse | AxisZ) * 0.5f);
			}
		}

		CharacterMovement->AddImpulse(Impulse, bMassIndependentImpulse);
	}
}

FVector APCharacter::GetPawnViewLocation() const
{
	return GetActorLocation() + GetActorQuat().GetAxisZ() * BaseEyeHeight;
}

void APCharacter::PostNetReceiveLocationAndRotation()
{
	// Always consider Location as changed if we were spawned this tick as in that case our replicated Location was set as part of spawning, before PreNetReceive().
	if (ReplicatedMovement.Location == GetActorLocation() && ReplicatedMovement.Rotation == GetActorRotation() && CreationTime != GetWorld()->TimeSeconds)
	{
		return;
	}

	if (Role == ROLE_SimulatedProxy)
	{
		const FVector OldLocation = GetActorLocation();
		const FQuat OldRotation = GetActorQuat();
		const FQuat NewRotation = ReplicatedMovement.Rotation.Quaternion();

		// Correction to make sure pawn doesn't penetrate floor after replication rounding.
		ReplicatedMovement.Location += NewRotation.GetAxisZ() * 0.01f;

		SetActorLocationAndRotation(ReplicatedMovement.Location, ReplicatedMovement.Rotation, /*bSweep=*/ false);

		INetworkPredictionInterface* PredictionInterface = Cast<INetworkPredictionInterface>(GetMovementComponent());
		if (PredictionInterface)
		{
			PredictionInterface->SmoothCorrection(OldLocation, OldRotation, ReplicatedMovement.Location, NewRotation);
		}
	}
}

void APCharacter::AddHorizontalMovement(float Amount)
{
	if (Amount != 0.0f)
	{
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Roll = 0.0f;
		ControlRotation.Pitch = 0.0f;
		const FQuat Rotation = GetActorQuat() * ControlRotation.Quaternion();

		AddMovementInput(Rotation.GetRightVector(), Amount);
	}
}

void APCharacter::AddVerticalMovement(float Amount)
{
	if (Amount != 0.0f)
	{
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Roll = 0.0f;
		ControlRotation.Pitch = 0.0f;
		const FQuat Rotation = GetActorQuat() * ControlRotation.Quaternion();

		AddMovementInput(Rotation.GetForwardVector(), Amount);
	}
}

void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FCalculateGravityResult Gravity = APGravityManager::CalculateGravity(Location);

	CharacterMovementComponent->SetGravityDirection(Gravity.Direction);
	CharacterMovementComponent->GravityPoint = Gravity.FloorPoint;
}
