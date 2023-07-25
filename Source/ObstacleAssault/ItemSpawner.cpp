#include "ItemSpawner.h"

#include "ItemSpawner.h"

void UItemSpawner::SpawnItemFromActor(UPickupObject* pickupObject, AActor* actor, bool groundClamp)
{

	if (actor == nullptr || pickupObject == nullptr) return;

	FVector actorLocation = actor->GetActorLocation();
	FVector actorForward = actor->GetActorForwardVector();

	FVector dropLocation = actorLocation + (actorForward * 150);


}
