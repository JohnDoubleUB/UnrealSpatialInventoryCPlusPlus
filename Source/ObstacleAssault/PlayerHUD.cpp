

#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::SetItemName(FString newItemName)
{
	if (ItemName) 
	{
		ItemName->SetText(FText::FromString(newItemName));
	}
}
