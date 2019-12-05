// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaTimeSlowAbility.h"
#include "UObject/UObjectBase.h"
#include "Engine/World.h"
#include "Components/DecalComponent.h"
#include "Camera/CameraComponent.h"
#include "TopDownARPG.h"
#include "TopDownARPG/TopDownARPGCharacter.h"
#include "TopDownARPG/Triggers/TimeDilationSphere.h"
//#include "Components/DecalComponent.h"

void UAreaTimeSlowAbility::Activate(AActor* Source)
{
	Super::Activate(Source);

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate IsValid(World) == false"));
		return;
	}

	ATopDownARPGCharacter* RPGCharacter = Cast<ATopDownARPGCharacter>(Source);
	if (!IsValid(RPGCharacter))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate(Source): Source is not a valid ATopDownARPGCharacter"));
		return;
	}

	// get cursor position and spawn sphere there

	UDecalComponent* CursorToWorldComponent = RPGCharacter->GetCursorToWorld();
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
	UCameraComponent* ActorTopDownCameraComponent = RPGCharacter->GetTopDownCameraComponent();
	FVector StartLocation = ActorTopDownCameraComponent->GetComponentLocation();
	FVector EndLocation = ActorTopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
	Params.AddIgnoredActor(RPGCharacter);
	World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
	
	FVector SpawnLocation = HitResult.Location;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Source; // only the owner of the sphere does not suffer its effect

	ATimeDilationSphere* Sphere = World->SpawnActor<ATimeDilationSphere>(ATimeDilationSphere::StaticClass(), SpawnLocation, Source->GetActorRotation(), SpawnParameters);
	if (!IsValid(Sphere))
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("UAreaTimeSlowAbility::Activate Could not spawn valid sphere."));
	}
}