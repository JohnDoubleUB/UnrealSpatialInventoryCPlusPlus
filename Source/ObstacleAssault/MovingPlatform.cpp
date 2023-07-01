// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	Player1Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	StartLocation = GetActorLocation();
	//if (Player1Pawn != nullptr) //Check that this isn't a nullptr
	//{
	//	FVector playerLoc = Player1Pawn->GetActorLocation();
	//	TargetLoc = (Player1Pawn->GetActorForwardVector() * 100) + playerLoc;
	//	FVector rotationEuler = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerLoc).Euler();
	//	rotationEuler.Y = 0;
	//	SetActorLocationAndRotation(TargetLoc, FRotator::MakeFromEuler(rotationEuler));
	//}


}

//References can't change after compilation
//Pointers can

// Called every frame
void AMovingPlatform::Tick(float DeltaTime) //Scope resolution operator ::
{
	Super::Tick(DeltaTime);
	//PointersAndReferencesWeirdness(&DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(DeltaTime));//Sanitize these nuts

	//FVector NewLocation = GetActorLocation();
	//float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//NewLocation.Z += DeltaHeight * 100.0f; // Scale our height by a factor of 20
	//RunningTime += DeltaTime;
	//
	//NewLocation.X += 50 * DeltaTime;
	
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

	SetActorLocation(CurrentLocation);

	float distanceMoved = FVector::Distance(CurrentLocation, StartLocation);

	if (distanceMoved > MoveDistance) 
	{
		StartLocation = StartLocation + (PlatformVelocity.GetSafeNormal() * MoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}

	//// Move the platform forwards
	//	// Get current location
	//FVector currentLoc = GetActorLocation();
	//	// Add vector to that location
	//	// Set the location
	//currentLoc.X += 300 * DeltaTime;
	//SetActorLocation(currentLoc);



	//Send platform back if gone too far
		// Check how far we've moved
		// Reverse direction of motion if gone too far.
}

void AMovingPlatform::PointersAndReferencesWeirdness(float* deltaTime)
{

	//Using references to manipulate a variable via another variable (a reference)
	//double& y = TargetLoc.Y; //This is a reference to targetLoc.y which allows us to do weird things
	//y += 50.0f * *deltaTime;

	// Using a pointer that we then dereference in order to refer directly to what the pointer is pointing at (Yes that's convoluted)
	// In order to change the value via a pointer to the variable (Got it?) 
	double* y2 = &TargetLoc.Y;
	(*y2) += 50.0f * *deltaTime; //More dereferencing :?

	//Why? Because pointers and references are weird
	//Pointers -> Can change what they are pointing at, this is why they can also be null
	//Reference -> These can only refer to one thing and cannot change.
	//Pointers are basically references that can change? (but also don't let us manupulate the variable directly unless we dereference)

	//double test = static_cast<double>((200.0f * DeltaTime));
	//TargetLoc.X = TargetLoc.X + (50.0f * DeltaTime);
}

