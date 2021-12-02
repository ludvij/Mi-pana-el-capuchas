#include "Layers/GameLayer.h"

GameLayer::GameLayer()
{
	Init();
}

GameLayer::~GameLayer()
{
	deleteAll();
}

void GameLayer::keysToControls(SDL_Event event)
{
}

void GameLayer::gamepadToControls(SDL_Event event)
{
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	int stickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	//LOG_TRACE("botones:" << buttonA << "," << buttonB);
	//LOG_TRACE("stickX: " << stickX << " stickY: " << stickY);

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		m_controlMoveX = 1;
	}
	else if (stickX < -4000) {
		m_controlMoveX = -1;
	}
	else {
		m_controlMoveX = 0;
	}

	if (stickY > 4000) {
		m_controlMoveY = 1;
	}
	else if (stickY < -4000) {
		m_controlMoveY = -1;
	}
	else {
		m_controlMoveY = 0;
	}
}

// use to delete all resources in the class
void GameLayer::deleteAll()
{
	delete player;
}


void GameLayer::Init() {
	deleteAll();
	space = Space();
	player = new Player(Game::Get().Width/2, Game::Get().Height/2);
	space.addDynamicEntity(player);
}

void GameLayer::Draw()
{
	player->Draw();

	Game::Get().Present();
}

void GameLayer::Update() 
{
	player->Update();
	space.update();
}

void GameLayer::ProcessControls(SDL_Event event)
{
	// if event.type ...
	if (event.type == SDL_CONTROLLERDEVICEADDED) {
		controller = SDL_GameControllerOpen(0);
		if (controller == nullptr) {
			//LOG_ERROR("\terror en GamePad");
		}
		else {
			//LOG_TRACE("\tGamepad conectado");
		}
	}

	// Cambio automático de input
	switch (event.type) {
	case SDL_CONTROLLERBUTTONDOWN:
		[[fallthrough]];
	case SDL_CONTROLLERAXISMOTION:
		Game::Get().Input = Input::CONTROLLER;
		break;
	case SDL_KEYDOWN:
		Game::Get().Input = Input::KEYBOARD;
		break;
	}

	if (Game::Get().Input == Input::CONTROLLER) {
		gamepadToControls(event);
	}
	if (Game::Get().Input == Input::KEYBOARD) {
		keysToControls(event);
	}

	if (m_controlMoveX > 0) {
		player->MoveX(1);
	}
	else if (m_controlMoveX < 0) {
		player->MoveX(-1);
	}
	else {
		player->MoveX(0);
	}

	// Eje Y
	if (m_controlMoveY > 0) {
		player->MoveY(1);
	}
	else if (m_controlMoveY < 0) {
		player->MoveY(-1);
	}
	else {
		player->MoveY(0);
	}
}

template<typename T>
inline void GameLayer::deleteActors(std::list<T>& list)
{
	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		T ent = *itr;
		if (ent->deleted == true)
		{
			//space->removeDynamicActor(actor);
			list.erase(itr);
			delete ent;
		}
	}
}
