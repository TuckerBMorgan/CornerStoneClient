// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HandController.h"
#include "Card.h"
#include "BattleGameState.generated.h"

/**
 * 
 */
UCLASS()
class CLIENTCORNERSTONE_API ABattleGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controllers)
	TArray<UHandController*> HandControllers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameMode)
    int32 Hello;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cards)
	TMap<int32, UCard*> CardInstances;
	

	void AddHandController(UHandController* HandController) {
		HandControllers.Add(HandController);
	}

	void AddCardInstanceToGame(UCard* CardInstance) {
		CardInstances.Add(CardInstance->GetUniqueId(), CardInstance);
	}

	UHandController* GetHandController(int32 ControllerId) {
		return this->HandControllers[ControllerId];
	}
};
