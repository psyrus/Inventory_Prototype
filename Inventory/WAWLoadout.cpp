// Copyright 2015. Black Sand Studios. All Rights Reserved.

#include "Inventory_Prototype.h"
#include "WAWWeapon.h"
#include "WAWLoadout.h"
#include "Engine.h"

AWAWLoadout::AWAWLoadout(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	PhysicalMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("PhysicalMesh"));
	PhysicalMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	PhysicalMesh->bChartDistanceFactor = true; /////////////////
	PhysicalMesh->CastShadow = true;
	PhysicalMesh->bReceivesDecals = true;
	PhysicalMesh->SetOnlyOwnerSee(false);

	
	PhysicalMesh->SetVisibility(false);
	RootComponent = PhysicalMesh;
	FMagazineType GunMags;
	MagazineList.Add(GunMags);
}

void AWAWLoadout::PostInitProperties()
{
	Super::PostInitProperties();
	CurrentMagazineIndex = -1;
}

void AWAWLoadout::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	/* Spawn all of the equipment items that are in the equipment lists*/
	for (TSubclassOf<AWAWEquippableItem> Item : EquipmentList)
	{
		if (Item)
		{
			GetWorld()->SpawnActor<AWAWEquippableItem>(Item);
		}
	}

	/* Spawn magazines for the guns*/
	for (int32 iter = 0; iter < MagazineList.Num(); ++iter)
	{
		//AWAWWeapon* EditWeapon = Cast<AWAWWeapon>(EquipmentList[MagazineList[iter].AssociatedSlot]);
		//EditWeapon->MagazineListIndex = iter;
	}


}

void AWAWLoadout::Physicalize()
{
	bool bIdentifierChosen = false;
	for (int32 iter = 0; iter < EquipmentList.Num() && !bIdentifierChosen; iter++)
	{
		AWAWWeapon* TempWeaponCheck = Cast<AWAWWeapon>(EquipmentList[iter]);
		if (EquipmentList[iter] && TempWeaponCheck != NULL)
		{
			if (TempWeaponCheck->Mesh->IsVisible())
			{
				PhysicalMesh = TempWeaponCheck->Mesh;
				bIdentifierChosen = true;
			}
		}
		
	}
	if (PhysicalMesh == NULL || bIdentifierChosen == false)
	{
		PhysicalMesh = GetOwningPawn()->GetMesh();
	}
	PhysicalMesh->SetVisibility(true);
	this->DetachRootComponentFromParent(false);
	SetOwner(NULL);
	return;
}

void AWAWLoadout::Destroy()
{
	return;
}


/** Return the current owner of the loadout (actually the owner of the inventory controller, but to avoid a circular dependency we set it here too)*/
AWAWCharacter* AWAWLoadout::GetOwningPawn()
{
	return OwningCharacter;
}

/** Receives the owning pawn character from the InventoryController. Used to attach items to the pawn.*/
void AWAWLoadout::SetOwner(AWAWCharacter* NewOwner)
{
	if (NewOwner)
	{
		OwningCharacter = NewOwner;
		AssignToCharacter(OwningCharacter);
		//OwningCharacter->InputComponent->BindAction("CycleWeapon", IE_Pressed, OwningCharacter->_getUObject(), &AWAWLoadout::CycleItems);
	}
	return;
}

void AWAWLoadout::EquipItem(int32 ItemIndex) const
{
	/**Stuff about the item's classification */

	/** */

	/** Stuff about Animations/sounds */

	//Play Equip Sound

	//Play Equip Animation

	/** Miscellaneous housekeeping stuff */
}

void AWAWLoadout::AssignToCharacter(AWAWCharacter* NewOwner)
{
	PhysicalMesh->SetVisibility(false);
	AttachRootComponentToActor(NewOwner);

}

AWAWMagazine* AWAWLoadout::GetNextMagazine(bool IsRoundChambered)
{
	AWAWMagazine* ReturnMag = MagazineList[CurrentMagazineIndex].Magazines[MagazineList[CurrentMagazineIndex].UsedMagazines];
	MagazineList[CurrentMagazineIndex].UsedMagazines++;
	if (IsRoundChambered)
	{
		ReturnMag->AddChamberedRound();
	}
	return ReturnMag;
}

void AWAWLoadout::CycleItems()
{
	//Not sure if mod is expensive, if it is, replace with an if block
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, (FString("The index of the new item is: %s"), FString::FromInt(CurrentItemIndex)));
}

