// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

/**
 * 
 */
UCLASS()
class CLIENTCORNERSTONE_API UCard : public UObject
{


	GENERATED_BODY()
public: 
	int CatalogId;
	int UniqueId;
	int Cost;
	int StartingHealth;
	int StartingAttack;


	void Setup(int catalog_id, int unique_id, int cost, int starting_health, int starting_attack) {
		this->CatalogId = catalog_id;
		this->UniqueId = unique_id;
		this->Cost = cost;
		this->StartingHealth = starting_health;
		this->StartingAttack = starting_attack;
	}

	int32 GetUniqueId() {
		return this->UniqueId;
	}
};
