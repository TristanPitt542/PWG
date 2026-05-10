// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute.h"

// Sets default values for this component's properties
UAttribute::UAttribute()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAttribute::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IncreaseAttribute(AttributeRegen * DeltaTime);
}

// Set Current Attribute Clamped between 0 and AttributeMax
void UAttribute::SetAttribute(float Amount)
{
	AttributeCurrent = FMath::Clamp(Amount, 0.0f, AttributeMax);
}

// Increase AttributeCurrent by Amount
void UAttribute::IncreaseAttribute(float Amount)
{
	SetAttribute(AttributeCurrent + Amount);
}

// Decrement AttributeCurrent by Amount
void UAttribute::DecreaseAttribute(float Amount)
{
	SetAttribute(AttributeCurrent - Amount);

	if (AttributeCurrent <= 0.0f)
	{
		OnZeroReached();
	}

}

void UAttribute::OnZeroReached_Implementation()
{
}
