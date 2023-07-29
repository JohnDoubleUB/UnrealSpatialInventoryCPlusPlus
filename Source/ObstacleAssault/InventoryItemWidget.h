#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

UCLASS(Abstract)
class OBSTACLEASSAULT_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeWidget(class UPickupObject* NewPickupObject, float NewTileSize);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ItemImage;

private:
	float TileSize;
	FVector2D Size;

	UPROPERTY(EditAnywhere)
	class UPickupObject* PickupObject;

	class UCanvasPanelSlot* ItemImageCanvasPanelSlot;

protected:
	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	class FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
};