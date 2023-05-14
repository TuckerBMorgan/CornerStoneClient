// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NmJson.h"


using json = nlohmann::json;

class CLIENTCORNERSTONE_API EventType {

public:
	virtual void Execute(class ABattleGameState* GameState) = 0;
};

class StartGame : public EventType {
public:
	StartGame(json blob) {

	}

	virtual void Execute(class ABattleGameState* GameState) override;
};

class AddController : public EventType {
	int id;
public:
	AddController(json blob) {
		this->id = blob["id"];
	}

	virtual void Execute(class ABattleGameState* GameState) override;
};

EventType* CreateEventFromJson(json message);