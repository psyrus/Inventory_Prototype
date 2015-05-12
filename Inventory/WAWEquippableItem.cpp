// Copyright 2014 Black Sand Studio. All Rights Reserved.
#include "Inventory_Prototype.h"
#include "WAWEquippableItem.h"
	
AWAWEquippableItem::AWAWEquippableItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AWAWEquippableItem::AttachMeshToPawn()
{
	/*AWAWCharacter* CurrentPawn = Cast<AWAWCharacter>(Cast<AWAWLoadout>(GetOwningLoadout())->GetOwner());

	//Check if the CurrentPawn has an attachPoint that is named the same as EquippableItem's attachpoint
	//Something like:
	if (ItemAttachPoint.IsNone())
	{
		ItemAttachPoint = CurrentPawn->GetRootComponent()->GetAllSocketNames()[0];
	}

	if (CurrentPawn && CurrentPawn->IsValidAttachmentPoint(ItemAttachPoint))
	{
		Mesh->AttachTo(CurrentPawn->GetMesh(), ItemAttachPoint, EAttachLocation::KeepRelativeOffset);
	}
	*/
}

void AWAWEquippableItem::DetachMeshFromPawn()
{
	//AWAWCharacter* CurrentPawn = Cast<AWAWCharacter>(GetOwningInventory()->GetOwner());

	/**
	if(CurrentPawn)
	{
		DetachSceneComponentsFromParent();
	}
	**/
	
}

bool AWAWEquippableItem::IsAttachedToPawn()
{

	return false;

}

bool AWAWEquippableItem::IsEquipped()
{

	return false;
}

void AWAWEquippableItem::DropFrom(const FVector& StartLocation, const FVector& TossVelocity)
{


}

/*void AWAWEquippableItem::StopAnimation(const FInventoryItemAnim& Animation)
{


}*/

void AWAWEquippableItem::OnEquip()
{


}

void AWAWEquippableItem::OnEquipFinished()
{


}

void AWAWEquippableItem::OnUnEquip()
{


}

float AWAWEquippableItem::GetEquipStartedTime()
{

	return EquipStartedTime;
}

float AWAWEquippableItem::GetEquipDuration()
{

	return EquipDuration;
}

/*void AWAWEquippableItem::ModifyDamageTaken(int32& Damage, FVector& Momentum, AWAWArmorComponent*& HitItem, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{

	// If Damagecauser -> InitialMomentum > 0 // DamageCauser isA *projectile
	// Take the Current momentum, compare to initial momentum
	// The damage will be reduced by momentum differential multiplied by the armor status differential (Momentum/DamageCauser->GetInitialMomentum())*(HitItem->GetArmorStatePercent())
	
}*/

/*bool AWAWEquippableItem::PlayHitEffects(AWAWCharacter* HitPawn)
{
	return true; //why is it a bool?
}*/

/*void AWAWEquippableItem::OwnerEvent(FName EventName)
{

}*/

float AWAWEquippableItem::LagItemRotation(float NewValue, float LastValue, float DeltaTime, float MaxDiff, int Index)
{

	return 0.0f;
}

void AWAWEquippableItem::Tick(float DeltaTime)
{
	
	/*//Try to gracefully detect being active with no owner, which should never happen because we should always end up going through Removed() and going to the inactive state
	if (CurrentState != EInventoryItemState::InactiveState && (!WAWPawnOwner || WAWPawnOwner->bPendingKillPending))
	{
		UE_LOG(WAW, Warning, TEXT("%s lost Owner while active (state %d"), *GetName(), *(GetInventoryItemStateEnumAsString(CurrentState)).ToString());
		CurrentState = EInventoryItemState::InactiveState;
	}

	Super::Tick(DeltaTime);

	//Note that this relies on us making BeginPlay() always called before first tick; see UWAWGameEngine::LoadMap()
	if (CurrentState != EInventoryItemState::InactiveState)
	{
		AWAWCharacter* WAWCharacter = Cast<AWAWCharacter>(WAWPawnOwner);
		//If item/weapon is up in first person, view bob with movement
		if (Mesh && WAWCharacter && WAWCharacter->IsLocallyControlled())
		{
			if (FirstPMeshOffset.IsZero())
			{
				FirstPMeshOffset = Mesh->GetRelativeTransform().GetLocation();
				FirstPMeshRotation = Mesh->GetRelativeTransform().Rotator();
			}
			Mesh->SetRelativeLocation(FirstPMeshOffset);
			Mesh->SetWorldLocation(Mesh->GetComponentLocation() + WAWCharacter->GetItemBobOffset(DeltaTime, this));

			FRotator NewRotation = WAWCharacter ? WAWCharacter->GetControlRotation() : FRotator(0.f, 0.f, 0.f);
			FRotator FinalRotation = NewRotation;

			//Add some rotation leading
			if (WAWCharacter && WAWCharacter->Controller)
			{
				FinalRotation.Yaw = LagItemRotation(NewRotation.Yaw, LastRotation.Yaw, DeltaTime, MaxYawLag, 0);
				FinalRotation.Pitch = LagItemRotation(NewRotation.Pitch, LastRotation.Pitch, DeltaTime,

					MaxPitchLag, 1);
				FinalRotation.Roll = NewRotation.Roll;
			}
			LastRotation = NewRotation;
			Mesh3P->SetRelativeRotation(FinalRotation + FirstPMeshRotation);
		}
	}*/
}