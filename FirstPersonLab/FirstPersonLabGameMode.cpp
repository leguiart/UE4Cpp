// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonLabGameMode.h"
#include "FirstPersonLabHUD.h"
#include "FirstPersonLabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonLabGameMode::AFirstPersonLabGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonLabHUD::StaticClass();
}
