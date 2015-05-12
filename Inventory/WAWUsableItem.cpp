// Copyright 2015. Black Sand Studios. All Rights Reserved.

#include "Inventory_Prototype.h"
#include "WAWUsableItem.h"


AWAWUsableItem::AWAWUsableItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void AWAWUsableItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AWAWUsableItem::PostInitProperties()
{
	Super::PostInitProperties();

	NumberRemaining = NumberCarried;
}

uint8 AWAWUsableItem::GetRemainingNumber()
{
	return NumberRemaining;
}
/*
void AWAWUsableItem::Destroyed()
{
	Super::Destroyed();

}

void AWAWUsableItem::Tick(float DeltaTime)
{

}
*/