#include "InventoryGridWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"

void UInventoryGridWidget::InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize)
{
	InventoryComponent = inventoryComponent;
	TileSize = tileSize;

	if (InventoryComponent == nullptr) //If the inventory component is null then we don't want to do anything else
		return;
	//TODO: Continue implementing this method along with other things

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
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return false;
}
