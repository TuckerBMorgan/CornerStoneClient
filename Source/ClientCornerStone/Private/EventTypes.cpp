// Fill out your copyright notice in the Description page of Project Settings.


#include "EventTypes.h"
#include "../BattleGameState.h"
#include "HandController.h"
#include "Card.h"

EventType* CreateEventFromJson(json message) {
	std::string value = message["eventType"];
	if (value  == "StartGame") {
		StartGame* startGame = new StartGame(message);
		return startGame;
	}
	if (value == "AddController") {
		AddController* addController = new AddController(message);
		return addController;
	}
	if (value == "CreateCard") {
		CreateCard* create_card = new CreateCard(message);
		return create_card;
	}

	if (value == "GiveCardToController") {
		GiveCardToController* give_card_to_controller = new GiveCardToController(message);
		return give_card_to_controller;
	}

	return nullptr;
}


void StartGame::Execute(ABattleGameState* GameState) {

}

void AddController::Execute(ABattleGameState* GameState) {
	auto hand_controller = NewObject<UHandController>(UHandController::StaticClass());
	hand_controller->Setup(this->id);
	GameState->AddHandController(hand_controller);
}

void CreateCard::Execute(ABattleGameState* GameState) {
	auto card_instance = NewObject<UCard>(UCard::StaticClass());
	card_instance->Setup(this->catalog_id, this->unique_id, this->cost, this->starting_health, this->starting_attack);
	GameState->AddCardInstanceToGame(card_instance);

}

void GiveCardToController::Execute(ABattleGameState* GameState) {
	UHandController* Controller = GameState->GetHandController(this->controller_id);
	assert(Controller != NULL);
	Controller->AddCardToController(this->card_unique_id);
}