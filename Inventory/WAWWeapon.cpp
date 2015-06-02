// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
//#include "WAWLoadout.h"
#include "WAWWeapon.h"
#include "Engine.h"

AWAWWeapon::AWAWWeapon(const FObjectInitializer& ObjectInitializer) : Super( ObjectInitializer)
{
	CurrentMagazineIndex = 0;
}

void AWAWWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Magazine has shots remaining:"));
	CurrentMagazine = GetWorld()->SpawnActor<AWAWMagazine>(MagazineClass);

	for (uint8 i = 0; i < MagazineAmmoCounts.Num(); i++)
	{
		MagazineAmmoCounts.Add(CurrentMagazine->GetCapacity());
	}
}

bool AWAWWeapon::CanFire()
{
	bool CanFire = true;

	//Insert all conditions for being unable to fire here
	if (AmmoInMagazine <= 0)
		CanFire = false;

	return CanFire;
}

void AWAWWeapon::Fire()
{
	if (CanFire())
	{
		//Spawn projectile

		//Spawn effects

		//Decrement ammo
		AmmoInMagazine -= 1;
	}
	else
	{
		//Play empty shot sound (maybe networked, maybe not)
	}
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("Fired!!"));
}

/** Fire consecutive shots in one trigger pull. */
void AWAWWeapon::BurstFire(uint8 RoundsToFire)//I figured you won't always have 3 round burst
{
	if (CanFire())
	{
		/* If we decide to just call the fire() method in a loop, this block is pretty useless, we should
		 * just determine which is lower, AmmoInMagazine or RoundsToFire and fire that many times, so it just needs
		 * a single loop block 
		 */
		if (AmmoInMagazine >= RoundsToFire)
		{
			//Should we just call the fire method (RoundsToFire) times? 
			//For efficiency's sake (lowering the function call stack) we could implement the firing functionality again here.
		}
		{
			//if you have less rounds left than the burst mode, fire remaining rounds
			//In this one call the fire function AmmoRemaining times
			for (int fireIter = 1; fireIter < AmmoInMagazine; ++fireIter)
			{
				Fire();
			}
			
		}
	}
}

void AWAWWeapon::Reload()
{
	//Don't reload if the magazine is still full
	//AWAWMagazine* Magazine = Cast<AWAWMagazine>(CurrentMagazine);
	if (!CurrentMagazine->IsFull())
	{
		/** */
		CurrentMagazine->Refill();

		/** Stuff about playing animations & sounds - Can depend on if a round is chambered or not*/

		//Get the next magazine, if the current magazine is empty, a round is not chambered. 
		//CurrentMagazine = Cast<AWAWLoadout>(OwningLoadout)->GetNextMagazine(!(CurrentMagazine->IsEmpty()));
	}

}

