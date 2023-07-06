// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "BasicPickup.h"
#include "CustomTraceChannelNames.h"

// Sets default values
ABasicPickup::ABasicPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetRelativeLocation(FVector(0, 0, 0));
}

void ABasicPickup::Interact()
{
	SetCanBeInteracted(false);
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

}

void ABasicPickup::SetCanBeInteracted(const bool& canBeInteracted)
{
	isValid = canBeInteracted;
	StaticMeshComponent->SetCollisionObjectType(canBeInteracted ? ECC_PickupableItem : ECC_NonPickupableItem);
}

