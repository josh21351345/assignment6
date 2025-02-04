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
	FVector TargetLocation;			//목적지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float PatrolSpeed;				//이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	float PatrolPause;				//일시정지 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	EPauseType PauseType;

private:
	AActor* Owner;					//소유자포인터
	FVector GlobalTargetLocation;	//목적지의 세계위치
	FVector GlobalStartLocation;	//소유자의 세계위치
	FVector Location;				//현재 위치
	FVector Direction;				//목적지 방향
	FVector Temp;					//스왑하기 위한 임시 값
	
	FTimerHandle PauseTimer;			//일시정지 타이머
	bool bIsMoving;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Pause();
};
