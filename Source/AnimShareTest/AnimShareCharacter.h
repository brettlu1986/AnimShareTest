// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SignificanceManager.h"
#include "AnimationSharingManager.h"
#include "AnimationSharingSetup.h"
#include "AnimShareCharacter.generated.h"


USTRUCT(BlueprintType)
struct FSignificanceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Significance")
	float Significance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Significance")
	float MaxDistance = 0.f;
};

UCLASS()
class ANIMSHARETEST_API AAnimShareCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimShareCharacter();

	UFUNCTION(BlueprintCallable, Category = "Character Significance")
	float GetCurrentSignificance();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetSignificanceByDistance(float Distance);
	void UpdateAnimShareHandle(int32 Handle);

	float SignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, const FTransform& Viewpoint);
	void PostSignificanceFunction(USignificanceManager::FManagedObjectInfo* ObjectInfo, float OldSignificance, float Significance, bool bFinal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Significance")
	TArray<FSignificanceSettings> SignificanceThreholdsSetting;

	UPROPERTY(EditAnywhere, Category = "Character Significance")
	UAnimationSharingSetup* ShareSetup;

	int32 AnimShareHandle;
	
};
