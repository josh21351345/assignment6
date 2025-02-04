// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponentPatrol.h"

// Sets default values for this component's properties
UActorComponentPatrol::UActorComponentPatrol()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//�ʱ�ȭ
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
	
	GlobalStartLocation = Owner->GetActorLocation();										//������ġ
	GlobalTargetLocation = Owner->GetTransform().TransformPosition(TargetLocation);			//������ġ
	if (PauseType == EPauseType::Interval && !FMath::IsNearlyZero(PatrolPause))
	{
		GetWorld()->GetTimerManager().SetTimer(PauseTimer, this, &UActorComponentPatrol::Pause, PatrolPause, true);
	}
}


// Called every frame
void UActorComponentPatrol::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FMath::IsNearlyZero(PatrolSpeed) && TargetLocation != FVector(0.0f, 0.0f, 0.0f))	//���� �̵��Ѵٸ�
	{
		Location = Owner->GetActorLocation();												//������ ���� ��ġ
		Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();			//������ ����
		
		//�������� ����ġ�� �������� ������������ ����
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
			Location += Direction * PatrolSpeed * DeltaTime;									//����� �ӵ��� ��ŸŸ���� ���Ͽ� ������ġ ����
			Owner->SetActorLocation(Location);													//������ġ�� �̵�
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