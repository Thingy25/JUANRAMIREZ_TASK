// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PumpNotofy.generated.h"

/**
 * 
 */
UCLASS()
class JUANFRAMIREZ_TASK_API UPumpNotofy : public UAnimNotify
{
	GENERATED_BODY()

private:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
	
};
