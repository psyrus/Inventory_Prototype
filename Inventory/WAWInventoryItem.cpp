// Copyright 2014 Black Sand Studio. All Rights Reserved.
/*************Notes******************/
// On enter/leave inventory - The server vs client handling nneeds to defined
//Lifetime replicate function needs update
//PlayItemSound function seems senseless unless other sound functions are gonna call it

#include "Inventory_Prototype.h"
#include "WAWInventoryItem.h"
//#include "WAWLoadout.h"

AWAWInventoryItem::AWAWInventoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Set up the tick updates and replication
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	SetReplicates(true);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;


	
	//Create our third person perspective of our item/weapon
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ItemMesh"));
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh->bChartDistanceFactor = true; /////////////////
	Mesh->CastShadow = true;
	Mesh->bReceivesDecals = true;
	Mesh->SetOnlyOwnerSee(false);
	RootComponent = Mesh;
	//Disable all collisions but respond to ECC_Visibility, Weapons, and Projectiles
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
//	Mesh->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
//	Mesh->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	//The third person item/weapon mesh is the child of the first person item/weapon mesh

	//OwningLoadout = ObjectInitializer.CreateDefaultSubobject<AWAWLoadout>(this, "OwningLoadout");
	// default inventory item icon texture
	//static ConstructorHelpers::FObjectFinder<UTexture> ItemTexture(TEXT("Texture2D'/Game/UI/HUD/UI_HUD_BaseB.UI_HUD_BaseB'"));
//	HUDIcon.Texture = ItemTexture.Object;

	bAlwaysDropOnDeath = false;
	DisplayName = NSLOCTEXT("PickupMessage", "InventoryItemPickedUp", "InventoryItem");

	
}

void AWAWInventoryItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWAWInventoryItem::PostInitProperties()
{
	Super::PostInitProperties();

	//Existing function to set the name of the item based on the class name
	if (DisplayName.IsEmpty() || (GetClass() != AWAWInventoryItem::StaticClass() && DisplayName.EqualTo(GetClass() ->GetSuperClass()->GetDefaultObject<AWAWInventoryItem>()->DisplayName)))
	{
		DisplayName = FText::FromName(GetClass()->GetFName());
	}
}

void AWAWInventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AWAWInventoryItem, AWAWLoadout);
	//DOREPLIFETIME_CONDITION(AWAWInventoryItem, CurrentState, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(AWAWInventoryItem, bPendingReload, COND_SkipOwner);
}

void AWAWInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/*AWAWLoadout* AWAWInventoryItem::GetOwningLoadout()
{
	if (OwningLoadout)
	{
		return Cast<AWAWLoadout>(OwningLoadout);
	}
	else
	{
		return NULL;
	}
}*/

/*void AWAWInventoryItem::SetOwningLoadout(AWAWLoadout* NewLoadout)
{
	if (NewLoadout)
	{
//		Instigator = NewOwner;
		OwningLoadout = NewLoadout;
		SetOwner(Cast<AWAWLoadout>(NewLoadout)); // Don't know what this does <- turns out it's an unreal actor function: https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/SetOwner/index.html
	}
	
	
}*/

/**Plays a sound sent to it by one of the other functions - Not sure if it's necessary but we could have more specialized functions (weapon fire sound etc) that could call this one**/
UAudioComponent* AWAWInventoryItem::PlayItemSound(USoundBase* Sound)
{
	UAudioComponent* AC;
	if (Sound->IsPlayable())
	{
		AC = UGameplayStatics::PlaySoundAttached(Sound, RootComponent, NAME_None);
	}
	else
	{
		AC = NULL;
	}
	return AC;
}

USkeletalMeshComponent* AWAWInventoryItem::GetItemMesh()
{
	if (Mesh)
	{
		return Mesh;
	}
	else
	{
		return NULL;
	}
}

void AWAWInventoryItem::Destroyed()
{
	/**Code to remove it from the inventory*/
	//OwningLoadout->RemoveItem(this);
//	TRACE("Removing item %s from inventory (%s)", this, OwningLoadout);
	Super::Destroyed();
}

//Called to add this weapon to the Pawn's inventory
/*void AWAWInventoryItem::OnEnterInventory(AWAWLoadout* NewLoadout)
{
	//Set up the new owner - WHy is this not being done on the server?
	if (NewLoadout)
	{
		SetOwningLoadout(NewLoadout);
	}
}*/

//Called to remove this weapon from the Pawn's inventory
void AWAWInventoryItem::OnLeaveInventory()
{
	//Only allow the server to handle this
	if (Role == ROLE_Authority)
	{
		//Remove the current owner
		//SetOwningLoadout(NULL);
	}

}

