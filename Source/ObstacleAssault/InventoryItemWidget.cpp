#include "InventoryItemWidget.h"
#include "Components/SizeBox.h"
#include "PickupObject.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "InputCoreTypes.h"

void UInventoryItemWidget::InitializeWidget(UPickupObject* NewPickupObject, float NewTileSize)
{
	PickupObject = NewPickupObject;
	TileSize = NewTileSize;

	if (NewPickupObject == nullptr)
	{
		return;
	}

	FIntPoint* objectDimensions = NewPickupObject->GetDimensions();
	Size = FVector2D(objectDimensions->X * TileSize, objectDimensions->Y * TileSize);

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	ItemImageCanvasPanelSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);

	if (ItemImageCanvasPanelSlot == nullptr)
	{
		return;
	}

	ItemImageCanvasPanelSlot->SetSize(Size);
}

void UInventoryItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	BackgroundBorder->SetBrushColor(FLinearColor(0.5, 0.5, 0.5, 0.2));
}

void UInventoryItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	BackgroundBorder->SetBrushColor(FLinearColor(0, 0, 0, 0.5));
}

FReply UInventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return reply.NativeReply; //This requires private dependencies  "Slate", "SlateCore"  to be added in Build.cs
}

void UInventoryItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	//TODO: Continue this part of the code
	//UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation)
}
