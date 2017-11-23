// Fill out your copyright notice in the Description page of Project Settings.


#include "SomeFloatingCharacter.h"


// Sets default values
ASomeFloatingCharacter::ASomeFloatingCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASomeFloatingCharacter::BeginPlay()
{
	Super::BeginPlay();
	flag = false;
	phi = 0;
}

float ASomeFloatingCharacter::Module(FVector A)
{
	return FMath::Sqrt((FMath::Pow(A.X, 2) + FMath::Pow(A.Y, 2) + FMath::Pow(A.Z, 2)));
}

float ASomeFloatingCharacter::DotProduct(FVector V1, FVector V2)
{
	return V1.X*V2.X + V1.Y*V2.Y + V1.Z*V2.Z;
}

float ASomeFloatingCharacter::Module2D(FVector A)
{
	return FMath::Sqrt((FMath::Pow(A.X, 2) + FMath::Pow(A.Y, 2)));
}

float ASomeFloatingCharacter::DotProduct2D(FVector V1, FVector V2)
{
	return V1.X*V2.X + V1.Y*V2.Y;
}

float ASomeFloatingCharacter::Distance(FVector A, FVector B)
{
	return FMath::Sqrt(FMath::Pow((A.X - B.X), 2) + FMath::Pow((A.Y - B.Y), 2) + FMath::Pow((A.Z - B.Z), 2));
}

void ASomeFloatingCharacter::GetForwardVectorFromBlueprint(FVector AForwardVector)
{
	FirstPersonForwardVector = AForwardVector;
}

void ASomeFloatingCharacter::GetUpVectorFromBlueprint(FVector AUpVector)
{
	FirstPersonUpVector = AUpVector;
}

void ASomeFloatingCharacter::GetRightVectorFromBlueprint(FVector ARightVector)
{
	FirstPersonRightVector = ARightVector;
}

// Called every frame
void ASomeFloatingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight, DeltaWidth, DeltaDepth;
	if (dist <= 500.0f) flag = true;
	if (flag)
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

		NewLocation.X += DeltaDepth * xScale;
		NewLocation.Y += DeltaWidth * yScale;
		NewLocation.Z += DeltaHeight * zScale;  

		RunningTime += DeltaTime;
		SetActorLocation(NewLocation);
	}
}

float ASomeFloatingCharacter::GetVel()
{
	//float vel = FMath::Sqrt(FMath::Pow(xScale, 2) + FMath::Pow(yScale, 2) + FMath::Pow(zScale, 2));
	//UE_LOG(LogTemp, Warning, TEXT("Velocity is:  %f"), vel);
	if (flag)
	{
		return FMath::Sqrt(FMath::Pow(xScale, 2) + FMath::Pow(yScale, 2) + FMath::Pow(zScale, 2));
	}
	else
	{
		return 0.0f;
	}
}


float ASomeFloatingCharacter::GetDir()
{
	//float dir = FMath::Atan2(yScale, xScale)*180.0f / PI;
	//UE_LOG(LogTemp, Warning, TEXT("Direction is:  %f"), dir);
	if (flag)
	{
		return FMath::Atan2(yScale, xScale)*180.0f / PI;
	}
	{
		return 0.0f;
	}
}

float ASomeFloatingCharacter::DistanceFromPlayer(FVector Location)
{
	FVector ActorLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FRotator ActorRotation = GetActorRotation();
	angle = FMath::Atan2((Location.Y - ActorLocation.Y), (Location.X - ActorLocation.X));
	//phi = FMath::Abs(DotProduct2D(GetActorRightVector(), FirstPersonRightVector)) / (Module(GetActorRightVector())*Module(FirstPersonRightVector));
	dist = Distance(Location, ActorLocation);

	if (flag)
	{
		xScale = vel * FMath::Cos(angle);
		yScale = vel * FMath::Sin(angle);
		//if (!FVector::Coplanar(ActorLocation, GetActorRightVector(), Location, FirstPersonRightVector, 0.9f))
		//{
			//SetActorRotation(ActorRotation);
			//ActorRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		//}
		//else
		//{
			ForwardVector = GetActorForwardVector();
			ForwardVector.FVector::GetSafeNormal2D(0.01f);
			ForwardVector *= dist;
			Direction = FVector(Location.X - ActorLocation.X, Location.Y - ActorLocation.Y, 0.0f);
			ActorRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			SetActorRotation(ActorRotation);
		//}
	}
	return dist;
}