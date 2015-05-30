// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/WAWUsableItem.h"
#include "WAWMagazine.h"
#include "WAWWeapon.generated.h"

/**
 * 
 */

class AWAWLoadout;

USTRUCT()
struct FWeaponData
{
	GENERATED_BODY()

	/** inifite ammo for reloads */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteAmmo;

	/** infinite ammo in Mag, no reload required */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		bool bInfiniteMag;

	/** should this weapon be put back to safe upon reload? good for grenades */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		bool bGoToSafeOnReload;

	/** max ammo */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 MaxAmmo;

	/** Mag size */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 AmmoPerMag;

	/** initial Mags */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 InitialMags;

	/** time between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float TimeBetweenShots;

	/** failsafe equip duration if weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float NoAnimEquipDuration;

	/** failsafe reload duration if weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float NoAnimReloadDuration;

	/** minimum recoil amount in degrees to move player's pitch */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float RecoilPitchMin;

	/** maximum recoil amount in degrees to move player's pitch */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float RecoilPitchMax;

	/** minimum recoil amount in degrees to move player's yaw */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float RecoilYawMin;

	/** maximum recoil amount in degrees to move player's yaw */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
		float RecoilYawMax;

	/** defaults */
	FWeaponData()
	{
		bInfiniteAmmo = false;
		bInfiniteMag = false;
		bGoToSafeOnReload = false;
		MaxAmmo = 100;
		AmmoPerMag = 20;
		InitialMags = 4;
		TimeBetweenShots = 0.1f; //200 ms between shots => 300 rounds per minute
		NoAnimEquipDuration = 0.5f;
		NoAnimReloadDuration = 1.0f;
		RecoilPitchMin = 0.5f;
		RecoilPitchMax = 2.f;
		RecoilYawMin = -1.f;
		RecoilYawMax = 1.f;
	}
};

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
		void BurstFire(uint8 RoundsToFire);

	UFUNCTION(BlueprintCallable, Category = Gun)
		void CycleFireMode(); //needs a server equivalent

	bool CanFire();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Gun)
		uint8 shotsInMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
		TArray<EFireMode> fireModes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gun)
		TSubclassOf<AWAWMagazine> magazineType;

	TArray<int8> magazineAmmoCounts;

};
