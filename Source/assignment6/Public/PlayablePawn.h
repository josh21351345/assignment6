// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayablePawn.generated.h"

class USphereComponent;
struct FInputActionValue;

UCLASS()
class ASSIGNMENT6_API APlayablePawn : public APawn
{
	GENERATED_BODY()



public:
	// Sets default values for this pawn's properties
	APlayablePawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movespeed")
	float Acceleration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movespeed")
	float TurningSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movespeed")
	float SprintSpeedMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movespeed")
	float JumpingPower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movespeed")
	float DashCooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
	float WindDrag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
	float GroundedFriction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
	float Weight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
	float Gravity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	float CurrentSpeedX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	float CurrentSpeedY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	float CurrentSpeedZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	float CurrentAngleX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	float CurrentAngleY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	bool bIsSprint;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Jump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
	//UFUNCTION()
	//void Dash(const FInputActionValue& value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
