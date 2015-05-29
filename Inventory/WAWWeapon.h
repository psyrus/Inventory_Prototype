// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/WAWUsableItem.h"
#include "WAWMagazine.h"
#include "WAWWeapon.generated.h"

/**
 * 
 */

class AWAWLoadout;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFireMode : uint8
{
	VE_Single 	UMETA(DisplayName = "Single Shot"),
	VE_3_Burst 	UMETA(DisplayName = "3 Round Burst"),
	VE_Auto		UMETA(DisplayName = "Automatic Fire")
};

UCLASS()
class AWAWWeapon : public AWAWUsableItem
{
	GENERATED_BODY()

public:
	AWAWWeapon(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = Gun)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Gun)
	void Reload();

	UFUNCTION(BlueprintCallable, Category = Gun)
	void BurstFire(int8 RoundsToFire);

	bool CanFire();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Gun)
	uint8 shotsInMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
	TArray<EFireMode> fireModes;
	

};
