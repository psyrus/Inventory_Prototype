// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Inventory_Prototype.h"
#include "Inventory_PrototypeGameMode.h"
#include "Inventory_PrototypeCharacter.h"

AInventory_PrototypeGameMode::AInventory_PrototypeGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
