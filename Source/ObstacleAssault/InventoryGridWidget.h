#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryComponent.h"
#include "InventoryGridLineStruct.h"
#include "InventoryGridWidget.generated.h"

UCLASS(Abstract)
class OBSTACLEASSAULT_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "Initialization") //I'm, attmepting to call this using c++ now so exposing it isn't neccesary?
	void InitializeWidget(UInventoryComponent* inventoryComponent, float* tileSize);

	void CreateLineSegments();

	void Refresh(); //Was working on this!

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* GridBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

private:
	UInventoryComponent* InventoryComponent;
	UCanvasPanelSlot* CanvasPanelSlot;
	float* TileSize;
	TArray<FInventoryGridLineStruct> Lines;

protected:
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
};