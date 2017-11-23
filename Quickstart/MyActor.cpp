// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"

// Sets default values (constructor method)
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;

	//here is another equivalent way
	/*
	AMyActor::AMyActor() :
	TotalDamage(200),
	DamageTimeInSeconds(1.0f)
	{
	}
	*/
}


// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

//In order to just modify values and properties of an instance of the class set by the designer
//we wish to just modify the values of the object, in order to do that we should add a new method
// to the class specifically named: PostInitProperties() as follows
void AMyActor::PostInitProperties()
{
	Super::PostInitProperties();
	CalculateValue();
	CalculateAngle();
}


//Function to calculate property specified by designer's settings, instead of rewriting
void AMyActor::CalculateValue()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AMyActor::CalculateAngle()
{
	alpha = asin(vectZ / Module(vectX, vectY, vectZ))*180.0f / pi;
	beta = atan2(vectY, vectX)* 180.0f / pi;
}
//UE4 automatically recognizes a PostEditChangeProperty type method declaration
//What this method does is to enable the UE4 editor to reflect the changes 
//on a calculated property, what the engine does is generate an edition event
//handled by the following function each time the designer sets or modifies 
//the properties, this has to be done, since runtime changes on the UE4 editor
//are not accounted for automatically
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CalculateValue();
	if (vectX > 1.0f)
		vectX = 1.0f;
	else if (vectY > 1.0f)
		vectY = 1.0f;
	else if (vectZ > 1.0f)
		vectZ = 1.0f;

	if (vectX < -1.0f)
		vectX = -1.0f;
	else if (vectY < -1.0f)
		vectY = -1.0f;
	else if (vectZ < -1.0f)
		vectZ = -1.0f;

	CalculateAngle();
}

float AMyActor::Module(float x, float y, float z)
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//This version of the function is called when the blueprint in question fails to override the function
void AMyActor::CalledFromCpp_Implementation()
{
	CalculateAngle();
	NewLocation.Z += vel*sin(alpha*pi / 180) - RunningTime*9.81;
	NewLocation.Y += vel*cos(alpha*pi / 180)*sin(beta*pi / 180);
	NewLocation.X += vel*cos(alpha*pi / 180)*cos(beta*pi / 180);
	SetActorLocation(NewLocation);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NewLocation = GetActorLocation();
	RunningTime += DeltaTime;
	CalledFromCpp_Implementation();
}

