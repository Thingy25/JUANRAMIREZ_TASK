// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/TextBlock.h"

void UPlayerWidget::AddUIScore(int32 ScoreToAdd) {

	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(ScoreToAdd));
	}
}

