// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFPCharacter.h"
#include "GameFramework/PlayerController.h"
#include "IsolPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OBSTACLEASSAULT_API AIsolPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AIsolPlayerController();
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	AMyFPCharacter* possesedPawn;

	void HorizontalMovement(float value);
	void VerticalMovement(float value);

	void HorizontalRotation(float value);
	void VerticalRotation(float value);

	void Crouch();
	void Jump();
	void Interact(const bool& pressed); //pressed or released

	void Sprint(const bool& sprint);
};
