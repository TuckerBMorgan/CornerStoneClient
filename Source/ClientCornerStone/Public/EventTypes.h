// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NmJson.h"


using json = nlohmann::json;


struct StartGame {

	StartGame(json message) {

	}
};

struct AddController {
	unsigned int id;
	AddController(json message) {
		id = message["id"];
	}
};