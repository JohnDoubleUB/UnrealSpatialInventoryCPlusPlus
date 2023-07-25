#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryComponent.h"
#include "InventoryGridWidget.generated.h"

UCLASS(Abstract)
class OBSTACLEASSAULT_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializeWidget(UInventoryComponent* inventoryComponent, float tileSize);


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* GridBorder;

private:
	UInventoryComponent* InventoryComponent;
	UCanvasPanelSlot* CanvasPanelSlot;
	float* TileSize;
};