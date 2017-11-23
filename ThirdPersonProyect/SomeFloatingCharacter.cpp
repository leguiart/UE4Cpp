// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProyect.h"
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
	//phi = 0;
	moveFlag = true;
	bTimerExpired = true;
	PlayAttack = false;
	PlayBash = false;
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


// Called every frame
void ASomeFloatingCharacter::Tick(float DeltaTime)
{
	UWorld* World = GetWorld();
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	ForwardVector.FVector::GetSafeNormal2D(0.01f);
	float DeltaHeight, DeltaWidth, DeltaDepth;

	if (dist <= rDetection) flag = true;

	if (dist <= rAttack) PlayAttack = true;
	else PlayAttack = false;

	if (dist <= 80.0f) PlayBash = true;
	else PlayBash = false;

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
			if ((SampleTimerHandle.IsValid() == false) || (bTimerExpired) || (PlayAttack))
			{
				World->GetTimerManager().SetTimer(SampleTimerHandle, this, &ASomeFloatingCharacter::SampleTimerExpired, 1.0f);
				if (moveFlag)
					moveFlag = false;
				else
					moveFlag = true;
				bTimerExpired = false;
			}

			if (moveFlag && (!PlayAttack) && (!PlayBash) )
			{
				DeltaHeight = RunningTime + DeltaTime;
				DeltaWidth = DeltaHeight;
				DeltaDepth = DeltaHeight;
			}
			else
			{
				DeltaHeight = 0.0f;
				DeltaWidth = DeltaHeight;
				DeltaDepth = DeltaHeight;
			}

		}
		else
		{
			DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
			DeltaWidth = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
			DeltaDepth = (FMath::Cos(RunningTime + DeltaTime) - FMath::Cos(RunningTime));
		}
		//xScale = vel * FMath::Cos(angle);
		//yScale = vel * FMath::Sin(angle);
		xScale = vel * ForwardVector.X;
		yScale = vel * ForwardVector.Y;
		RunningTime += DeltaTime;
		SetActorLocation(FMath::Lerp(NewLocation, FVector(NewLocation.X + DeltaDepth * xScale, NewLocation.Y + DeltaWidth * yScale, NewLocation.Z + DeltaHeight * zScale), GetVel()));
	}
}

void ASomeFloatingCharacter::SampleTimerExpired()
{
	bTimerExpired = true;
}

bool ASomeFloatingCharacter::GetPlayAttackStatus()
{
	return PlayAttack;
}

bool ASomeFloatingCharacter::GetPlayBashStatus()
{
	return PlayBash;
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
	//FVector ForwardVector = GetActorForwardVector();
	angle = FMath::Atan2((Location.Y - ActorLocation.Y), (Location.X - ActorLocation.X));
	//phi = FMath::Abs(DotProduct2D(GetActorRightVector(), FirstPersonRightVector)) / (Module(GetActorRightVector())*Module(FirstPersonRightVector));
	dist = Distance(Location, ActorLocation);

	if (flag)
	{
		//if (!FVector::Coplanar(ActorLocation, GetActorRightVector(), Location, FirstPersonRightVector, 0.9f))
		//{
		//SetActorRotation(ActorRotation);
		//ActorRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		//}
		//else
		//{
		//ForwardVector = GetActorForwardVector();
		//ForwardVector.FVector::GetSafeNormal2D(0.01f);
		//ForwardVector *= dist;
		Direction = FVector(Location.X - ActorLocation.X, Location.Y - ActorLocation.Y, 0.0f);
		FRotator ActorRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), ActorRotation, GetWorld()->GetDeltaSeconds(), GetVel()));
		//}
	}
	return dist;
}