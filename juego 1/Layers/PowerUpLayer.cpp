#include "PowerUpLayer.h"
#include "Gamelayer.h"

PowerUpLayer::PowerUpLayer()
	: background("rcs/powerups.png",
		Game::Get().Width / 2,
		Game::Get().Height / 2,
		Game::Get().Width,
		Game::Get().Height),
	frameCadence("rcs/frame.png",
		Game::Get().Width * 1 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3),
	frameHealth("rcs/frame.png",
		Game::Get().Width * 2 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3),
	frameDmg("rcs/frame.png",
		Game::Get().Width * 3 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3),
	cadence("rcs/player/weapons/projectile_bow.png",
		Game::Get().Width * 1 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3),
	health("rcs/heart.png",
		Game::Get().Width * 2 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3),
	damage("rcs/player/weapons/weapon_sword.png",
		Game::Get().Width * 3 / 4.0f,
		Game::Get().Height * 0.6f,
		Game::Get().CellSizeX * 3,
		Game::Get().CellSizeY * 3)
{
	Init();
}


PowerUpLayer::~PowerUpLayer()
{
	if (controller) SDL_GameControllerClose(controller);
}

void PowerUpLayer::Init()
{
}


void PowerUpLayer::Draw() {
	background.Draw();
	frameCadence.Draw();
	frameDmg.Draw();
	frameHealth.Draw();

	cadence.Draw();
	health.Draw();
	damage.Draw();

	Game::Get().Present();
}

void PowerUpLayer::ProcessControls(SDL_Event event)
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
	frameCadence.m_texture = Game::Get().GetTexture("rcs/frame.png");
	frameHealth.m_texture = Game::Get().GetTexture("rcs/frame.png");
	frameDmg.m_texture = Game::Get().GetTexture("rcs/frame.png");
	if (pos == 0) {
		frameCadence.m_texture = Game::Get().GetTexture("rcs/selected_frame.png");
	}
	else if (pos == 1) {
		frameHealth.m_texture = Game::Get().GetTexture("rcs/selected_frame.png");
	}
	else if (pos == 2) {
		frameDmg.m_texture = Game::Get().GetTexture("rcs/selected_frame.png");
	}

	if (controlContinue) {
		if (pos == 0) {
			((GameLayer*)Game::Get().gameLayer)->player->cadence -= 2;
			if (((GameLayer*)Game::Get().gameLayer)->player->cadence <= 6) {
				((GameLayer*)Game::Get().gameLayer)->player->cadence = 6;
			}
		}
		if (pos == 1) {
			((GameLayer*)Game::Get().gameLayer)->player->Health = 10;
			((GameLayer*)Game::Get().gameLayer)->hud.UpdateHearts(((GameLayer*)Game::Get().gameLayer)->player);
		}
		if (pos == 2) {
			((GameLayer*)Game::Get().gameLayer)->player->dmg += 1;
		}
		Game::Get().layer = Game::Get().gameLayer;
		controlContinue = false;
		
	}
}

void PowerUpLayer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // stop
			Game::Get().Stop();
			break;
		case SDLK_a: {
			pos--;
			if (pos < 0) {
				pos = 2;
			}
			break;
		}
		case SDLK_d: {
			pos++;
			if (pos > 2) {
				pos = 0;
			}
			break;
		}
		case SDLK_RETURN: // continue
			controlContinue = true;
			break;
		}
	}
}

void PowerUpLayer::gamePadToControls(SDL_Event event)
{
	int stickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);

	bool buttonA = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);

	if (buttonA) {
		controlContinue = true;
	}

	if (canMove) {
		if (stickX < -4000) {
			pos--;
			if (pos < 0) {
				pos = 2;
			}
			canMove = false;
		}
		else if (stickX > 4000) {
			pos++;
			if (pos > 2) {
				pos = 0;
			}
			canMove = false;
		}
	}
	else {
		if (stickX < 4000 && stickX > -4000)
			canMove = true;
	}
}

