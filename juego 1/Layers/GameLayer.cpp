#include "Layers/GameLayer.h"
#include <algorithm>

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


constexpr int MAX_POS = 30000;
constexpr int MIN_POS = 4000;

constexpr int MAX_MAP_POS = 50;
constexpr int MIN_MAP_POS = 1;


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

	// TODO: mapear de alguna forma el rango de el jystick a una escala para hacer que el movimiento no sea super clunky
	// coger el rango [-30000, 30000] y mapearlo a un rango de el tipo [1, 10]
	// si esta entre [-4000, 4000] se deja como 0
	if (stickX > MIN_POS) {
		
		m_controlMoveX = mapRangeControls(stickX);
	}
	else if (stickX < -MIN_POS) {
		m_controlMoveX = mapRangeControls(stickX);
	}
	else {
		m_controlMoveX = 0;
	}

	if (stickY > MIN_POS) {
		m_controlMoveY = mapRangeControls(stickY);
	}
	else if (stickY < -MIN_POS) {
		m_controlMoveY = mapRangeControls(stickY);
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




// maps ranges	[ MIN_POS,  MAX_POS] into [ MIN_MAP_POS,  MAX_MAP_POS]
//				[-MIN_POS, -MAX_POS] into [-MIN_MAP_POS, -MAX_MAP_POS]
int GameLayer::mapRangeControls(int stick)
{
	// clamp stick range to make it consistant
	int clamppedStick = std::clamp(stick, -MAX_POS, MAX_POS);
	// inverse lerp funcion since c++ doesn't provide one that I know of
	auto iLerp = [](int x, int a, int b) { return static_cast<float>(x - a) / static_cast<float>(b - a); };

	if (stick > 0) {
		float t = iLerp(stick, MIN_POS, MAX_POS);
		return std::lerp(MIN_MAP_POS, MAX_MAP_POS , t);
	}
	if (stick < 0) {
		float t = iLerp(stick, -MIN_POS, -MAX_POS);
		return std::lerp(-MIN_MAP_POS, -MAX_MAP_POS, t);
	}
	return 0;
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

	float speedMultX = static_cast<float>(m_controlMoveX) / static_cast<float>(MAX_MAP_POS);
	float speedMultY = static_cast<float>(m_controlMoveY) / static_cast<float>(MAX_MAP_POS);
	player->MoveX(speedMultX);
	player->MoveY(speedMultY);
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
