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
	//UFUNCTION(BlueprintCallable, Category = "Initialization") //I'm, attmepting to call this using c++ now so exposing it isn't neccesary?
	void InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* GridBorder;

private:
	UInventoryComponent* InventoryComponent;
	UCanvasPanelSlot* CanvasPanelSlot;
	float* TileSize;

protected:
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};