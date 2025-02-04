// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponentRotate.h"

// Sets default values for this component's properties
UActorComponentRotate::UActorComponentRotate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RotationSpeedPitch = 0.0f;	//��ġ �ӵ�
	RotationSpeedYaw = 0.0f;	//�� �ӵ�
	RotationSpeedRoll = 0.0f;	//�� �ӵ�
	RotationPause = 0.0f;		//���� �ð�

	Owner = this->GetOwner();	//������ ����

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

	if (!FMath::IsNearlyZero(RotationSpeedPitch) || !FMath::IsNearlyZero(RotationSpeedYaw) || !FMath::IsNearlyZero(RotationSpeedRoll)) //���� ������ �ϳ��� 0�� �ƴ϶��
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