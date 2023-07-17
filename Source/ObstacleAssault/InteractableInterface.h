// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OBSTACLEASSAULT_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(USceneComponent* interactingComponent) = 0;
	virtual AActor* GetOwningActor() = 0;
	virtual bool IsValid() = 0; //If the pickup is currently valid

	virtual FString* GetName();

	EInteractionType GetInteractionType();

protected:
	EInteractionType InteractionType;
	
	
};

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	Button UMETA(DisplayName = "Button"),
	Physics UMETA(DisplayName = "Physics"),
	PhysicsRigid UMETA(DisplayName = "PhysicsRigid")
};