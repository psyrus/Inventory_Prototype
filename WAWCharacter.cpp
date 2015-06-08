// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory_Prototype.h"
#include "WAWCharacter.h"
#include "Inventory/WAWLoadout.h"
#include "Inventory/WAWEquippableItem.h"
#include "Inventory/WAWWeapon.h"

AWAWCharacter::AWAWCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AWAWCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CheckLoadout();
	//SpawnLoadout = GetWorld()->SpawnActor<AWAWLoadout>(AWAWLoadout::StaticClass());
	//SpawnLoadout->SetOwner(this);


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
	Kit = GetWorld()->SpawnActor<AWAWLoadout>(SpawnLoadout);
	AWAWEquippableItem* CurrentItem = Kit->GetCurrentItem();
	
	if (CurrentItem->IsA<AWAWWeapon>())
	{
		AWAWWeapon* temp = Cast<AWAWWeapon>(CurrentItem);
		FString x = temp->DisplayAmmoCounts();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *x);
	}
}

void AWAWCharacter::dummyFunc()
{
	//AWAWLoadout* SpawnLoadout = GetWorld()->SpawnActor<AWAWLoadout>(AWAWLoadout::StaticClass());
}
