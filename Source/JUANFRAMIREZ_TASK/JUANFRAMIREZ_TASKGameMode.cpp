// Copyright Epic Games, Inc. All Rights Reserved.

#include "JUANFRAMIREZ_TASKGameMode.h"
#include "JUANFRAMIREZ_TASKCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJUANFRAMIREZ_TASKGameMode::AJUANFRAMIREZ_TASKGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
