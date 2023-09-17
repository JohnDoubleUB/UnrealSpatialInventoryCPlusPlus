// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupObject.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FInventoryChangeDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, BlueprintEditableComponent) )
class OBSTACLEASSAULT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool TryAddItem(UPickupObject* pickupObject);

	bool IsRoomAvailable(int TopLeftIndex, FIntPoint* ItemDimensions, TArray<int>*& validatedIndexes);

	bool TryValidateGridAvailablility(int topLeftIndex, FIntPoint* ItemDimensions, TArray<int>*& validatedIndexes);

	void RemoveItem(UPickupObject* pickupObject);

	void AddItemAtInventoryGridIndexes(UPickupObject* pickupObject, TArray<int> validatedIndexPositions);

	TMap<UPickupObject*, FIntPoint> GetAllItems();

	FIntPoint IndexToTile(int index);

	int TileToIndex(int x, int y);

	TArray<UPickupObject*> InventoryGrid;

	FInventoryChangeDelegate OnInventoryChangeDelegate;

	UPROPERTY(EditAnywhere)
	int Rows = 6;
	UPROPERTY(EditAnywhere)
	int Columns = 6;

private:
	bool IsDirty;

		
};
