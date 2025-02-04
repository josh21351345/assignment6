// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponentPatrol.h"

// Sets default values for this component's properties
UActorComponentPatrol::UActorComponentPatrol()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//초기화
	TargetLocation = FVector(0.0f, 0.0f, 0.0f);
	PatrolSpeed = 0.0f;
	PatrolPause = 0.0f;
	PauseType = EPauseType::Location;

	Temp = FVector(0.0f, 0.0f, 0.0f);
	GlobalStartLocation = FVector(0.0f, 0.0f, 0.0f);
	GlobalTargetLocation = FVector(0.0f, 0.0f, 0.0f);
	Location = FVector(0.0f, 0.0f, 0.0f);
	Direction = FVector(0.0f, 0.0f, 0.0f);
	Owner = this->GetOwner();

	bIsMoving = true;
}


// Called when the game starts
void UActorComponentPatrol::BeginPlay()
{
	Super::BeginPlay();
	
	GlobalStartLocation = Owner->GetActorLocation();										//시작위치
	GlobalTargetLocation = Owner->GetTransform().TransformPosition(TargetLocation);			//도착위치
	if (PauseType == EPauseType::Interval && !FMath::IsNearlyZero(PatrolPause))
	{
		GetWorld()->GetTimerManager().SetTimer(PauseTimer, this, &UActorComponentPatrol::Pause, PatrolPause, true);
	}
}


// Called every frame
void UActorComponentPatrol::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FMath::IsNearlyZero(PatrolSpeed) && TargetLocation != FVector(0.0f, 0.0f, 0.0f))	//만약 이동한다면
	{
		Location = Owner->GetActorLocation();												//엑터의 현재 위치
		Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();			//목적지 방향
		
		//목적지를 지나치면 목적지를 시작지점으로 변경
		if ((Location - GlobalStartLocation).Size() > (GlobalTargetLocation - GlobalStartLocation).Size())
		{
			if (
				PauseType == EPauseType::Location && !FMath::IsNearlyZero(PatrolPause))
			{

				Pause();
			}
			Temp = GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation;
			GlobalStartLocation = Temp;
		}
		if (bIsMoving == true)
		{
			Location += Direction * PatrolSpeed * DeltaTime;									//방향과 속도와 델타타임을 곱하여 다음위치 지정
			Owner->SetActorLocation(Location);													//다음위치로 이동
		}
	}

}


void UActorComponentPatrol::Pause()
{
	if (bIsMoving == true)
	{
		bIsMoving = false;
		if (PauseType == EPauseType::Location)
		{
			GetWorld()->GetTimerManager().SetTimer(PauseTimer, this, &UActorComponentPatrol::Pause, PatrolPause, false);
		}
	}
	else
	{
		bIsMoving = true;
	}
}