// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "AnimShareGameViewPort.generated.h"

/**
 * 
 */
UCLASS()
class ANIMSHARETEST_API UAnimShareGameViewPort : public UGameViewportClient
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	TWeakObjectPtr<class APlayerController> CachedPlayerController;
};
