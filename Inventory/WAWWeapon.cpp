// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
//#include "WAWLoadout.h"
#include "WAWWeapon.h"
#include "Engine.h"

AWAWWeapon::AWAWWeapon(const FObjectInitializer& ObjectInitializer) : Super( ObjectInitializer)
{
	shotsInMagazine = 1;
}

void AWAWWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Magazine has shots remaining:"));
}

bool AWAWWeapon::CanFire()
{
	bool canFire = true;

	//Insert all conditions for being unable to fire here
	if (shotsInMagazine > 0)
		canFire = false;

	return canFire;
}

void AWAWWeapon::Fire()
{
	if (CanFire())
	{
		//Spawn projectile

		//Spawn effects

		//Decrement ammo
		shotsInMagazine -= 1;
	}
	else
	{
		//Play empty shot sound (maybe networked, maybe not)
	}
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("Fired!!"));
}

void AWAWWeapon::BurstFire(uint8 RoundsToFire)//I figured you won't always have 3 round burst
{
	if (canFire())
	{
		if (CurrentMagazine->GetCurrentAmmo() >= RoundsToFire)
		{
			CurrentMagazine->DecrementAmmo(RoundsToFire);
		}
		else
		{
			CurrentMagazine->DecrementAmmo(CurrentMagazine->GetCurrentAmmo());//if you have less rounds left than the burst mode, fire remaining rounds
		}
	}
}

void AWAWWeapon::Reload()
{
	//Don't reload if the magazine is still full
	if (!CurrentMagazine->IsFull())
	{
		/** */

		/** Stuff about playing animations & sounds - Can depend on if a round is chambered or not*/

		//Get the next magazine, if the current magazine is empty, a round is not chambered. 
		//CurrentMagazine = Cast<AWAWLoadout>(OwningLoadout)->GetNextMagazine(!(CurrentMagazine->IsEmpty()));
	}

}

