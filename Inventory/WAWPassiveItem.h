// Copyright 2015. Black Sand Studios. All Rights Reserved.

#pragma once
#include "WAWEquippableItem.h"
#include "WAWPassiveItem.generated.h"

/**
 * This class seems pretty pointless to be honest - Can't see any functionality that is specifically related to passive items
 */
UCLASS()
class AWAWPassiveItem : public AWAWEquippableItem
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(EditDefaultsOnly, Category = Defaults)
		USoundBase* PassiveSound;
	
	
};
