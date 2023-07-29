// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObject.h"

UPickupObject* UPickupObject::SetParameters(FIntPoint NewDimensions, UMaterialInterface* NewIconMaterialInterface, UMaterialInterface* NewIconRotatedMaterialInterface, TSubclassOf<class ABasicPickup> NewItemClass)
{
	Dimensions = NewDimensions;
	IconMaterialInterface = NewIconMaterialInterface;
	IconRotatedMaterialInterface = NewIconRotatedMaterialInterface;
	ItemClass = NewItemClass;


	return this;
}
