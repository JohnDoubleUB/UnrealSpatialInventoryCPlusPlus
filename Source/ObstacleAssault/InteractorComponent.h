// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableInterface.h"
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent, BlueprintEditableComponent))
class OBSTACLEASSAULT_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	IInteractableInterface* CurrentInteractable = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	USceneComponent* ActorViewComponent;
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractDistance = 150.0f;

	IInteractableInterface* GetCurrentInteractable();
	bool TryGetCurrentInteractable(IInteractableInterface*& interactable);

	// Delegate signature
	DECLARE_DELEGATE_TwoParams(FOnInteractionChangeSignature, bool /* interaction */, FString* /* name */)
	FOnInteractionChangeSignature OnInteractionChangeDelegate;

	// Function signature
	//void OnInteractionChange(bool interaction);

private:
	void HandleItemHit();
	bool CheckIfValid();
	bool TryGetInteractableFromHit(FHitResult& hitResult, IInteractableInterface*& interactable);
};
