// Copyright Epic Games, Inc. All Rights Reserved.


#include "ClientCornerStoneGameModeBase.h"
#include "BattleGameState.h"
#include "HandController.h"
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <mutex>
#include "NmJson.h"
#include "NetworkingThread.h"
#include "CoreMinimal.h"
using json = nlohmann::json;



AClientCornerStoneGameModeBase::AClientCornerStoneGameModeBase() {
    PrimaryActorTick.bStartWithTickEnabled = true;
    PrimaryActorTick.bCanEverTick = true;
}

void AClientCornerStoneGameModeBase::InitGame

(
    const FString& MapName,
    const FString& Options,
    FString& ErrorMessage
)

{

    Super::InitGame(MapName, Options, ErrorMessage);

  
     
    shrd_ptr_for_channel = std::make_shared<std::queue<json>>(message_channel);
    shrd_ptr_for_to_server_channel = std::make_shared<std::queue<json>>(to_server_message_channel);
    ThreadParameters thread_params(message_channel_lock, shrd_ptr_for_channel, to_server_channel_lock, shrd_ptr_for_to_server_channel);

      std::thread thread_object (network_thread, thread_params);
      thread_object.detach();
    
}

void AClientCornerStoneGameModeBase::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);    
    std::unique_lock<std::mutex> a_lock(message_channel_lock);
    while (shrd_ptr_for_channel->empty() == false)
    {
        auto new_message = std::move(shrd_ptr_for_channel->front());
        messages.push(new_message);
        UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
        shrd_ptr_for_channel->pop();
    }


    while (messages.empty() == false) {
        auto new_message = std::move(messages.front());
        if (new_message["eventType"] == "AddController") {
            auto game_state = GetGameState<ABattleGameState>();
            auto hand_controller = NewObject<UHandController>(UHandController::StaticClass());
            hand_controller->Setup(new_message["id"]);
            game_state->AddHandController(hand_controller);
        }
        messages.pop();
    }
    
}