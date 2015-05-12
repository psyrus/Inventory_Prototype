// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
//#include "WAWLoadout.h"
#include "WAWWeapon.h"
#include "Engine.h"

AWAWWeapon::AWAWWeapon(const FObjectInitializer& ObjectInitializer) : Super( ObjectInitializer)
{

}

void AWAWWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CurrentMagazine = GetWorld()->SpawnActor<AWAWMagazine>(AWAWMagazine::StaticClass());
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Magazine has shots remaining:"));
}

void AWAWWeapon::Fire()
{

	if (CurrentMagazine->IsEmpty() == false)
	{
		CurrentMagazine->DecrementAmmo(1);
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, TEXT("Pushed!!"));
		//int x = CurrentMagazine->GetCurrentAmmo();
	}
}

void AWAWWeapon::BurstFire(int RoundsToFire)//I figured you won't always have 3 round burst
{
	if (CurrentMagazine->IsEmpty() == false)
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

