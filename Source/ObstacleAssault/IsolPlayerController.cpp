// Fill out your copyright notice in the Description page of Project Settings.


#include "IsolPlayerController.h"
#include "IsolGamemodeBase.h"

AIsolPlayerController::AIsolPlayerController()
{
}

void AIsolPlayerController::BeginPlay()
{
	Super::BeginPlay();

	possesedPawn = Cast<AMyFPCharacter>(GetPawn());
}

void AIsolPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveRight", this, &AIsolPlayerController::HorizontalMovement);
	InputComponent->BindAxis("MoveForward", this, &AIsolPlayerController::VerticalMovement);
	InputComponent->BindAxis("TurnRight", this, &AIsolPlayerController::HorizontalRotation);
	InputComponent->BindAxis("LookUp", this, &AIsolPlayerController::VerticalRotation);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AIsolPlayerController::Crouch);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AIsolPlayerController::Jump);
	InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AIsolPlayerController::ToggleInventory);

	FInputActionBinding SprintPressedAB("Sprint", IE_Pressed);
	SprintPressedAB.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			Sprint(true);
		}
	);

	FInputActionBinding SprintReleasedAB("Sprint", IE_Released);
	SprintReleasedAB.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			Sprint(false);
		}
	);

	InputComponent->AddActionBinding(SprintPressedAB);
	InputComponent->AddActionBinding(SprintReleasedAB);

	FInputActionBinding InteractPressedAB("Interact", IE_Pressed);
	InteractPressedAB.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			Interact(true);
		}
	);

	FInputActionBinding InteractReleasedAB("Interact", IE_Released);
	InteractReleasedAB.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			Interact(false);
		}
	);

	InputComponent->AddActionBinding(InteractPressedAB);
	InputComponent->AddActionBinding(InteractReleasedAB);

}

void AIsolPlayerController::Tick(float DeltaTime)
{
}

void AIsolPlayerController::HorizontalMovement(float value)
{
	if (possesedPawn) 
	{
		possesedPawn->HorizontalMovement(value);
	}
}

void AIsolPlayerController::VerticalMovement(float value)
{
	if (possesedPawn) 
	{
		possesedPawn->VerticalMovement(value);
	}
}

void AIsolPlayerController::HorizontalRotation(float value)
{
	if (possesedPawn) 
	{
		possesedPawn->HorizontalRotation(value);
	}
}

void AIsolPlayerController::VerticalRotation(float value)
{
	if (possesedPawn)
	{
		possesedPawn->VerticalRotation(value);
	}
}

void AIsolPlayerController::Crouch()
{
	if (possesedPawn)
	{
		possesedPawn->Crouch();
	}
}

void AIsolPlayerController::Jump()
{
	if (possesedPawn)
	{
		possesedPawn->Jump();
	}
}

void AIsolPlayerController::Interact(const bool& pressed)
{
	if (possesedPawn) 
	{
		possesedPawn->Interact(pressed);
	}
}

void AIsolPlayerController::ToggleInventory()
{
	if (possesedPawn) 
	{
		possesedPawn->ToggleInventory();
	}
}

void AIsolPlayerController::Sprint(const bool& sprint)
{
	if (possesedPawn)
	{
		possesedPawn->Sprint(sprint);
	}
}
