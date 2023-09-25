#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoryGridWidget.h"
#include "ItemSpawner.h"
#include "InventoryWidget.generated.h"


UCLASS(Abstract)
class OBSTACLEASSAULT_API UInventoryWidget : public UUserWidget, public UItemSpawner
{
	GENERATED_BODY()

public:
	void InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetInitialized(UInventoryComponent* inventoryComponent, float tileSize);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInventoryGridWidget* InventoryGridWidget;

	void RotateDraggedObject();

private: 
	UInventoryComponent* InventoryComponent;
	float* TileSize;

protected:
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};