// Fill out your copyright notice in the Description page of Project Settings.
#include "Dientes.h"



// Sets default values
ADientes::ADientes()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADientes::BeginPlay()
{
	Super::BeginPlay();
	if (random)
	{
		//A limit for the movement
		LimitCounter = rand() % 5 + 1;
		//Movement scale
		zScale = 0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 9.9f));
		//Velocity of movement
		DeltaHeight = 0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.9f));
	}
}

// OnBeginOverlap Trigger Handler
void ADientes::OnBeginOverlapTriggerHandle()
{
	animate = true;
}

// OnEndOverlap Trigger Handler
void ADientes::OnEndOverlapTriggerHandle()
{
	animate = false;
}

// Called every frame
void ADientes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = GetActorLocation();
	if(animate)
	{
		counter++;
		if (acc)
		{
			if (up)
			{
				DeltaHeight = RunningTime + DeltaTime;
				if (counter >= LimitCounter)
				{
					counter = 0;
					up = false;
				}
				Location.Z += DeltaHeight * zScale;
			}
			else
			{
				DeltaHeight = RunningTime - DeltaTime;
				if (counter >= LimitCounter)
				{
					counter = 0;
					up = true;
				}
				Location.Z -= DeltaHeight * zScale;
			}
		}
		else
		{
			if (up)
			{
				if (counter >= LimitCounter)
				{
					counter = 0;
					up = false;
				}
				Location.Z += DeltaHeight * zScale;
			}
			else
			{
				if (counter >= LimitCounter)
				{
					counter = 0;
					up = true;
				}
				Location.Z -= DeltaHeight * zScale;
			}
		}
	}
	RunningTime += DeltaTime;
	SetActorLocation(Location);
}
