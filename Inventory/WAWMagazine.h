// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/WAWEquippableItem.h"
#include "WAWMagazine.generated.h"

/**
 * 
 */
UCLASS()
class AWAWMagazine : public AWAWEquippableItem
{
	GENERATED_BODY()

		AWAWMagazine(const FObjectInitializer& ObjectInitializer);
		int Capacity;
		int CurrentAmmo;
		bool bIsFull;
		bool bIsEmpty;
		FText DisplayName;
public:
		//Accessor Functions
		int GetCurrentAmmo();
		int GetCapacity();
		bool IsEmpty();
		bool IsFull();

		void AddChamberedRound();
		void DecrementAmmo(int Amount);
};