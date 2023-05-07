// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ClientCornerStoneGameModeBase.generated.h"

class TcpClient;
/**
 * 
 */
UCLASS()
class CLIENTCORNERSTONE_API AClientCornerStoneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
   std::shared_ptr<TcpClient> Client;
public:
    virtual void InitGame

    (
        const FString& MapName,
        const FString& Options,
        FString& ErrorMessage
    ) override;
};
