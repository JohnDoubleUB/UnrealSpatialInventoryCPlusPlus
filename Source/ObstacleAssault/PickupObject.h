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
	FIntPoint* GetDimensions() { return &Dimensions; }

private: 
	UPROPERTY(EditAnywhere)
	FIntPoint Dimensions = FIntPoint(10, 10);
	
};
