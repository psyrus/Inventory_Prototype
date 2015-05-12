// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/WAWUsableItem.h"
#include "WAWMagazine.h"
#include "WAWWeapon.generated.h"

/**
 * 
 */

class AWAWLoadout;

UCLASS()
class AWAWWeapon : public AWAWUsableItem
{
	GENERATED_BODY()

public:
	AWAWWeapon(const FObjectInitializer& ObjectInitializer);
	int CurrentMagazineCount;//how many the weapon has left

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category=Misc)
	void Fire();

	void Reload();
	void BurstFire(int RoundsToFire);
	int GetMaximumMagazines();
	int GetCurrentMagazineCount();
	void SetCurrentMagazineCount(int Magazines);//Can I use "Amount" for this even though it was used before, for DecrementAmmo(Amount)?

	int MagazineListIndex;
	AWAWMagazine* CurrentMagazine;
	//TSubclassOf<AWAWMagazine> CurrentMagazine;

};
