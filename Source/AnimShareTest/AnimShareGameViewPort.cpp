// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimShareGameViewPort.h"
#include "SignificanceManager.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

UAnimShareGameViewPort::UAnimShareGameViewPort(const FObjectInitializer& ObjectInittializer)
:Super(ObjectInittializer)
{
	
}

void UAnimShareGameViewPort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* MyWorld = GetWorld();
	if(MyWorld != nullptr)
	{
		const bool bHasValidData = CachedPlayerController.IsValid();
		if(!bHasValidData)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(MyWorld, 0);
			CachedPlayerController = TWeakObjectPtr<class APlayerController>(PC);
		}

		if(bHasValidData)
		{
			USignificanceManager* SignificanceManager = FSignificanceManagerModule::Get(MyWorld);

			FVector ViewLoc;
			FRotator ViewRot;
			CachedPlayerController.Get()->GetPlayerViewPoint(ViewLoc, ViewRot);


			TArray<FTransform> Viewpoints;
			Viewpoints.Emplace(FTransform(ViewRot, ViewLoc, FVector::OneVector));
			SignificanceManager->Update(Viewpoints);
		}
	}
}
