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
	int32 controller_id;

	void Setup(uint32 id) {
		this->controller_id = id;
	};
};
