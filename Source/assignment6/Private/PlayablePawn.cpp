// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayablePawn.h"
#include "PlayablePawnController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayablePawn::APlayablePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Acceleration = 50.0f;
	TurningSpeed = 2.0f;
	SprintSpeedMultiplier = 1.5f;
	JumpingPower = 1000.0f;
	DashCooldown = 1.0f;
	WindDrag = 0.1f;
	GroundedFriction = 2.0f;
	Weight = 30.0f;
	Gravity = 98.0f;

	CurrentSpeedX = 0.0f;
	CurrentSpeedY = 0.0f;
	CurrentSpeedZ = 0.0f;

	CurrentAngleX = 0.0f;
	CurrentAngleY = 0.0f;

	bIsSprint = false;
}

// Called when the game starts or when spawned
void APlayablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CurrentSpeedZ -= Gravity;

	if (!FMath::IsNearlyZero(CurrentSpeedX) || !FMath::IsNearlyZero(CurrentSpeedY) || !FMath::IsNearlyZero(CurrentSpeedZ))
	{
		AddActorWorldOffset(FVector(CurrentSpeedX * DeltaTime, CurrentSpeedY * DeltaTime, CurrentSpeedZ * DeltaTime));
		CurrentSpeedX -= CurrentSpeedX * GroundedFriction * DeltaTime;
		CurrentSpeedY -= CurrentSpeedY * GroundedFriction * DeltaTime;
		CurrentSpeedZ -= CurrentSpeedZ * GroundedFriction * DeltaTime;
	}
	if (!FMath::IsNearlyZero(CurrentAngleX) || !FMath::IsNearlyZero(CurrentAngleY)) 
	{
		SetActorRotation(FRotator(CurrentAngleY, CurrentAngleX, 0.0f));
	}
}

// Called to bind functionality to input
void APlayablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayablePawnController* PlayerController = Cast<APlayablePawnController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APlayablePawn::Move
				);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&APlayablePawn::Jump
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APlayablePawn::Look
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&APlayablePawn::StartSprint
				);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&APlayablePawn::StopSprint
				);
			}
		}
	}
}

void APlayablePawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X) || !FMath::IsNearlyZero(MoveInput.Y))
	{
		CurrentSpeedX += Acceleration * (MoveInput.X * FMath::Cos(GetActorRotation().Yaw * (PI / 180)) + MoveInput.Y * FMath::Cos((GetActorRotation().Yaw + 90) * (PI / 180)));
		CurrentSpeedY += Acceleration * (MoveInput.X * FMath::Sin(GetActorRotation().Yaw * (PI / 180)) + MoveInput.Y * FMath::Sin((GetActorRotation().Yaw + 90) * (PI / 180)));

		if (bIsSprint == true)
		{
			CurrentSpeedX += Acceleration * SprintSpeedMultiplier * (MoveInput.X * FMath::Cos(GetActorRotation().Yaw * (PI / 180)) + MoveInput.Y * FMath::Cos((GetActorRotation().Yaw + 90) * (PI / 180)));
			CurrentSpeedY += Acceleration * SprintSpeedMultiplier * (MoveInput.X * FMath::Sin(GetActorRotation().Yaw * (PI / 180)) + MoveInput.Y * FMath::Sin((GetActorRotation().Yaw + 90) * (PI / 180)));
		}
	}
}

void APlayablePawn::Jump(const FInputActionValue& value)
{
	if (!Controller) return;

	CurrentSpeedZ = JumpingPower;
}

void APlayablePawn::Look(const FInputActionValue& value)
{
	if (!Controller) return;

	FVector2D LookInput = value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(LookInput.X) || !FMath::IsNearlyZero(LookInput.Y))
	{
		CurrentAngleX += LookInput.X;
		CurrentAngleY += LookInput.Y;

	}
}

void APlayablePawn::StartSprint(const FInputActionValue& value)
{
	if (!Controller) return;

	bIsSprint = true;
}

void APlayablePawn::StopSprint(const FInputActionValue& value)
{
	if (!Controller) return;

	bIsSprint = false;
}