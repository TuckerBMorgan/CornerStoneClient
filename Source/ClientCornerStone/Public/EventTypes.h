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
	size_t id;
public:
	AddController(json blob) {
		this->id = blob["id"];
	}

	virtual void Execute(class ABattleGameState* GameState) override;
};


class CreateCard : public EventType {
	
	size_t catalog_id;
	size_t unique_id;
	size_t cost;
	size_t starting_health;
	size_t starting_attack;
 
public: 
	CreateCard(json blob) {
		this->catalog_id = blob["catalog_id"];
		this->unique_id = blob["unique_id"];
		this->cost = blob["cost"];
		this->starting_health = blob["starting_health"];
		this->starting_attack = blob["starting_attack"];
	}

	virtual void Execute(class ABattleGameState* GameState) override;
};
EventType* CreateEventFromJson(json message);

class GiveCardToController : public EventType {
private: 
	size_t card_unique_id;
	size_t controller_id;

public:
	GiveCardToController(json blob) {
		this->card_unique_id = blob["card_unique_id"];
		this->controller_id = blob["controller_id"];
	}

	virtual void Execute(class ABattleGameState* GameState) override;
};