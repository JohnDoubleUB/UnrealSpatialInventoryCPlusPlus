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

//Useful reference: https://github.com/dengboltj/ue4-umg-drag/blob/master/BagsProject/Source/BagsProject/Item.cpp
void UInventoryItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{	
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(OutOperation->StaticClass());

	OutOperation->Payload = PickupObject;
	OutOperation->DefaultDragVisual = this;
	OutOperation->Pivot = EDragPivot::CenterCenter;

	OnRemovedDelegate.Broadcast(PickupObject);
	RemoveFromParent();
}

void UInventoryItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (PickupObject == nullptr) 
	{
		return; 
	}

	UMaterialInterface* matInstance = PickupObject->GetIcon();

	if (CurrentIcon == matInstance) 
	{
		return;
	}
	 //TODO: Possibly improve this
	CurrentIcon = matInstance;

	FSlateBrush newSlateBrush = UWidgetBlueprintLibrary::MakeBrushFromMaterial(CurrentIcon, FMath::FloorToInt(Size.X), FMath::FloorToInt(Size.Y));

	ItemImage->Brush = newSlateBrush;

}
