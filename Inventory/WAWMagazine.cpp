// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
#include "WAWMagazine.h"
#include "Engine.h"

AWAWMagazine::AWAWMagazine(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Capacity = 30;
	CurrentAmmo = Capacity;
	bIsFull = true;
	bIsEmpty = false;
}

int8 AWAWMagazine::GetCurrentAmmo()
{
	return CurrentAmmo;
}

int8 AWAWMagazine::GetCapacity()
{
	return Capacity;
}

bool AWAWMagazine::IsEmpty()
{
	return bIsEmpty;
}

void AWAWMagazine::Refill()
{

	CurrentAmmo = Capacity;
}

void AWAWMagazine::LoadAmmo(uint8 NumShots)
{
	CurrentAmmo = NumShots;
}

bool AWAWMagazine::IsFull()
{
	return bIsFull;
}

void AWAWMagazine::DecrementAmmo(int8 Amount)
{
	if((CurrentAmmo - Amount) > 0) 
	{
		FString blah = FString::FromInt(CurrentAmmo);
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, (FString("Magazine has %s shots remaining"), blah));
		bIsFull = false;
		CurrentAmmo = CurrentAmmo - Amount;
	}
	else
	{
		bIsEmpty = true;
		CurrentAmmo = 0;
	}
}

void AWAWMagazine::AddChamberedRound()
{
	if (CurrentAmmo <= Capacity)
	{
		CurrentAmmo++;
	}
	else
	{
		/** Throw an error at the log to explain that it has been called incorrectly (when it shouldn't have been, it should never get to this else statement)*/
	}
}