#include "InventoryGridWidget.h"
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
	//GridBorder->GetSlot
	//UPanelSlot* panelSlot = GridBorder->Slot;
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
	if (GridCanvasPanel == nullptr) return;

	GridCanvasPanel->ClearChildren();

	TMap<UPickupObject*, FIntPoint> allItems = InventoryComponent->GetAllItems();


	for (auto& Elem : allItems)
	{
		//Create widget for item
		//Give tilesize
		// Bind an event it has to an on remove event
		// Add as child to canvas panel
		// Cast to panel slot
		// Set auto size
		// Set position
		//CreateWidget<>
	}

}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D localTopLeft = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f)); //Get top left
	FPaintContext paintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	

	for (auto& Line : Lines)
	{
		UWidgetBlueprintLibrary::DrawLine(paintContext, Line.Start + localTopLeft, Line.End + localTopLeft, FLinearColor(0.5f, 0.5f, 0.5f, 0.5f));
	}

	return int32();
}
