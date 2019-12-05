// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "TimeDilationSphere.generated.h"

UCLASS()
class TOPDOWNARPG_API ATimeDilationSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimeDilationSphere();

	const int SphereRadius = 30;
	const float AbnormalTimeDilation = .1f;

protected:
	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	USphereComponent* SphereComponent;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
