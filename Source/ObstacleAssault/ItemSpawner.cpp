#include "ItemSpawner.h"

#include "ItemSpawner.h"
#include "CustomTraceChannelNames.h"
#include "BasicPickup.h"

void UItemSpawner::SpawnItemFromActor(UWorld* world, UPickupObject* pickupObject, AActor* actor, bool groundClamp)
{

	if (actor == nullptr || pickupObject == nullptr) return;

	TSubclassOf<ABasicPickup> itemSubclass = pickupObject->GetItemSubclass();

	if (itemSubclass == nullptr) return;

	FVector actorLocation = actor->GetActorLocation();
	FVector actorForward = actor->GetActorForwardVector();

	FVector dropLocation = actorLocation + (actorForward * 150);
	FVector spawnLocation = dropLocation;

	if (groundClamp) 
	{
		FHitResult hit;
		FCollisionQueryParams TraceParams;
		FCollisionObjectQueryParams ObjectQueryParams;

		ObjectQueryParams.AddObjectTypesToQuery(ECC_Visibility);

		bool bHit = world->LineTraceSingleByObjectType(hit, dropLocation, dropLocation - FVector(0, 0, 1000), ObjectQueryParams);

		if (bHit) 
		{
			spawnLocation = hit.Location;
		}
	}

	FActorSpawnParameters spawnParams;

	world->SpawnActor<ABasicPickup>(itemSubclass, spawnLocation, FRotator(), spawnParams);
}
