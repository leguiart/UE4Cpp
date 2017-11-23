// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SomeFloatingCharacter.generated.h"

UCLASS()
class FIRSTPERSONLAB_API ASomeFloatingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASomeFloatingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetVel();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetDir();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		float DistanceFromPlayer(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void GetForwardVectorFromBlueprint(FVector AForwardVector);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void GetUpVectorFromBlueprint(FVector AUpVector);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void GetRightVectorFromBlueprint(FVector AUpVector);
	float RunningTime;
	//Choose to make z grow 
	UPROPERTY(EditAnywhere) bool frenet = false;
	//Choose to produce linear movement
	UPROPERTY(EditAnywhere) bool line = false;
	//Modify scale of movement in 3D (x,y,z)
	UPROPERTY(EditAnywhere) float xScale;
	UPROPERTY(EditAnywhere) float yScale;
	UPROPERTY(EditAnywhere) float zScale;

	//Set character velocity
	UPROPERTY(EditAnywhere) float vel;

private:
	bool flag, flag2;
	float angle, dist, phi, theta;
	FVector FirstPersonForwardVector, FirstPersonUpVector, FirstPersonRightVector, ForwardVector, Direction;
	float Module(FVector A);
	float DotProduct(FVector V1, FVector V2);
	float Module2D(FVector A);
	float DotProduct2D(FVector V1, FVector V2);
	float Distance(FVector A, FVector B);
};
