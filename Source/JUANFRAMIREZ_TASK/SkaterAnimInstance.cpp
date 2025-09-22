// Fill out your copyright notice in the Description page of Project Settings.


#include "SkaterAnimInstance.h"
#include "JUANFRAMIREZ_TASKCharacter.h"

void USkaterAnimInstance::NativeNotify(const FAnimNotifyEvent& NotifyEvent) {
	if (NotifyEvent.NotifyName == FName("PumpNotify"))
	{
		if (AJUANFRAMIREZ_TASKCharacter* Character = Cast<AJUANFRAMIREZ_TASKCharacter>(TryGetPawnOwner()))
		{

		}
	}
}

