// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickupObject.h"

class UItemSpawner
{
	protected:
		void SpawnItemFromActor(UPickupObject* pickupObject, AActor* actor, bool groundClamp);

};