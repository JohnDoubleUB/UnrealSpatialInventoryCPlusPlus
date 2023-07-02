// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.

FString* IInteractableInterface::GetName()
{
	return nullptr;
}

EInteractionType IInteractableInterface::GetInteractionType()
{
	return InteractionType;
}


