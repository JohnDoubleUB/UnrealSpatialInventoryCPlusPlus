#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoryWidget.generated.h"

UCLASS(Abstract)
class OBSTACLEASSAULT_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetInitialized(UInventoryComponent* inventoryComponent, float tileSize);

private: 
	UInventoryComponent* InventoryComponent;
	float* TileSize;
};