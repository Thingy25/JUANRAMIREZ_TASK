// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "PlayerWidget.h"


void AMainHUD::BeginPlay() {


	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}

void AMainHUD::UpdateScore(int32 ScoreToAdd) {

	PlayerWidget->AddUIScore(ScoreToAdd);
}

