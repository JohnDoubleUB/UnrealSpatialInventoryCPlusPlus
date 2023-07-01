// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestSharedEnums.h"
#include "MovingPlatform.generated.h"


UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AMovingPlatform();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
	TEnumAsByte<Status> status;

	UPROPERTY(EditAnywhere)
	FVector TargetLoc; //We don't use the new keyword in C++??
	UPROPERTY(EditAnywhere)
	float MyX;

	UPROPERTY(EditAnywhere)
	FVector PlayerLoc;

	APawn* Player1Pawn = nullptr; //Oopsie

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	FVector PlatformVelocity = FVector(100, 0, 0);

	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float MoveDistance = 100;

private:
	void PointersAndReferencesWeirdness(float* deltaTime);//IDK what I'm doing

	double RunningTime = 0;

};




