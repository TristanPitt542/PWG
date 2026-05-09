// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Set Current Health Clamped between 0 and MaxHealth
void UHealth::SetHealth(float Amount)
{
	CurrentHealth = FMath::Clamp(Amount, 0.0f, MaxHealth);
}

// Increase CurrentHealth by Amount
void UHealth::IncreaseHealth(float Amount)
{
	SetHealth(CurrentHealth + Amount);
}

// Decrement CurrentHealth by Amount
void UHealth::DecreaseHealth(float Amount)
{
	SetHealth(CurrentHealth - Amount);

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}

}

void UHealth::Die()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->Destroy();
	}
}
