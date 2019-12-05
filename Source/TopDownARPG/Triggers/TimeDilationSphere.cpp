// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationSphere.h"
#include <Runtime\Engine\Classes\GameFramework\MovementComponent.h>

ATimeDilationSphere::ATimeDilationSphere()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(SphereRadius);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	// TODO: fix collision mode and make it visible

	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATimeDilationSphere::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ATimeDilationSphere::OnEndOverlap);
}

void ATimeDilationSphere::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other != nullptr && Other != this && OtherComp != nullptr && Other != this->GetOwner())
	{
		Other->CustomTimeDilation = AbnormalTimeDilation;
	}
}

void ATimeDilationSphere::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Other != nullptr && Other != this && OtherComp != nullptr && Other != this->GetOwner())
	{
		Other->CustomTimeDilation = 1.f;
	}
}
