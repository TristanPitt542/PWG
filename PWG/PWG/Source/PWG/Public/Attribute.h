// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attribute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class PWG_API UAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttribute();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	float AttributeCurrent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	float AttributeMax = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	float AttributeRegen = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetAttribute(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void IncreaseAttribute(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void DecreaseAttribute(float Amount);

	UFUNCTION(BlueprintNativeEvent, Category = "Attribute")
	void OnZeroReached();
};
