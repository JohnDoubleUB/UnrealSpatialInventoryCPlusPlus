// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPickup.h"

// Sets default values
ABasicPickup::ABasicPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABasicPickup::Interact()
{
	Destroy();
}

FString ABasicPickup::GetName()
{
	return Name;
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

