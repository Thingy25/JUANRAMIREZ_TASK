// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InteractionInterface.h"
#include "ScoreManager.h"
#include "JUANFRAMIREZ_TASKCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AJUANFRAMIREZ_TASKCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PumpAction;



public:
	AJUANFRAMIREZ_TASKCharacter();

	virtual void Tick(float DeltaTime) override;
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
	float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
	float CurrentYawSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
	float MaxYawSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement variables")
	float YawAcceleration;

	float CurrentSpeed;       
	float PumpImpulse;       
	float MaxSpeed;           
	float Friction;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Pump(const FInputActionValue& Value);

	void AlignToGround();
			

protected:

	virtual void NotifyControllerChanged() override;

	virtual void OnObstaclePassed_Implementation(int32 ScoreToAdd) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Skatebrd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UScoreManager* ScoreManager;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }	
};

