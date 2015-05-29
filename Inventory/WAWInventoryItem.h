
// Copyright 2014 Black Sand Studio. All Rights Reserved.

#pragma once

//#include "WAWLoadout.h"
#include "WAWInventoryItem.generated.h"


UCLASS(Abstract, Blueprintable)
class AWAWInventoryItem : public AActor /**Done CPP**/
{
	GENERATED_UCLASS_BODY()
	
public:
	/** animation played on pawn */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage* PawnAnimation;

	/** Handle some state issues and rotation lag of the item in 1st person mode */
	virtual void Tick(float DeltaTime) override; /**Done CPP**/

	/** used to set the default display name */
	virtual void PostInitProperties() override; /**Done CPP**/

	/** So we can keep a reference to which inventory controller owns this inventory item*/
	//AWAWLoadout* OwningLoadout;
	
	/** returns the item's owning inventory controller */
	//UFUNCTION(BlueprintCallable, Category = Inventory)
		//AWAWLoadout* GetOwningLoadout(); /**Done CPP**/

	/** set the item's/weapon's owning inventory controller */
	//UFUNCTION(BlueprintCallable, Category = Inventory)
	//	void SetOwningLoadout(AWAWLoadout* NewOwner); /**Done CPP**/

	UFUNCTION()
		UAudioComponent* PlayItemSound(USoundBase* Sound);
	/** play item/weapon sounds ***********************************************************Confusing... Is it a function or a component? Why is it returning an audiocomponent?**********/
	

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh;

	/** get item/weapon mesh (needs pawn owner to determine variant) */
	USkeletalMeshComponent* GetItemMesh(); /**Done CPP**/

	virtual void Destroyed() override; /**Done CPP**/

	/** Human readable localized name for the item. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
		FText DisplayName;

	/** [server] item/weapon was added to pawn's inventory */
	//virtual void OnEnterInventory(AWAWLoadout* NewLoadout); /**Done CPP**/

	/** [server] item/weapon was removed from pawn's inventory */
	virtual void OnLeaveInventory(); /**Done CPP**/

	/*Below two functions seem to be related to the above two - Needs research/reading*/
	//virtual void GivenTo(AWAWCharacter* NewOwner, bool bAutoActivate);

	//virtual void Removed();

	/** if set, item is always dropped when its holder dies if uses/charges/etc remain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		bool bAlwaysDropOnDeath;

	/** HUD icon for e.g. inventory item bar */
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Icon)
		FCanvasIcon HUDIcon;*/

	/** perform initial setup */
	virtual void PostInitializeComponents() override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;
	
};
