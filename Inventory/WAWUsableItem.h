// Copyright 2015. Black Sand Studios. All Rights Reserved.

#pragma once

#include "WAWEquippableItem.h"
#include "WAWUsableItem.generated.h"

/**
 * This could be split to have a sub class which is called "consumableItem" which would hold such values as NumRemaining etc.
 * Grenades, Potentially Magazines and healing packs etc would fall under this category
 */
UCLASS()
class AWAWUsableItem : public AWAWEquippableItem
{
	GENERATED_UCLASS_BODY()
public:
	/** perform initial setup */
	virtual void PostInitializeComponents() override;
	virtual void PostInitProperties() override;

	//virtual void Destroyed() override;

	/** Updates the laser pointing location */
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		uint8 GetRemainingNumber();
	
	
protected:

	UPROPERTY(EditAnywhere, Category = Defaults)
		uint8 NumberCarried;

	uint8 NumberRemaining;

};
