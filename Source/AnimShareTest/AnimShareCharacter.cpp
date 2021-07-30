// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimShareCharacter.h"

// Sets default values
AAnimShareCharacter::AAnimShareCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AAnimShareCharacter::GetCurrentSignificance()
{
	USignificanceManager* SignificanceMgr = FSignificanceManagerModule::Get(GetWorld());
	return SignificanceMgr->GetSignificance(this);
}

// Called when the game starts or when spawned
void AAnimShareCharacter::BeginPlay()
{
	if(!IsNetMode(NM_DedicatedServer))
	{
		UWorld* MyWorld = GetWorld();
		USignificanceManager* SignificanceMgr = FSignificanceManagerModule::Get(MyWorld);
		if(SignificanceMgr)
		{
			auto SignificanceFunc = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint) -> float 
			{
				return SignificanceFunction(ObjectInfo, Viewpoint);
			};

			auto PostSignificanceFunc = [&](USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal) 
			{
				PostSignificanceFunction(ObjectInfo, OldSignificance, Significance, bFinal);
			};

			SignificanceMgr->RegisterObject(this, "AnimShareCharacter", SignificanceFunc, USignificanceManager::EPostSignificanceType::Sequential, PostSignificanceFunc);
		}

		UAnimationSharingManager* AnimShareManager = UAnimationSharingManager::GetAnimationSharingManager(MyWorld);
		if (AnimShareManager == nullptr)
		{
			UAnimationSharingManager::CreateAnimationSharingManager(MyWorld, ShareSetup);
		}

		UAnimationSharingManager::GetAnimationSharingManager(MyWorld)->RegisterActorWithSkeleton(this, GetMesh()->SkeletalMesh->Skeleton, FUpdateActorHandle::CreateUObject(this, &AAnimShareCharacter::UpdateAnimShareHandle));
	}
	
	//IMPORTANT: if this super:BeginPlay execute in the first line in this function , there will be a problem that the BeginPlay in blueprint execute first, 
	// for we usually Register the actor to AnimSharePlugin  in blueprint,  this will result we can not get the significance value in the register
	Super::BeginPlay();
}

void AAnimShareCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!IsNetMode(NM_DedicatedServer))
	{
		UWorld* MyWorld = GetWorld();
		USignificanceManager* SignificanceMgr = FSignificanceManagerModule::Get(MyWorld);
		SignificanceMgr->UnregisterObject(this);
	}
	

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAnimShareCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimShareCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAnimShareCharacter::SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint)
{
	if(ObjectInfo->GetTag() == TEXT("AnimShareCharacter"))
	{
		AAnimShareCharacter* Charcter = CastChecked<AAnimShareCharacter>(ObjectInfo->GetObject());
		const float Distance = (Charcter->GetActorLocation() - Viewpoint.GetLocation()).Size();

		UAnimationSharingManager* AnimShareManager = UAnimationSharingManager::GetAnimationSharingManager(GetWorld());
		float Significance = GetSignificanceByDistance(Distance);
		AnimShareManager->UpdateSignificanceForActorHandle(AnimShareHandle, Significance);
		return Significance;
		
	}
	return 0.f;
}

void AAnimShareCharacter::PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal)
{
	if(ObjectInfo->GetTag() == TEXT("AnimShareCharacter"))
	{
		AAnimShareCharacter* Charcter = CastChecked<AAnimShareCharacter>(ObjectInfo->GetObject());
		//if (Significance == 0.f)
		//{

		//}
		//else
		//{

		//}
	}
}

float AAnimShareCharacter::GetSignificanceByDistance(float Distance)
{
	const int32 NumSettings = SignificanceThreholdsSetting.Num();
	if(Distance >= SignificanceThreholdsSetting[NumSettings - 1].MaxDistance)
	{
		return SignificanceThreholdsSetting[NumSettings - 1].Significance;
	}
	else 
	{
		for(int32 Idx = 0; Idx < NumSettings; Idx ++)
		{
			FSignificanceSettings& Setting = SignificanceThreholdsSetting[Idx];
			if(Distance < Setting.MaxDistance)
			{
				return Setting.Significance;
			}
		}
	}

	return 0.f;
}

void AAnimShareCharacter::UpdateAnimShareHandle(int32 Handle)
{
	AnimShareHandle = Handle;
}

