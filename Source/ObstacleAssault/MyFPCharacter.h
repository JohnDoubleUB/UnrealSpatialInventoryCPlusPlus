// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"
#include "InteractorComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "MyFPCharacter.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMyFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyFPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float WalkingSpeed = 0.5;
	UPROPERTY(EditAnywhere)
	float CrouchingSpeed = 0.25;

	UPROPERTY(EditAnywhere)
	float RunningSpeed = 1;

	UPROPERTY(VisibleAnywhere)
	float MovementSpeed = 0.5;
	UPROPERTY(EditAnywhere)
	float WalkingBobbingSpeed = 14.0f;

	UPROPERTY(EditAnywhere)
	float WalkingSwaySpeed = 7.0f;

	UPROPERTY(EditAnywhere)
	float BobbingAmount = 6.0f;

	UPROPERTY(EditAnywhere)
	float SwayAmount = 1.5f;

	UPROPERTY(EditAnywhere)
	USoundCue* FootstepSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	class UPlayerHUD* PlayerHUD;

	//Inputs
	void HorizontalMovement(float value);
	void VerticalMovement(float value);

	void HorizontalRotation(float value);
	void VerticalRotation(float value);

	void Crouch();
	void Jump();
	void Interact(const bool& pressed);
	void ToggleInventory();

	void Sprint(const bool& sprint);

	bool SetCrouch(const bool& crouch);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInventoryEnabled(bool enabled);

private: 

	bool CanUnCrouch();

	FVector CameraBob(const float& DeltaTime, const bool& falling);

	void HandleFootstep(const FVector& currentPosition, const bool& isFalling);
	void HandleCrouch(const float& DeltaTime);
	
	void PlayFootstep();
	void PlayFootLand();

	void OnInteractionChange(bool interaction, FString* name = nullptr);

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* cam;
	UCharacterMovementComponent* CharacterMovement;
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInteractorComponent* InteractorComponent;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	FVector CurrentVelocity;

	float BobTimer;
	float SwayTimer;

	float DefaultCameraZPos;
	float DefaultCameraRoll;

	float UncrouchTraceRadius;

	bool bStepTaken;
	bool bWasInAir;
	bool bIsCrouching;
	bool bIsSprinting;
	bool bIsInInventory;
};
