#include "EndLayer.h"

EndLayer::EndLayer()
	: background("rcs/game_over.png",
		Game::Get().Width / 2,
		Game::Get().Height / 2, 
		Game::Get().Width, 
		Game::Get().Height)
{
	Init();
}

EndLayer::~EndLayer()
{
	if (controller) SDL_GameControllerClose(controller);
}

void EndLayer::Init()
{
}

void EndLayer::Draw()
{
	background.Draw();
	Game::Get().Present();
}

void EndLayer::ProcessControls(SDL_Event event)
{
	if (event.type == SDL_CONTROLLERDEVICEADDED) {
		controller = SDL_GameControllerOpen(0);
		if (controller == nullptr) {
			LOG_ERROR("error en GamePad");
		}
		else {
			LOG_ERROR("GamePad conectado");
		}
	}
	switch (event.type) {
	case SDL_CONTROLLERBUTTONDOWN: [[fallthrough]]; // FALLTHROUGH (usar c++17+ si no no compila)
	case SDL_CONTROLLERAXISMOTION: {
		if (controller == nullptr) {
			controller = SDL_GameControllerOpen(0);
		}
		Game::Get().Input = Input::CONTROLLER;
		break;
	}
	case SDL_KEYDOWN:
		Game::Get().Input = Input::KEYBOARD;
		break;
	}
	// Procesar teclas
	if (Game::Get().Input == Input::CONTROLLER) {  // gamePAD
		gamePadToControls(event);
	}
	if (Game::Get().Input == Input::KEYBOARD) {
		keysToControls(event);
	}
	//procesar controles, solo tiene uno
	if (controlContinue) {
		// Cambia la capa
		Game::Get().layer = Game::Get().gameLayer;
		controlContinue = false;
	}
}
void EndLayer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // stop
			Game::Get().Stop();
			break;
		case SDLK_RETURN: // continue
			controlContinue = true;
			break;
		}
	}
}

void EndLayer::gamePadToControls(SDL_Event event)
{
	if (controller == nullptr) {
		LOG_ERROR("error en GamePad");
	}
	bool buttonStart = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
	if (buttonStart) {
		controlContinue = true;
	}
}

