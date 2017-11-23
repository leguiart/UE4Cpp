// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SomeActor.generated.h"

UCLASS()
class THIRDPERSONPROYECT_API ASomeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASomeActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetVel();

	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	float RunningTime;
	//Choose between curved movement or purely orbital movement
	UPROPERTY(EditAnywhere) bool spiral = false;
	//Choose to make z grow 
	UPROPERTY(EditAnywhere) bool frenet = false;
	//Choose to produce linear movement
	UPROPERTY(EditAnywhere) bool line = false;
	//Modify scale of movement in 3D (x,y,z)
	UPROPERTY(EditAnywhere) float xScale;
	UPROPERTY(EditAnywhere) float yScale;
	UPROPERTY(EditAnywhere) float zScale;
	//Modify velocity
	UPROPERTY(EditAnywhere) float velZ = 1.0f;
	UPROPERTY(EditAnywhere) float velY = 1.0f;
	UPROPERTY(EditAnywhere) float velX = 1.0f;
	
	
};
