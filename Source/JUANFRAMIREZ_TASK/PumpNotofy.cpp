// Fill out your copyright notice in the Description page of Project Settings.


#include "PumpNotofy.h"
#include "JUANFRAMIREZ_TASKCharacter.h"

void UPumpNotofy::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	

	AActor* Owner = MeshComp->GetOwner();
	if (AJUANFRAMIREZ_TASKCharacter* Player = Cast<AJUANFRAMIREZ_TASKCharacter>(Owner))
	{
		Player->ApplyPump();
	}
}

