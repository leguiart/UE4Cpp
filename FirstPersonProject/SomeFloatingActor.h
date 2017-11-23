// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SomeFloatingActor.generated.h"

UCLASS()
class FIRSTPERSONPROJECT_API ASomeFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASomeFloatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Movement for actor")
		float GetVel();
	UFUNCTION(BlueprintCallable, Category = "Movement for actor")
		float GetDir();
	UFUNCTION(BlueprintCallable, Category = "Movement for actor")
		float DistanceFromPlayer(FVector Location);
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

private:
	bool flag = true;
};
