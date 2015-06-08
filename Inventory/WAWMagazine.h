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
	
		
protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
			int8 Capacity;

		int8 CurrentAmmo;
		bool bIsFull;
		bool bIsEmpty;
public:
		//Accessor Functions
		UFUNCTION(BlueprintCallable, Category = "Ammo")
		int8 GetCurrentAmmo();
		UFUNCTION(BlueprintCallable, Category = "Ammo")
		int8 GetCapacity();
		UFUNCTION(BlueprintCallable, Category = "Ammo")
		bool IsEmpty();
		UFUNCTION(BlueprintCallable, Category = "Ammo")
		bool IsFull();
		UFUNCTION(BlueprintCallable, Category = "Ammo")
			void Refill();
		UFUNCTION(BlueprintCallable, Category = "Ammo")
			void LoadAmmo(uint8 NumShots);


		UFUNCTION(BlueprintCallable, Category = "Ammo")
		void AddChamberedRound();
		void DecrementAmmo(int8 Amount);
};