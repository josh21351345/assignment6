// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponentRotate.h"

// Sets default values for this component's properties
UActorComponentRotate::UActorComponentRotate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RotationSpeedPitch = 0.0f;	//피치 속도
	RotationSpeedYaw = 0.0f;	//요 속도
	RotationSpeedRoll = 0.0f;	//롤 속도
	RotationPause = 0.0f;		//정지 시간

	Owner = this->GetOwner();	//오너의 정보

	bIsMoving = true;
}


// Called when the game starts
void UActorComponentRotate::BeginPlay()
{
	Super::BeginPlay();

	if (!FMath::IsNearlyZero(RotationPause))
	{
		GetWorld()->GetTimerManager().SetTimer(PauseTimer, this, &UActorComponentRotate::Pause, RotationPause, true);
	}
}


// Called every frame
void UActorComponentRotate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FMath::IsNearlyZero(RotationSpeedPitch) || !FMath::IsNearlyZero(RotationSpeedYaw) || !FMath::IsNearlyZero(RotationSpeedRoll)) //만약 값들중 하나라도 0이 아니라면
	{
		if (bIsMoving == true)
		{
			Owner->AddActorLocalRotation(FRotator(RotationSpeedPitch * DeltaTime, RotationSpeedYaw * DeltaTime, RotationSpeedRoll * DeltaTime));
		}
	}
}

void UActorComponentRotate::Pause()
{
	bIsMoving = !bIsMoving;
}