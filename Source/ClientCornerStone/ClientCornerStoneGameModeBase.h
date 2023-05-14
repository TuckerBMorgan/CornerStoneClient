// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <queue>
#include <string>
#include <mutex>
#include "NmJson.h"
#include "ClientCornerStoneGameModeBase.generated.h"
/**
 * 
 */


using json = nlohmann::json;


UCLASS()
class CLIENTCORNERSTONE_API AClientCornerStoneGameModeBase : public AGameModeBase
{ 
	GENERATED_BODY()
protected:

public:

    AClientCornerStoneGameModeBase();
    virtual void InitGame

    (
        const FString& MapName,
        const FString& Options,
        FString& ErrorMessage
    ) override;

    //UFUNCTION()
    virtual void Tick(float) override;


private:
    std::shared_ptr<std::queue<json>> shrd_ptr_for_channel;
    std::shared_ptr<std::queue<json>> shrd_ptr_for_to_server_channel;
    std::queue<json> messages;
    std::mutex message_channel_lock;
    std::queue<json> message_channel;

    std::mutex to_server_channel_lock;
    std::queue<json> to_server_message_channel;
   // std::thread thread_object;
};
