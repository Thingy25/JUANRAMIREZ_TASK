// Copyright Epic Games, Inc. All Rights Reserved.

#include "JUANFRAMIREZ_TASKCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include <Kismet/GameplayStatics.h>
#include "WidgetMessages.h"
#include "GameFramework/HUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AJUANFRAMIREZ_TASKCharacter

AJUANFRAMIREZ_TASKCharacter::AJUANFRAMIREZ_TASKCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Skatebrd = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skateboard"));
	Skatebrd->SetupAttachment(this->GetMesh());

	ScoreManager = CreateDefaultSubobject<UScoreManager>(TEXT("ScoreManager"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	CurrentYawSpeed = 0.f;
	MaxYawSpeed = 160.f; 
	YawAcceleration = 80.f;

	BaseSpeed = 0.5f;
	CurrentSpeed = 17.5f;
	PumpImpulse = 500.f;
	MaxSpeed = 5000.f;
	Friction = 50.f;
	SlowDownRate = 150.f;

}

//////////////////////////////////////////////////////////////////////////
// Input

void AJUANFRAMIREZ_TASKCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector ForwardDir = GetActorForwardVector().GetSafeNormal();
	AddMovementInput(ForwardDir, BaseSpeed * CurrentSpeed);
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + CurrentSpeed;
	CurrentSpeed = FMath::Max(CurrentSpeed - Friction * DeltaTime, 0.f);

	AlignToGround();
}

void AJUANFRAMIREZ_TASKCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AJUANFRAMIREZ_TASKCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AJUANFRAMIREZ_TASKCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJUANFRAMIREZ_TASKCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJUANFRAMIREZ_TASKCharacter::Look);

		EnhancedInputComponent->BindAction(PumpAction, ETriggerEvent::Started, this, &AJUANFRAMIREZ_TASKCharacter::Pump);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AJUANFRAMIREZ_TASKCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();

			float TargetYawSpeed = MovementVector.X * MaxYawSpeed;
			CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, DeltaTime, YawAcceleration);

			FRotator NewRotation = GetActorRotation();
			NewRotation.Yaw += CurrentYawSpeed * DeltaTime;
			SetActorRotation(NewRotation);

			FVector ForwardDir = GetActorForwardVector().GetSafeNormal();

			float InputScale = MovementVector.Y;

			if (MovementVector.Y < 0.f)
			{
				CurrentSpeed += MovementVector.Y * SlowDownRate * DeltaTime;
			}
			if (CurrentSpeed < 0) CurrentSpeed = 0;

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green,
					FString::Printf(TEXT("CurrentSpeed: %.2f"), CurrentSpeed));
			}
		else {
			CurrentSpeed = 0;
		}
	}
}

void AJUANFRAMIREZ_TASKCharacter::Pump(const FInputActionValue& Value) 
{
	if (PumpMontage && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(PumpMontage, 1.75f);
	}
}

void AJUANFRAMIREZ_TASKCharacter::ApplyPump() {

	CurrentSpeed = FMath::Clamp(CurrentSpeed + PumpImpulse, 0.f, MaxSpeed);
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
			FString::Printf(TEXT("CurrentSpeed: %.2f"), CurrentSpeed));
	}*/

}

void AJUANFRAMIREZ_TASKCharacter::Jump(const FInputActionValue& Value)
{
	Super::Jump();
	if (PumpMontage && GetMesh()->GetAnimInstance())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(JumpMontage);
	}
}

void AJUANFRAMIREZ_TASKCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AJUANFRAMIREZ_TASKCharacter::AlignToGround() {
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, 100.f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		FVector GroundNormal = Hit.ImpactNormal;

		FVector Forward = GetActorForwardVector();
		FVector Right = FVector::CrossProduct(GroundNormal, Forward).GetSafeNormal();
		FVector AdjustedForward = FVector::CrossProduct(Right, GroundNormal).GetSafeNormal();

		FRotator TargetRotation = AdjustedForward.Rotation();

		FRotator CurrentRotation = GetActorRotation();
		FRotator SmoothedRotation = CurrentRotation;

		SmoothedRotation.Pitch = FMath::FInterpTo(
			CurrentRotation.Pitch,
			TargetRotation.Pitch,
			GetWorld()->GetDeltaSeconds(),
			5.f
		);

		SmoothedRotation.Roll = FMath::FInterpTo(
			CurrentRotation.Roll,
			TargetRotation.Roll,
			GetWorld()->GetDeltaSeconds(),
			5.f
		);

		SetActorRotation(SmoothedRotation);
	}	
}

void AJUANFRAMIREZ_TASKCharacter::OnObstaclePassed_Implementation(int32 ScoreToAdd) {

	ScoreManager->AddScore(ScoreToAdd);
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		AHUD* HUD = PC->GetHUD();
		if (HUD && HUD->GetClass()->ImplementsInterface(UWidgetMessages::StaticClass()))
		{
			IWidgetMessages::Execute_OnScoreChanged(HUD, ScoreManager->Score);
		}
	}
}
