// Fill out your copyright notice in the Description page of Project Settings.

#include "Dientes.h"


// Sets default values
ADientes::ADientes()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADientes::TriggerHandle()
{
	trigger = true;
}

void ADientes::OnEndOverlapTriggerHandle()
{
	trigger = false;
}
// Called when the game starts or when spawned
void ADientes::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADientes::Tick(float DeltaTime)
{
	if (trigger)
	{
		Super::Tick(DeltaTime);
		FVector Location = GetActorLocation();
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
		RunningTime += DeltaTime;
		SetActorLocation(Location);
	}
}

