// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PickupObject.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class OBSTACLEASSAULT_API UPickupObject : public UObject
{
	GENERATED_BODY()

public:
	FIntPoint* GetDimensions();
	void SetDimensions(FIntPoint NewDimensions) { Dimensions = NewDimensions; }
	bool GetIsRotated() { return bIsRotated; }
	UMaterialInterface* GetIconMaterialInterface() { return IconMaterialInterface; }
	UMaterialInterface* GetIconRotatedMaterialInterface() { return IconRotatedMaterialInterface; }
	UMaterialInterface* GetIcon();
	TSubclassOf<class ABasicPickup> GetItemSubclass() { return ItemClass; }
	UPickupObject* SetParameters(FIntPoint NewDimensions, UMaterialInterface* NewIconMaterialInterface, UMaterialInterface* NewIconRotatedMaterialInterface, TSubclassOf<class ABasicPickup> NewItemClass);
	void Rotate();

	DECLARE_DELEGATE(FOnRotationChange)
	FOnRotationChange OnRotationChange;

private:
	UPROPERTY(EditAnywhere)
	FIntPoint Dimensions = FIntPoint(10, 10);

	UPROPERTY(EditAnywhere)
	bool bIsRotated;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* IconMaterialInterface;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* IconRotatedMaterialInterface;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABasicPickup> ItemClass;

};
