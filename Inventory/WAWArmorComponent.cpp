// Copyright 2015. Black Sand Studios. All Rights Reserved.

#include "Inventory_Prototype.h"
#include "WAWArmorComponent.h"


void AWAWArmorComponent::PostInitProperties()
{
	Super::PostInitProperties();

	//Set the Current armor to the amount of the base armor

	if (BaseArmor >= 0)
	{
		ArmorAmount = BaseArmor;
	}
}

/**Take the regular damage and reduce it bythe strength of the armor, then return that value*/
uint32 AWAWArmorComponent::ModifyIncomingDamage(uint32 IncomingDamage)
{
	if (ArmorAmount > 0)
	{
		if (IncomingDamage > ArmorStrength)
		{
			IncomingDamage -= ArmorStrength;
			ArmorAmount -= IncomingDamage;			
		}
	}

	return IncomingDamage;
}

/**Repair the armor by the set amount, if it exceeds the maximum armor, set it to the base armor amount*/
void AWAWArmorComponent::RepairArmor(uint32 RepairAmount)
{
	ArmorAmount += RepairAmount;

	if (ArmorAmount > BaseArmor)
	{
		ArmorAmount = BaseArmor;
	}
}

/**Attach the armor component to the given character at the attachpoint*/
void AWAWArmorComponent::AttachTo(AWAWCharacter* Recipient)
{
	if (Recipient)
	{
		if (Recipient->IsValidAttachmentPoint(ItemAttachPoint))
		{
//			Recipient->AttachItem(this, ItemAttachPoint);
		}
	}
}