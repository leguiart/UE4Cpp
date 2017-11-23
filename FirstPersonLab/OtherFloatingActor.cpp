// Fill out your copyright notice in the Description page of Project Settings.

#include "OtherFloatingActor.h"


// Sets default values
AOtherFloatingActor::AOtherFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOtherFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOtherFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight, DeltaWidth, DeltaDepth;

	if (spiral == false)
	{

		if (frenet == true)
		{
			DeltaHeight = RunningTime + DeltaTime;
			DeltaWidth = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
			DeltaDepth = (FMath::Cos(RunningTime + DeltaTime) - FMath::Cos(RunningTime));
		}
		else if (line == true)
		{
			DeltaHeight = RunningTime + DeltaTime;
			DeltaWidth = DeltaHeight;
			DeltaDepth = DeltaHeight;
		}
		else
		{
			DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
			DeltaWidth = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
			DeltaDepth = (FMath::Cos(RunningTime + DeltaTime) - FMath::Cos(RunningTime));
		}

	}
	else
	{
		if (velX == velY)
		{
			DeltaHeight = (FMath::Sin(RunningTime*velZ + DeltaTime) - FMath::Sin(RunningTime));
			DeltaWidth = (FMath::Cos(RunningTime*velY + DeltaTime) - FMath::Cos(RunningTime));
			DeltaDepth = (FMath::Sin(RunningTime*velX + DeltaTime) - FMath::Sin(RunningTime));
		}
		else
		{
			DeltaHeight = (FMath::Sin(RunningTime*velZ + DeltaTime) - FMath::Sin(RunningTime));
			DeltaWidth = (FMath::Sin(RunningTime*velY + DeltaTime) - FMath::Sin(RunningTime));
			DeltaDepth = (FMath::Cos(RunningTime*velX + DeltaTime) - FMath::Cos(RunningTime));
		}
	}
	NewLocation.X += DeltaDepth * xScale;
	NewLocation.Y += DeltaWidth * yScale;
	NewLocation.Z += DeltaHeight * zScale;       //Scale our height by a factor 

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

float AOtherFloatingActor::GetVel()
{
	return FMath::Sqrt(FMath::Pow(xScale, 2) + FMath::Pow(yScale, 2) + FMath::Pow(zScale, 2));
}

float AOtherFloatingActor::GetDir()
{
	return FMath::Atan2(yScale, xScale)*180.0f / PI;
}
