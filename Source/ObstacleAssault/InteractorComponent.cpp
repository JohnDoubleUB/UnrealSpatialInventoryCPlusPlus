// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "CustomTraceChannelNames.h"
#include "InteractorComponent.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandleItemHit();
	// ...
}

IInteractableInterface* UInteractorComponent::GetCurrentInteractable()
{
	return CurrentInteractable;
}

void UInteractorComponent::HandleItemHit()
{
	if (CheckIfValid() == false) return;

	const FVector startLoc = Actor->GetActorLocation() + ActorViewComponent->GetRelativeLocation();
	const FVector endLoc = (ActorViewComponent->GetForwardVector() * InteractDistance) + startLoc;
	
	FHitResult hit;
	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(hit, startLoc, endLoc, ECC_PickupableItem, TraceParams);

	//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Orange, false, 0.1f);

	IInteractableInterface* newInteractable = nullptr; //I mean it was anyways but now its obvious

	if (bHit && TryGetInteractableFromHit(hit, newInteractable))
	{
		CurrentInteractable = newInteractable;
	}
	else if(CurrentInteractable != nullptr)
	{
		CurrentInteractable = nullptr;
		OnInteractionChangeDelegate.ExecuteIfBound(false, nullptr);
	}
}

bool UInteractorComponent::CheckIfValid() 
{
	if (Actor != nullptr && ActorViewComponent != nullptr) return true;

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, FString::Printf(TEXT("Oops, it looks like the Interactor Component has nullptrs!")));

	return false;
}

//Hello, hello, yes I came from C# and I miss my out parameters
bool UInteractorComponent::TryGetInteractableFromHit(FHitResult& hitResult, IInteractableInterface*& interactable) //This is how you'd define something a bit like an out parameter in C#
{
	AActor* hitActor = hitResult.GetActor();

	//Attempt to get actor return false if null
	if (hitActor == nullptr) 
	{
		return false; 
	}

	//Ensures that we only cast if this is a new interactable and not the same item we were already looking at
	if (CurrentInteractable != nullptr && CurrentInteractable->GetOwningActor() == hitActor) 
	{
		interactable = CurrentInteractable;
		return true;
	}
	
	//Check if it implements the correct interface, return false if it doesn't
	if (hitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()) == false) 
	{
		return false; 
	}

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Orange, FString::Printf(TEXT("New item found, casting!")));
	//Assign the pointer back to the interactable argument passed in
	interactable = Cast<IInteractableInterface>(hitActor);

	OnInteractionChangeDelegate.ExecuteIfBound(true, interactable->GetName());

	return true;
}

