// Copyright 2015. Black Sand Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "WAWCharacter.h"
#include "WAWLoadout.generated.h"

/**
 * 
 * Need to do some research about component registration 
 * https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Actors/Components/index.html#registeringcomponents
 */

/**
* Things I need to understand better:
* - When should I be initializing the various components?
* (eg: The class int/fname variables go in the constructor or PostInitProperties?)
* (eg: The AWAWWeapons are initialized in PostInitializeComponents? -> Should I be doing that CreateDefaultSubObject for every sub object in the constructor?)
*
* When should I be using the TSubclassOf versus just straight pointers to sub components? 
**/

class AWAWEquippableItem;
class AWAWArmorComponent;
class AWAWWeapon;
class AWAWMagazine;

USTRUCT(BlueprintType)
struct FMagazineType
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	FName MagazineName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	AWAWWeapon* AssociatedWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	int8 AssociatedSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	uint8 NumMagazines;
	uint8 UsedMagazines;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	TSubclassOf<AWAWMagazine> DefaultMagClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MagazineStruct)
	TArray<AWAWMagazine*> Magazines;
	FMagazineType()
	{
		MagazineName = TEXT("None");
		AssociatedSlot = -1;
		AssociatedWeapon = nullptr;
		NumMagazines = 5;
		UsedMagazines = 0;
		DefaultMagClass = nullptr;
	}
};

UCLASS()
class AWAWLoadout : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	/** used to set the default display name */
	virtual void PostInitProperties() override;

	/** perform initial setup */
	virtual void PostInitializeComponents() override;

	/** The function to call a selected item's Equip() function*/
	UFUNCTION(BlueprintCallable, Category=Kit)
		void EquipItem(int32 ItemIndex) const;

	/** The physical representation of the kit when it is dropped in the world*/
	UPROPERTY(EditAnywhere, Category = Kit)
		USkeletalMeshComponent* PhysicalMesh;

	/*The base 0-9 Inventory that will be in the kit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Contents)
		//TArray<AWAWEquippableItem*> EquipmentList;
		TArray<TSubclassOf<AWAWEquippableItem>> EquipmentList;
	
	/*The armor that is associated with this kit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Contents)
		TArray<AWAWArmorComponent*> ArmorList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Contents)
		TArray<FMagazineType> MagazineList;

	/** This function will be used to create physical kit bags on the ground*/
	UFUNCTION(BlueprintCallable, Category=Kit)
		void Physicalize();

	/** Return the current owner of the loadout (actually the owner of the inventory controller, but to avoid a circular dependency we set it here too)*/
	UFUNCTION(BlueprintCallable, Category = Kit)
		AWAWCharacter* GetOwningPawn();

	/** Receives the owning pawn character from the InventoryController. Used to attach items to the pawn.*/
	UFUNCTION(BlueprintCallable, Category = Kit)
		void SetOwner(AWAWCharacter* NewOwner);

	/** Return the magazine index of the current weapon */
	int const GetCurrentMagazineIndex() { return CurrentMagazineIndex; }

	/** Returns the next full magazine from the pool of magazines related to our currently equipped weapon*/
	AWAWMagazine* GetNextMagazine(bool IsRoundChambered);

	/** Remove the kit from the world*/
	void Destroy();

	/** Add this loudout to a character - This will need to be modified to apply to vehicles as well*/
	UFUNCTION(BlueprintCallable, Category = Kit)
		void AssignToCharacter(AWAWCharacter* NewOwner);

	UFUNCTION(BlueprintCallable, Category = Kit)
		void CycleItems();

protected:
	/** The pawn that owns the inventorycontroller that controls this loadout.*/
	UPROPERTY(EditDefaultsOnly, Category=Defaults)
	class AWAWCharacter* OwningCharacter;

	/** An identifier to quickly access the magazines related to the currently equipped weapon*/
	int CurrentMagazineIndex;

	/** An identifier for which item is currently being used, so it can be easily referenced */
	int CurrentItemIndex;

	/** Use this as the actual inventory, that way it doesn't need the subclassof except for the initial spawning*/
	UPROPERTY(BlueprintReadWrite, Category = Contents)
		TArray<AWAWEquippableItem*> Inventory;
};
