// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
#include "WAWCharacter.h"
#include "Inventory/WAWLoadout.h"

AWAWCharacter::AWAWCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AWAWCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CheckLoadout();
	//Loadout = GetWorld()->SpawnActor<AWAWLoadout>(AWAWLoadout::StaticClass());
	//Loadout->SetOwner(this);


	//PrimaryWeapon = (AWAWWeapon*)GetWorld()->SpawnActor(AWAWWeapon::StaticClass());
	//PrimaryWeapon->SetOwner(this);
	
}

void AWAWCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	//Set up the bindings for the loadout
	InputComponent->BindAction("CycleWeaponsUp", IE_Pressed, this, &AWAWCharacter::CheckLoadout);
}


bool AWAWCharacter::IsValidAttachmentPoint(FName PointToCheck)
{

	return true;
}

void AWAWCharacter::AttachItem(AWAWEquippableItem* Item, FName AttachmentPoint)
{
	return;
}

AWAWLoadout* AWAWCharacter::GetLoadout()
{

	return NULL;

}

void AWAWCharacter::CheckLoadout()
{
	GetWorld()->SpawnActor(Loadout);
}

void AWAWCharacter::dummyFunc()
{
	//AWAWLoadout* Loadout = GetWorld()->SpawnActor<AWAWLoadout>(AWAWLoadout::StaticClass());
}
