// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "BasicPickup.generated.h"

//class UStaticMeshComponent; // Forward declaration

UCLASS(Blueprintable, Category="Game Interactable")
class OBSTACLEASSAULT_API ABasicPickup : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicPickup();

	virtual void Interact(USceneComponent* interactingComponent) override;
	inline virtual FString* GetName() override { return &Name; };
	inline virtual AActor* GetOwningActor() override { return this; }; //This is kinda cool
	inline virtual bool IsValid() override { return isValid; }

protected:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float InterpolationDuration = 0.5f; // Duration in seconds

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;


private:
	bool isValid = true;
	USceneComponent* TargetComponent;
	float InterpolationElapsed = 0.0f;

	void SetCanBeInteracted(const bool& canBeInteracted);

};
