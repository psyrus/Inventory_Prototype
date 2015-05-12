// Copyright 2015. Black Sand Studios. All Rights Reserved.

#pragma once

#include "WAWEquippableItem.h"
#include "WAWArmorComponent.generated.h"

/**
 * Should the character or something have a flag to say they are usng armor?
 Would it be better to have an armor controller to handle which takes damage etc, or just let the inentory controller handle it?
 */
UCLASS()
class AWAWArmorComponent : public AWAWEquippableItem
{
	GENERATED_BODY()

public:

		void PostInitProperties();
		
		/**Take the regular damage and reduce it bythe strength of the armor, then return that value*/
		UFUNCTION(BlueprintCallable, Category=Armor)
		uint32 ModifyIncomingDamage(uint32 IncomingDamage);
		
		/**Repair the armor by the set amount, if it exceeds the maximum armor, set it to the base armor amount*/
		UFUNCTION(BlueprintCallable, Category = Armor)
			void RepairArmor(uint32 RepairAmount);

		/**Sound played if the armor is hit*/
		UPROPERTY(EditDefaultsOnly, Category=Defaults)
		USoundBase* ArmorHitSound;

		/**Attach the armor component to the given character at the attachpoint*/
		UFUNCTION()
		void AttachTo(AWAWCharacter* Recipient);

		/**Any special effects that should play if the armor component is hit*/
//		UPROPERTY(EditDefaultsOnly, Category = Defaults)
//		AWAWImpactEffect* ArmorImpactEffects;
	

protected:
	/** Scenecomponent to attach the armor to*/
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
		USceneComponent* RelatedPoint;

	/**How much damage does this armor counteract*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults)
		uint32 ArmorStrength;

	/**How much of this armor exists in this component*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults)
		uint32 BaseArmor;

	/**How much armor remains in this component. When it reaches 0, it will no longer cancel out damage*/
	UPROPERTY(BlueprintReadOnly, Category = Armor)
		uint32 ArmorAmount;
};
