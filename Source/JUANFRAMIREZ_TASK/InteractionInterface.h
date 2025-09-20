// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractionInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractionInterface : public UInterface {
	GENERATED_BODY()

};

class IInteractionInterface {
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	void OnObstaclePassed(int32 ScoreToAdd);
};
