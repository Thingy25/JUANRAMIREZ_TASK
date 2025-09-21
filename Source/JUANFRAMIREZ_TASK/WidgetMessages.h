// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetMessages.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UWidgetMessages : public UInterface {
	GENERATED_BODY()

};

class IWidgetMessages{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	void OnScoreChanged(int32 ScoreToAdd);
};
