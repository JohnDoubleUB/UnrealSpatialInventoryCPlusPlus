// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "PickupObject.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InventoryGrid.SetNumUninitialized(Rows * Columns); //Initialize the Inventory grid

	// ...

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::TryAddItem(UPickupObject* pickupObject)
{
	if (pickupObject == nullptr) return false; //Check its a valid item

	FIntPoint* Dimensions = pickupObject->GetDimensions();

	//Check if item would fit length ways at this index
	if (Dimensions->X < 1 || Dimensions->Y < 1) return false; //If the dimensions are 0 then they are invalid
	if (Dimensions->X * Dimensions->Y > InventoryGrid.Num()) return false; //If item could not possibly fit in inventory

	TArray<int>* fullyValidatedIndexes = nullptr;

	//Iterate over each grid tile
	for (int i = 0; i < InventoryGrid.Num(); ++i)
	{

		if (IsRoomAvailable(i, Dimensions, fullyValidatedIndexes) && fullyValidatedIndexes != nullptr) //Check if this position is available and item is valid (it should be)
		{
			//Add item, this is a valid position!
			for (int x = 0; x < fullyValidatedIndexes->Num(); x++)
			{
				InventoryGrid[x] = pickupObject;
			}

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::IsRoomAvailable(int TopLeftIndex, FIntPoint* ItemDimensions, TArray<int>*& validatedIndexes)
{
	//validatedIndexes->Empty(); //Clear array incase it has anything in it
	return TryValidateGridAvailablility(TopLeftIndex, ItemDimensions, validatedIndexes);
}

bool UInventoryComponent::TryValidateGridAvailablility(int TopLeftIndex, FIntPoint* ItemDimensions, TArray<int>*& validatedIndexes)
{
	FIntPoint tileIndex = IndexToTile(TopLeftIndex); //Get the current tile

	//Furthest X and Y positions from top left most index
	int lastIndexX = tileIndex.X + ItemDimensions->X;
	int lastIndexY = tileIndex.Y + ItemDimensions->Y;

	//If it would overflow rows/columns return that this position is invalid
	if (lastIndexX >= Columns || lastIndexY >= Rows) return false;


	for (int x = tileIndex.X; x < lastIndexX; ++x) //get x
	{
		for (int y = tileIndex.Y; tileIndex.Y < lastIndexY; y++) //get y
		{
			int index = TileToIndex(x, y); //Get the index

			validatedIndexes->Add(index); //Add this index to the array

			if (InventoryGrid[index] == nullptr) //If nothing is in this array value then its clear!
			{
				continue;
			}

			//If we get to here then the position was not valid

			validatedIndexes->Empty(); //Empty the array as it might have old values in it

			return false;
		}
	}

	//If we reach this point then the placement is valid
	return true;
}

TMap<UPickupObject*, FIntPoint> UInventoryComponent::GetAllItems()
{
	TMap<UPickupObject*, FIntPoint> itemMap;

	for (int i = 0; i != InventoryGrid.Num(); ++i)
	{
		UPickupObject* currentItem = InventoryGrid[i];
		if (currentItem == nullptr) continue; //Skip over nullptr
		if (itemMap.Contains(currentItem)) continue; //Skip if item is already in map
		itemMap.Add(currentItem, IndexToTile(i));
	}

	return itemMap;
}

FIntPoint UInventoryComponent::IndexToTile(int index)
{
	return FIntPoint(index % Columns, index / Columns);
}

int UInventoryComponent::TileToIndex(int x, int y)
{
	return (y * Columns) + x;
}



