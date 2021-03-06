// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonProject.h"
#include "FirstPersonProjectGameMode.h"
#include "FirstPersonProjectHUD.h"
#include "FirstPersonProjectCharacter.h"

AFirstPersonProjectGameMode::AFirstPersonProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonProjectHUD::StaticClass();
}
