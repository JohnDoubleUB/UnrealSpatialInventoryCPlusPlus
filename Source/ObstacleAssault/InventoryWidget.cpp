#include "InventoryWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/DragDropOperation.h"
#include "BasicPickup.h"

void UInventoryWidget::InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize)
{
	InventoryComponent = inventoryComponent;
	TileSize = tileSize;

	if (InventoryGridWidget == nullptr) return;
	InventoryGridWidget->InitializeWidget(inventoryComponent, tileSize);
	OnWidgetInitialized(inventoryComponent, *tileSize);
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UPickupObject* pickupObject = Cast<UPickupObject>(InOperation->Payload); //Get the pickup
	
	if (pickupObject == nullptr) //Null check
		return false;

	UWorld* world = GetWorld();

	SpawnItemFromActor(GetWorld(), pickupObject, InventoryComponent->GetOwner(), true);

	return false;
}
