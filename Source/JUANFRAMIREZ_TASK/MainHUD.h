// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UPlayerWidget;

/**
 * 
 */
UCLASS()
class JUANFRAMIREZ_TASK_API AMainHUD : public AHUD
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;


public:

	void UpdateScore(int32 ScoreToAdd);

protected:

	virtual void BeginPlay() override;
	
};
