// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponentPatrol.generated.h"

UENUM()
enum class EPauseType { Location, Interval, None };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENT6_API UActorComponentPatrol : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentPatrol();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	FVector TargetLocation;			//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float PatrolSpeed;				//�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float PatrolPause;				//�Ͻ����� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	EPauseType PauseType;

private:
	AActor* Owner;					//������������
	FVector GlobalTargetLocation;	//�������� ������ġ
	FVector GlobalStartLocation;	//�������� ������ġ
	FVector Location;				//���� ��ġ
	FVector Direction;				//������ ����
	FVector Temp;					//�����ϱ� ���� �ӽ� ��
	
	FTimerHandle PauseTimer;			//�Ͻ����� Ÿ�̸�
	bool bIsMoving;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Pause();
};
