// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerHUD.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/AudioComponent.h"
#include "MyFPCharacter.h"
#include "CustomTraceChannelNames.h"


// Sets default values
AMyFPCharacter::AMyFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	CharacterMovement = GetCharacterMovement();

	CapsuleComponent = GetCapsuleComponent();

	UncrouchTraceRadius = CapsuleComponent->GetCollisionShape().GetCapsuleRadius();

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	cam->SetRelativeLocation(FVector(0, 0, 40));

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor"));
	InteractorComponent->Actor = this;
	InteractorComponent->ActorViewComponent = cam;

	//Bind to interactor event
	InteractorComponent->OnInteractionChangeDelegate.BindUObject(this, &AMyFPCharacter::OnInteractionChange);

	//Add Inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
}

// Called when the game starts or when spawned
void AMyFPCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultCameraZPos = cam->GetRelativeLocation().Z;
	DefaultCameraRoll = cam->GetRelativeRotation().Roll;
	SetCrouch(false);

	if (IsLocallyControlled() && PlayerHUDClass)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (PlayerHUDClass) 
		{
			PlayerHUD = CreateWidget<UPlayerHUD>(PlayerController, PlayerHUDClass);
			PlayerHUD->AddToPlayerScreen();
		}

		if (InventoryWidgetClass) 
		{
			InventoryWidget = CreateWidget<UInventoryWidget>(PlayerController, InventoryWidgetClass);
			InventoryWidget->InitializeWidget(InventoryComponent, &TileSize);
		}

	}


}

void AMyFPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		//We can't destroy the widget directly, let the GC take care of it.
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMyFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentVelocity = GetVelocity();
	bool isFalling = CharacterMovement->IsFalling();
	FVector cameraHeight = CameraBob(DeltaTime, isFalling);
	HandleFootstep(cameraHeight, isFalling);
	HandleCrouch(DeltaTime);
}

FVector AMyFPCharacter::CameraBob(const float& DeltaTime, const bool& falling)
{
	FVector curRelativeLoc = cam->GetRelativeLocation();
	FRotator curRelativeRot = cam->GetRelativeRotation();

	if (falling)
	{
		bWasInAir = true;
		SwayTimer = 0;
		BobTimer = 0;
		curRelativeLoc.Z = DefaultCameraZPos;
		curRelativeRot.Roll = DefaultCameraRoll;
	}
	else if (FMath::Abs(CurrentVelocity.X) > 0.1 || FMath::Abs(CurrentVelocity.Y) > 0.1)
	{
		BobTimer += DeltaTime * (WalkingBobbingSpeed * MovementSpeed);
		SwayTimer += DeltaTime * (WalkingSwaySpeed * MovementSpeed);

		curRelativeLoc.Z = DefaultCameraZPos + (FMath::Sin(BobTimer) * BobbingAmount);
		curRelativeRot.Roll = DefaultCameraRoll + (FMath::Sin(SwayTimer) * SwayAmount);
	}
	else
	{
		SwayTimer = 0;
		BobTimer = 0;
		curRelativeLoc.Z = FMath::Lerp(curRelativeLoc.Z, DefaultCameraZPos, DeltaTime * (WalkingBobbingSpeed * MovementSpeed));
		curRelativeRot.Roll = FMath::Lerp(curRelativeRot.Roll, DefaultCameraRoll, DeltaTime * (WalkingSwaySpeed * MovementSpeed));
	}

	cam->SetRelativeLocation(curRelativeLoc);
	cam->SetRelativeRotation(curRelativeRot);

	return curRelativeLoc;
}

void AMyFPCharacter::HandleFootstep(const FVector& currentCameraPosition, const bool& isFalling)
{
	if (bWasInAir && !isFalling)
	{
		PlayFootLand();
	}

	if (!bStepTaken && currentCameraPosition.Z < DefaultCameraZPos)
	{
		PlayFootstep();
		bStepTaken = true;
	}
	else if (bStepTaken && currentCameraPosition.Z >= DefaultCameraZPos)
	{
		bStepTaken = false;
	}

	bWasInAir = isFalling;
}

void AMyFPCharacter::PlayFootstep()
{
	UE_LOG(LogTemp, Warning, TEXT("Play Footstep"));

	if (FootstepSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FootstepSound, GetActorLocation());
	}
}

void AMyFPCharacter::PlayFootLand()
{
	UE_LOG(LogTemp, Warning, TEXT("Play Footland"));
	if (FootstepSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FootstepSound, GetActorLocation());
	}
}

void AMyFPCharacter::OnInteractionChange(bool interaction, FString* name)
{
	if (PlayerHUD)
	{
		PlayerHUD->SetItemName(name != nullptr ? *name : FString()); //We don't want to accidentally dereference a nullptr, things will die
		PlayerHUD->OnInteractAvailable(interaction);
	}
}

void AMyFPCharacter::Crouch()
{
	SetCrouch(!bIsCrouching);
}

bool AMyFPCharacter::SetCrouch(const bool& crouch)
{
	if (bIsCrouching && CanUnCrouch() == false)
	{
		return false;
	}

	bIsCrouching = crouch;
	MovementSpeed = bIsCrouching ? CrouchingSpeed : WalkingSpeed;
	return true;
}


bool AMyFPCharacter::CanUnCrouch()
{
	const FVector startLoc = GetActorLocation();
	const FVector endLoc = FVector(startLoc.X, startLoc.Y, startLoc.Z + CharacterMovement->CrouchedHalfHeight);
	CapsuleComponent->GetCollisionShape().GetCapsuleRadius();
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	//If nothing is hit then we can uncrouch!
	return !GetWorld()->SweepSingleByChannel(HitResult, startLoc, endLoc, FQuat::Identity, ECC_Camera, CapsuleComponent->GetCollisionShape(), TraceParams);
}


void AMyFPCharacter::Jump()
{
	if (bIsCrouching && SetCrouch(false) == false) return;
	Super::Jump();
}

void AMyFPCharacter::Interact(const bool& pressed)
{
	if (pressed)
	{
		IInteractableInterface* currentInteractable;

		if (InteractorComponent->TryGetCurrentInteractable(currentInteractable)) //Try and get interactable if one is present
		{
			InteractWithObject(currentInteractable);
		}
	}
}


void AMyFPCharacter::InteractWithObject(IInteractableInterface* interactable)
{
	interactable->Interact(cam, this, this);
}

bool AMyFPCharacter::TryAddItemToInventory(UPickupObject* pickupObject)
{
	if (InventoryComponent == nullptr) 
	{
		return false;
	}

	return InventoryComponent->TryAddItem(pickupObject);
}

void AMyFPCharacter::ToggleInventory()
{
	bIsInInventory = !bIsInInventory;
	OnInventoryEnabled(!bIsInInventory);

	if (InventoryWidget == nullptr) return;

	if (!bIsInInventory) 
	{
		InventoryWidget->RemoveFromParent();

		//Create an input mode
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
	else 
	{
		//Create input mode
		FInputModeGameAndUI gameAndUIInputMode;

		//Make this new widget in focus
		gameAndUIInputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		gameAndUIInputMode.SetHideCursorDuringCapture(false); //Show mouse

		InventoryWidget->AddToPlayerScreen();
		PlayerController->SetInputMode(gameAndUIInputMode);
	}

	PlayerController->SetShowMouseCursor(bIsInInventory);
}

void AMyFPCharacter::Sprint(const bool& sprint)
{
	//UE_LOG(LogTemp, Warning, TEXT("Perform sprint: %s"), (sprint ? "True" : "False"));

	if (sprint)
	{
		if (bIsCrouching && SetCrouch(false) == false) return; //Return if we fail to uncrouch
		MovementSpeed = RunningSpeed;
	}
	else
	{
		MovementSpeed = bIsCrouching ? CrouchingSpeed : WalkingSpeed;
	}
}

void AMyFPCharacter::HandleCrouch(const float& DeltaTime)
{
	const float TargetBEH = bIsCrouching ? CrouchedEyeHeight : BaseEyeHeight;
	const float TargetCapsuleSize = bIsCrouching ? CharacterMovement->CrouchedHalfHeight : CharacterMovement->CrouchedHalfHeight * 2;

	if (Controller != NULL)
	{
		BaseEyeHeight = FMath::FInterpTo(BaseEyeHeight, TargetBEH, DeltaTime, 10.0f);
		CapsuleComponent->SetCapsuleHalfHeight(FMath::FInterpTo(CapsuleComponent->GetUnscaledCapsuleHalfHeight(), TargetCapsuleSize, DeltaTime, 10.0f), true);
		// Dist and DeltaMovCaps are used for the interpolation value added to RelativeLocation.Z
		const float Dist = TargetCapsuleSize - CapsuleComponent->GetUnscaledCapsuleHalfHeight();
		const float DeltaMovCaps = Dist * FMath::Clamp<float>(DeltaTime * 10.0f, 0.f, 1.f);
		FVector currentCapsuleLocation = CapsuleComponent->GetRelativeLocation();
		CapsuleComponent->SetRelativeLocation(FVector(currentCapsuleLocation.X, currentCapsuleLocation.Y, (currentCapsuleLocation.Z + DeltaMovCaps)), true);
	}
}

void AMyFPCharacter::HorizontalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value * MovementSpeed);
	}
}

void AMyFPCharacter::VerticalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value * MovementSpeed);
	}
}

void AMyFPCharacter::HorizontalRotation(float value)
{
	if (value && !bIsInInventory)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AMyFPCharacter::VerticalRotation(float value)
{
	if (value && !bIsInInventory)
	{
		FRotator currentRotation = cam->GetRelativeRotation();
		currentRotation.Pitch = FMath::Clamp(cam->GetRelativeRotation().Pitch - value, -65, 65);
		cam->SetRelativeRotation(currentRotation);
	}

}

