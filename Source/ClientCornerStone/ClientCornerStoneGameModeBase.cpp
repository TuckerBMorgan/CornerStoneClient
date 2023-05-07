// Copyright Epic Games, Inc. All Rights Reserved.


#include "ClientCornerStoneGameModeBase.h"
#include "TcpClient.h"

void AClientCornerStoneGameModeBase::InitGame

(
    const FString& MapName,
    const FString& Options,
    FString& ErrorMessage
)

{

    Super::InitGame(MapName, Options, ErrorMessage);

    auto tcp_client = new TcpClient();


}