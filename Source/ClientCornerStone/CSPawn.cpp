// Fill out your copyright notice in the Description page of Project Settings.


#include "CSPawn.h"

// Sets default values
ACSPawn::ACSPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACSPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

