// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetMessages.h"
#include "MainHUD.generated.h"

class UPlayerWidget;

/**
 * 
 */
UCLASS()
class JUANFRAMIREZ_TASK_API AMainHUD : public AHUD, public IWidgetMessages
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;


public:

protected:

	virtual void BeginPlay() override;

	void OnScoreChanged_Implementation(int32 ScoreToAdd) override;
	
};
