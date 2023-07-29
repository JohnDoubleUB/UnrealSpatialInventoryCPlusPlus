// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.

/*

TIL: If I was exposing any of this stuff to blueprints I.e. I set the paramater as UINTEFACE(BlueprintType), then I would be advised to use unreals weird interface safety checks
i.e:
in this class we wouldn't override, we'd instead just use 
UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger Reaction) //THis would allow implementation in blueprint on C++ 
bool interfaceFunction();

then in classes that implement this interface we would have:
UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger Reaction) //This would allow implementation in blueprint on C++
bool interfaceFunction();

bool interfaceFunction_implementation() override; // This gets generated on compile time, this is how you'd override this event in C++

then when calling a casted interface of this type you would use
castedInterface->Execute_interfaceFunction(); and this would safely call the override
unreal generates Excute_ for C++ use in these kinds of interfaces

*/
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
	virtual void Interact(USceneComponent* interactingComponent, AActor* interactingActor, class IInventoryHandlerInterface* inventoryHandlerInterface) = 0;
	virtual AActor* GetOwningActor() = 0;
	virtual bool IsValid() = 0; //If the pickup is currently valid

	virtual FString* GetName() = 0;


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