

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

UCLASS(Abstract)
class OBSTACLEASSAULT_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
		
public:
	void SetHealth(float CurrentHealth, float MaxHealth);
	void SetPower(float CurrentPower, float MaxPower);
	void SetItemName(FString newItemName);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ItemName;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractAvailable(bool interacting);
};