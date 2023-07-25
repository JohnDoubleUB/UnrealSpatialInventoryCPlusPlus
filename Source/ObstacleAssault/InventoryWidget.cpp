#include "InventoryWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize)
{
	InventoryComponent = inventoryComponent;
	TileSize = tileSize;

	//TODO: Initialize Inventory Grid widget

	OnWidgetInitialized(inventoryComponent, *tileSize);
}
