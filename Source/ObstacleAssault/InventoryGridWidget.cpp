#include "InventoryGridWidget.h"
#include "PickupObject.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UInventoryGridWidget::InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize)
{
	InventoryComponent = inventoryComponent;
	TileSize = tileSize;

	if (InventoryComponent == nullptr) //If the inventory component is null then we don't want to do anything else
		return;
	

	//Get the canvas panel slot:
	CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot); //Hopefully this should work?
	
	if (CanvasPanelSlot == nullptr) 
	{
		//Log something here
		//return to avoid crash
		return;
	}

	CanvasPanelSlot->SetSize(FVector2D(InventoryComponent->Columns * (*TileSize), InventoryComponent->Rows * (*TileSize)));

	CreateLineSegments();

	//TODO: Continue implementing this method along with other things
	Refresh();

	//Bind Refresh to on Inventory changed
	InventoryComponent->OnInventoryChangeDelegate.AddUObject(this, &UInventoryGridWidget::Refresh);
}

void UInventoryGridWidget::CreateLineSegments()
{
	Lines.Empty(); //Empty incase there are items before this point

	//Create vertical lines

	float endOfRowTile = InventoryComponent->Rows * (*TileSize);

	for (int i = 0; i <= InventoryComponent->Columns; i++) 
	{
		float localX = i * (*TileSize);

		FInventoryGridLineStruct newGridLine = FInventoryGridLineStruct(
			FVector2D(localX, 0), //Start
			FVector2D(localX, endOfRowTile) //End
		);

		Lines.Add(newGridLine);
	}

	//Create horizontal lines

	float endOfColumnTile = InventoryComponent->Columns * (*TileSize);
	
	for (int i = 0; i <= InventoryComponent->Rows; i++) 
	{
		float localY = i * (*TileSize);

		FInventoryGridLineStruct newGridLine = FInventoryGridLineStruct(
			FVector2D(0, localY), //Start
			FVector2D(endOfColumnTile, localY) //End
		);

		Lines.Add(newGridLine);
	}
}

void UInventoryGridWidget::Refresh()
{
	if (GridCanvasPanel == nullptr || ItemWidgetClass == nullptr) 
	{
		return; 
	}

	GridCanvasPanel->ClearChildren();

	TMap<UPickupObject*, FIntPoint> allItems = InventoryComponent->GetAllItems();

	for (auto& Elem : allItems)
	{
		UInventoryItemWidget* newWidget = CreateWidget<UInventoryItemWidget>(this, ItemWidgetClass);
		newWidget->InitializeWidget(Elem.Key, *TileSize);

		newWidget->OnRemovedDelegate.AddUObject(this, &UInventoryGridWidget::OnItemRemovedEvent);
		
		UPanelSlot* panelSlot = GridCanvasPanel->AddChild(newWidget);
		UCanvasPanelSlot* gridCanvasPanelSlot = Cast<UCanvasPanelSlot>(panelSlot);
		
		if (gridCanvasPanelSlot)
		{
			float tileSize = *TileSize;
			gridCanvasPanelSlot->SetAutoSize(true);
			gridCanvasPanelSlot->SetPosition(FVector2D(Elem.Value.X * tileSize, Elem.Value.Y * tileSize));
		}
	}

}

void UInventoryGridWidget::OnItemRemovedEvent(UPickupObject* PickupObject)
{
	InventoryComponent->RemoveItem(PickupObject);
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation); //We don't want to call this other event it is being handled!

	UE_LOG(LogTemp, Warning, TEXT("Drag End"));
	CurrentlyDraggedObject = nullptr;

	UPickupObject* pickupObjectPayload = Cast<UPickupObject>(InOperation->Payload);

	TArray<int> fullyValidatedIndexes;
	TArray<int>* fullyValidatedIndexesPtr = &fullyValidatedIndexes;

	if (pickupObjectPayload != nullptr)
	{
		FIntPoint* pickupDimensions = pickupObjectPayload->GetDimensions();

		if (InventoryComponent->TryValidateGridAvailablility(DragItemTopLeftTile(DragMousePosition, pickupDimensions), pickupDimensions, fullyValidatedIndexesPtr))
		{
			//Room is available
			//UE_LOG(LogTemp, Warning, TEXT("Hello, Unreal! This is a warning message. Yeeeee"));
			InventoryComponent->AddItemAtInventoryGridIndexes(pickupObjectPayload, fullyValidatedIndexes);
		}
		else if (!InventoryComponent->TryAddItem(pickupObjectPayload)) //Check if item can be added back
		{
			//If not we spawn it
			SpawnItemFromActor(GetWorld(), pickupObjectPayload, InventoryComponent->GetOwner(), true);
		}

		return true;
	}

	//Room was not available
	return false;
}

//NOTE: Const functions can only call other const functions on the same object, because const functions cannot alter the object they are part of in any way
int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D localTopLeft = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f)); //Get top left
	FPaintContext paintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	

	for (auto& Line : Lines)
	{
		UWidgetBlueprintLibrary::DrawLine(paintContext, Line.Start + localTopLeft, Line.End + localTopLeft, FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
	}

	//TODO: Add in the paint code for the drag and drop color display
	//Almost done!

	if (CurrentlyDraggedObject != nullptr) 
	{
		FIntPoint topLeftTile = DragItemTopLeftTile(DragMousePosition, CurrentlyDraggedObject->GetDimensions());
		bool goodPosition = InventoryComponent->IsRoomAvailable(topLeftTile, CurrentlyDraggedObject->GetDimensions());

		float currentTileSize = *TileSize;
		//Idk how to draw box
		UWidgetBlueprintLibrary::DrawBox(
			paintContext,
			FVector2D(topLeftTile) * currentTileSize,
			FVector2D(*CurrentlyDraggedObject->GetDimensions()) * currentTileSize,
			DragAndDropBackgroundBrush,
			goodPosition ? DroppingAllowedColor : DroppingDisallowedColor
		);

	}

	return int32();
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DragMousePosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	return true;
}

void UInventoryGridWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Drag enter"));
	CurrentlyDraggedObject = Cast<UPickupObject>(InOperation->Payload);

}

void UInventoryGridWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Drag End"));
	CurrentlyDraggedObject = nullptr;
}

FIntPoint UInventoryGridWidget::DragItemTopLeftTile(const FVector2D dragMousePosition, FIntPoint* itemDimensions) const
{
	float tileHalfExtents = *TileSize * 0.5f;
	float tileSize = *TileSize;

	bool right = FMath::Fmod(dragMousePosition.X, tileSize) > tileHalfExtents;
	bool down = FMath::Fmod(dragMousePosition.Y, tileSize) > tileHalfExtents;

	FIntPoint topLeftTilePos = FIntPoint(
		(dragMousePosition.X / tileSize) - (FMath::Max(right ? itemDimensions->X - 1 : itemDimensions->X, 0) / 2),
		(dragMousePosition.Y / tileSize) - (FMath::Max(down ? itemDimensions->Y - 1 : itemDimensions->Y, 0) / 2)
	);

	return topLeftTilePos;
}