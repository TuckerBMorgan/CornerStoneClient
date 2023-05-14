// Fill out your copyright notice in the Description page of Project Settings.


#include "EventTypes.h"
#include "../BattleGameState.h"
#include "HandController.h"

#pragma optimize("", off)
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

	return nullptr;
}
#pragma optimize("", on)

void StartGame::Execute(ABattleGameState* GameState) {

}

void AddController::Execute(ABattleGameState* GameState) {
	auto hand_controller = NewObject<UHandController>(UHandController::StaticClass());
	hand_controller->Setup(this->id);
	GameState->AddHandController(hand_controller);
}