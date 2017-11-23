// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dientes.generated.h"

UCLASS()
class FRAGMENTOSMECHONE_API ADientes : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADientes();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = "trigger") void TriggerHandle();
	UFUNCTION(BlueprintCallable, Category = "trigger") void OnEndOverlapTriggerHandle();

	float RunningTime;
	int counter = 0;
	bool trigger=false;
	//Choose between up or down movement
	UPROPERTY(EditAnywhere) bool up = true;
	//Choose between accelerated or constant velocity movement
	UPROPERTY(EditAnywhere) bool acc = true;
	//A limit for the movement
	UPROPERTY(EditAnywhere) int LimitCounter;
	//Movement scale
	UPROPERTY(EditAnywhere) float zScale;
	//Velocity of movement
	UPROPERTY(EditAnywhere) float DeltaHeight;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
