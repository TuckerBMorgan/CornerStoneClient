// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HandController.generated.h"

/**
 * 
 */
UCLASS()
class CLIENTCORNERSTONE_API UHandController : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ControllerId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSet<int32> CardIds;


	void Setup(uint32 id) {
		this->ControllerId = id;
	};

	void AddCardToController(uint32 id) {
		this->CardIds.Add(id);
	}
};
