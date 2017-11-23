// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Math.h>
#include "MyActor.generated.h"


#define  pi 3.14159265

UCLASS()
class  AMyActor : public AActor
{
	GENERATED_BODY()
		//declaring class and its methods

public:
	//Use the categorization feature of UPROPERTY() macro
	//UPROPERTY(EditAnywhere, Category = "Damage") int32 TotalDamage; 

	/*Use the blueprint specific parameter to make a property available
	for read/write to a blueprint: BlueprintReadWrite*/

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	/*Use BlueprintReadOnly, Blueprint specific parameter to set that
	this property can only be read by Blueprints, but not modified*/

	//Property to control total amount of damage dealt to the actor deals out
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		int32 TotalDamage;

	//Property the designer can modify
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float DamageTimeInSeconds;

	/*Property calculated using the designer's settings
	VisibleAnywhere flag marks the property as viewable, but not editable
	in the Unreal editor
	Transient flag means the property won't be saved or loaded from disk
	instead, it is a derived non-persistent value*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
		float DamagePerSecond;

	//Modify initial velocity scalar
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parabol")  float vel = 1.0f;

	//Modify the direction of the initial velocity vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parabol") float vectX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parabol") float vectY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parabol") float vectZ;

	//Alpha and Beta angles of the initial velocity vector
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Parabol")
		float alpha;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Parabol")
		float beta;
	// Sets default values for this actor's properties
	AMyActor();
	void PostInitProperties();
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	//Placing the macro UFUNCTION, we are able to expose the function to
	//the editor. BlueprintCallable option exposes the function to the
	//Blueprint Virtual Machine, every function exposed requires a category
	//associated to it, now the function is callable from the blueprint editor
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void CalculateValue();
	/*//BlueprintImplementableEvent option allows C++ code to call functions defined in blueprints
	//If there is no function named that way in blueprints then the function is just empty
	//This option allows us to call a blueprint function but we cannot modify it via C++ implementation
	UFUNCTION(BlueprintImplementableEvent, Category = "Damage")
	void CalledFromCpp();*/

	//What if we still want to provide a default C++ implementation while still allowing a Blueprint to override the method?
	//UFUNCTION macro has an option for that too:
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")
		void CalledFromCpp();

	// Called every frame with the time elapsed since last call passed in
	virtual void Tick(float DeltaSeconds) override;

	float RunningTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Module(float x, float y, float z);
	void CalculateAngle();
	FVector NewLocation;
};