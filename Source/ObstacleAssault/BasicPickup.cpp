// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "BasicPickup.h"
#include "CustomTraceChannelNames.h"

// Sets default values
ABasicPickup::ABasicPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, 0));
}

void ABasicPickup::Interact(USceneComponent* interactingComponent)
{
	SetCanBeInteracted(false);
	InterpolationElapsed = 0.0f;
	TargetComponent = interactingComponent;
}

// Called when the game starts or when spawned
void ABasicPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasicPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPendingKill()) return;
	if (isValid || TargetComponent == nullptr) return; //If its a nullptr or target is still valid then return

	FVector currentTargetPos = TargetComponent->GetComponentLocation() - (TargetComponent->GetUpVector() * 80);
	FVector currentLocation = GetActorLocation();

	FVector targetForwardVector = currentLocation - (currentTargetPos - TargetComponent->GetForwardVector() * 50);
	targetForwardVector.Normalize();

	FRotator targetRotation = targetForwardVector.Rotation();

	InterpolationElapsed = FMath::Min(InterpolationElapsed + (InterpolationDuration * DeltaTime), 1);

	if (InterpolationElapsed > 0.15 && StaticMeshComponent->CastShadow) 
	{
		StaticMeshComponent->SetCastShadow(false);
	}

	if (InterpolationElapsed > 0.35f) 
	{
		Destroy();
	}

	SetActorLocation(FMath::Lerp(currentLocation, currentTargetPos, InterpolationElapsed));
	SetActorRotation(FMath::Lerp(GetActorRotation(), targetRotation, InterpolationElapsed));
}

void ABasicPickup::SetCanBeInteracted(const bool& canBeInteracted)
{
	isValid = canBeInteracted;
	StaticMeshComponent->SetCollisionObjectType(canBeInteracted ? ECC_PickupableItem : ECC_NoCollision);
	//StaticMeshComponent->SetCastShadow(canBeInteracted);
}

