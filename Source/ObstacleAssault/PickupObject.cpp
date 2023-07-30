// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"

UMaterialInterface* UPickupObject::GetIcon()
{
	return bIsRotated ? IconRotatedMaterialInterface : IconMaterialInterface;
}

UPickupObject* UPickupObject::SetParameters(FIntPoint NewDimensions, UMaterialInterface* NewIconMaterialInterface, UMaterialInterface* NewIconRotatedMaterialInterface, TSubclassOf<class ABasicPickup> NewItemClass)
{
	Dimensions = NewDimensions;
	IconMaterialInterface = NewIconMaterialInterface;
	IconRotatedMaterialInterface = NewIconRotatedMaterialInterface;
	ItemClass = NewItemClass;


	return this;
}
