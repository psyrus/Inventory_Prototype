// Copyright 2014 Black Sand Studio. All Rights Reserved.
#pragma once
#include "Inventory_Prototype/WAWCharacter.h"
#include "WAWInventoryItem.h"
#include "WAWEquippableItem.generated.h"

UCLASS(Abstract, Blueprintable)
class AWAWEquippableItem : public AWAWInventoryItem
{
	GENERATED_UCLASS_BODY()

public:

	/** attaches weapon mesh to pawn's mesh */
	virtual void AttachMeshToPawn(); /**CPP DONE**/

	/** detaches weapon mesh from pawn */
	virtual void DetachMeshFromPawn(); /**CPP DONE**/

	/** check if mesh is already attached */
	virtual bool IsAttachedToPawn(); /**CPP DONE**/

	/** check if item/weapon is currently equipped */
	virtual bool IsEquipped(); /**CPP DONE**/

	virtual void DropFrom(const FVector& StartLocation, const FVector& TossVelocity); /**CPP DONE**/

	/** stop playing item/weapon animations */
	void StopAnimation(UAnimMontage* Animation); /**CPP DONE**/

	/** equip/bring up the item/weapon */
	virtual void OnEquip(); /**CPP DONE**/

	/** item/weapon is now equipped by owner pawn */
	virtual void OnEquipFinished(); /**CPP DONE**/

	/** socket or bone name for attaching weapon mesh */
	UPROPERTY(BlueprintReadWrite, Category = Inventory)
		FName ItemAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timings)
		float EquipTime; /************************************Seems to duplicate a protected variable below*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UAnimMontage* EquipAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		USoundBase* EquipSound;

	/** unequip/put down the item/weapon */
	virtual void OnUnEquip(); /**CPP DONE**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timings)
		float UnEquipTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		UAnimMontage* UnEquipAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		USoundBase* UnEquipSound;

	UPROPERTY(BlueprintReadWrite, Category=Sound)
		USoundBase* EquippedSound;
	/** gets last time when this weapon was switched to */

	/**This one is strange, gotta figure out if it's useful*/
	float GetEquipStartedTime();

	/** Gets the duration of equipping weapon*/
	float GetEquipDuration(); /**CPP DONE**/

	/** if set, inventory gets the ModifyDamageTaken() functions/events when the holder takes damage */
	UPROPERTY(EditDefaultsOnly, Category = Events)
		uint8 bCallDamageEvents : 1;

	/** if set, receive OwnerEvent() calls for various holder events (jump, land, fire, etc) */
	UPROPERTY(EditDefaultsOnly, Category = Events)
		uint32 bCallOwnerEvent : 1;

	//UFUNCTION(BlueprintNativeEvent)
	//	void ModifyDamageTaken(int32& Damage, FVector& Momentum, AWAWArmorComponent*& HitItem, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser);

	/** when a character takes damage that is reduced by inventory, the inventory item is included in the hit info and this	function is called for all clients on the inventory DEFAULT OBJECT
	* used to play item/shield/armor effects
	* @return whether an effect was played
	*/
//	UFUNCTION(BlueprintNativeEvent)
//		bool PlayHitEffects(AWAWCharacter* HitPawn) const; /**********************Why is it a BOOL?*/

	//UFUNCTION(BlueprintNativeEvent)
	//	void OwnerEvent(FName EventName); /**********************What is an owner event?*/

	virtual void Tick(float DeltaTime) override;
protected:

	/** is item/weapon currently equipped? */
	uint32 bIsEquipped : 1;

	/** Lag a component of item/weapon rotation behind player's rotation. */
	virtual float LagItemRotation(float NewValue, float LastValue, float DeltaTime, float MaxDiff, int Index); /**CPP DONE**/

	/** is equip animation playing? */
	uint32 bPendingEquip : 1;

	/** last time when this item/weapon was switched to */
	float EquipStartedTime;

	/** how much time item/weapon needs to be equipped */
	float EquipDuration;

	/** failsafe equip duration if item/weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = Timings)
		float NoAnimEquipDuration;

	/** failsafe reload duration if item/weapon doesn't have any animation for it */
	UPROPERTY(EditDefaultsOnly, Category = Timings)
		float NoAnimReloadDuration;

	/** Previous frame's item/weapon rotation */
	UPROPERTY(BlueprintReadOnly, Category=Item_State)
	FRotator LastRotation;

	/** Saved values used for lagging item/weapon rotation */
	UPROPERTY()
		float OldRotDiff[2];
	UPROPERTY()
		float OldLeadMag[2];
	UPROPERTY()
		float OldMaxDiff[2];

	/** How fast item/weapon Rotation offsets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Rotation")
		float RotChgSpeed;

	/** How fast item/weapon Rotation returns */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Rotation")
		float ReturnChgSpeed;

	/** Max item/weapon rotation Yaw offset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Rotation")
		float MaxYawLag;

	/** Max item/weapon rotation Pitch offset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Rotation")
		float MaxPitchLag;

	/** @return whether the item's/weapon's rotation is allowed to lag behind the holder's rotation */
	virtual bool ShouldLagRot() { return true; }
};
