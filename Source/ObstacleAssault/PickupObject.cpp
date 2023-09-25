// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"

UMaterialInterface* UPickupObject::GetIcon()
{
	return bIsRotated ? IconRotatedMaterialInterface : IconMaterialInterface;
}

FIntPoint* UPickupObject::GetDimensions() 
{
	return &Dimensions; 
}

UPickupObject* UPickupObject::SetParameters(FIntPoint NewDimensions, UMaterialInterface* NewIconMaterialInterface, UMaterialInterface* NewIconRotatedMaterialInterface, TSubclassOf<class ABasicPickup> NewItemClass)
{
	Dimensions = NewDimensions;
	IconMaterialInterface = NewIconMaterialInterface;
	IconRotatedMaterialInterface = NewIconRotatedMaterialInterface;
	ItemClass = NewItemClass;


	return this;
}

void UPickupObject::Rotate()
{
	bIsRotated = !bIsRotated;
	
	int32 x = Dimensions.X;

	Dimensions.X = Dimensions.Y;
	Dimensions.Y = x;

	OnRotationChange.ExecuteIfBound();
}
