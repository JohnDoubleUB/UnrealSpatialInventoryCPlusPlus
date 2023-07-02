// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "BasicPickup.generated.h"

UCLASS(Blueprintable, Category="Game Interactable")
class OBSTACLEASSAULT_API ABasicPickup : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicPickup();

	virtual void Interact() override;
	inline virtual FString* GetName() override { return &Name; };
	inline virtual AActor* GetOwningActor() override { return this; }; //This is kinda cool

protected:
	UPROPERTY(EditAnywhere)
	FString Name;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
