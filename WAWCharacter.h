// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory_PrototypeCharacter.h"
#include "WAWCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AWAWCharacter : public AInventory_PrototypeCharacter
{
public:
	GENERATED_BODY()

	AWAWCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents();

	UFUNCTION(BlueprintCallable, Category = Attachments)
	bool IsValidAttachmentPoint(FName PointToCheck);

	UFUNCTION(BlueprintCallable, Category=Attachments)
	void AttachItem(class AWAWEquippableItem* Item, FName AttachmentPoint);

	UFUNCTION(BlueprintCallable, Category = Attachments)
	class AWAWLoadout* GetLoadout();

	UFUNCTION(BlueprintCallable, Category = Attachments)
	void CheckLoadout();

protected:

	/** For now we will handle the input to the loadout in the character, but ideally it should be in the PC */

	/** OVerride input function */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void dummyFunc();

	UPROPERTY(BlueprintReadWrite, Category=Defaults)
	class AWAWWeapon* PrimaryWeapon; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TSubclassOf<AWAWLoadout> Loadout;

};
