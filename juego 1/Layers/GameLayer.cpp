#include "Layers/GameLayer.h"
#include "Entities/Enemies/RedEnemy.h"
#include "Entities/Enemies/CyanEnemy.h"
#include "Entities/Enemies/CyanVeteranEnemy.h"

#include <algorithm>
#include <fstream>
#include <sstream>

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
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
#ifdef _DEBUG
		case SDLK_ESCAPE:
			Game::Get().Stop();
			break;
#endif // _DEBUG
		case SDLK_d: // derecha
			m_controlMoveX = MAX_MAP_POS;
			break;
		case SDLK_a: // izquierda
			m_controlMoveX = -MAX_MAP_POS;
			break;
		case SDLK_w: // arriba
			m_controlMoveY = -MAX_MAP_POS;
			break;
		case SDLK_s: // abajo
			m_controlMoveY = MAX_MAP_POS;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (m_controlMoveX != 0) {
				m_controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (m_controlMoveX != 0) {
				m_controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (m_controlMoveY != 0) {
				m_controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (m_controlMoveY != 1) {
				m_controlMoveY = 0;
			}
			break;
		}
	}
}


void GameLayer::gamepadToControls(SDL_Event event)
{
	// Leer los botones
	bool triggerUR = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

	int stickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

	float stickRotX = static_cast<float>(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX));
	float stickRotY = static_cast<float>(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY));

	if (triggerUR) {
		m_controlShoot = true;
	}
	else {
		m_controlShoot = false;
	}


	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]

	if (stickX > MIN_POS || stickX < -MIN_POS) {
		m_controlMoveX = mapRangeControls(stickX);
	}
	else {
		m_controlMoveX = 0;
	}

	if (stickY > MIN_POS || stickY < -MIN_POS) {
		m_controlMoveY = mapRangeControls(stickY);
	}
	else {
		m_controlMoveY = 0;
	}

	if (!(stickRotX < MIN_POS && stickRotX > -MIN_POS && stickRotY < MIN_POS && stickRotY > -MIN_POS)) {
		float tangent = std::atan2f(-stickRotY, -stickRotX) * 180.0f / static_cast<float>(M_PI);
		player->Weapon->Angle = tangent;
	}
	else 
		player->Weapon->Angle = 0;

}

// use to delete all resources in the class
void GameLayer::deleteAll()
{
	delete player;
	space.Clear();
	while (!tiles.empty())       delete tiles.back(),       tiles.pop_back();
	while (!enemies.empty())     delete enemies.back(),     enemies.pop_back();
	while (!projectiles.empty()) delete projectiles.back(), projectiles.pop_back();
}




// maps ranges	[ MIN_POS,  MAX_POS] into [ MIN_MAP_POS,  MAX_MAP_POS]
//				[-MIN_POS, -MAX_POS] into [-MIN_MAP_POS, -MAX_MAP_POS]
int GameLayer::mapRangeControls(int stick)
{
	// clamp stick range to make it consistant
	int clampedStick = std::clamp(stick, -MAX_POS, MAX_POS);
	// inverse lerp funcion since c++ doesn't provide one that I know of
	auto iLerp = [](int x, int a, int b) { return static_cast<float>(x - a) / static_cast<float>(b - a); };

	if (stick > 0) {
		float t = iLerp(clampedStick, MIN_POS, MAX_POS);
		return std::lerp(MIN_MAP_POS, MAX_MAP_POS , t);
	}
	else if (stick < 0) {
		float t = iLerp(clampedStick, -MIN_POS, -MAX_POS);
		return std::lerp(-MIN_MAP_POS, -MAX_MAP_POS, t);
	}
	return 0;
}

void GameLayer::updateCollisions()
{
	for (const auto& p : projectiles) {
		if (!p->IsInrender()) {
			p->Deleted = true;
			space.RemoveProjectile(p);
		}
		if (p->HarmPlayer) {
			if (p->IsOverlap(player)) {
				
			}
		}
		else {
			for (const auto& e : enemies) {
				if (p->IsOverlap(e)) {
					e->Health--;
				}
			}
		}
	}
	deleteActors(projectiles);
	deleteActors(enemies);
}


void GameLayer::Init() {
	deleteAll();
	space = Space();
	loadMap("rcs/maps/map2");
	auto c = new CyanEnemy(10 * Game::Get().CellSizeX + Game::Get().CellSizeX/2, 10 * Game::Get().CellSizeY + Game::Get().CellSizeY/2);
	//auto r = new RedEnemy(5 * Game::Get().CellSizeX + Game::Get().CellSizeX / 2, 10 * Game::Get().CellSizeY + Game::Get().CellSizeY / 2);
	auto vc = new CyanVeteranEnemy(10 * Game::Get().CellSizeX + Game::Get().CellSizeX / 2, 7 * Game::Get().CellSizeY + Game::Get().CellSizeY / 2);
	enemies.push_back(c);
	//enemies.push_back(r);
	enemies.push_back(vc);
	space.AddDynamicEntity(c);
	//space.AddDynamicEntity(r);
	space.AddDynamicEntity(vc);
}

void GameLayer::Draw()
{

	for (const auto& tile : tiles) {
		tile->Draw();
	}
	for (const auto& enemy : enemies) {
		enemy->Draw();
	}
	player->Draw();
	for (const auto& p : projectiles) p->Draw();
	Game::Get().Present();
}

void GameLayer::Update()
{

	space.Update();
	for (const auto& p : projectiles) p->Update();
	for (const auto& e : enemies) {
		auto p = e->Update();
		if (p != nullptr) {
			space.AddProjectile(p);
			projectiles.push_back(p);
		}
	}
	player->Update();

	updateCollisions();
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

	if (m_controlShoot) {
		auto ps = player->Weapon->Use();
		if (ps.size() != 0) {
			for (const auto& p : ps) {
				projectiles.push_back(p);
				space.AddProjectile(p);
			}
			m_controlShoot = false;
		}
	}
}

template<typename T>
inline void GameLayer::deleteActors(std::list<T>& list)
{
	auto itr = list.begin();
	while(itr != list.end())
	{
		T ent = *itr;
		if (ent->Deleted == true)
		{
			list.erase(itr++);
			space.RemoveDynamicEntity(ent);
			delete ent;
		}
		else {
			itr++;
		}
	}
}

void GameLayer::loadMap(std::string_view name) {
	char character = 0;
	int cellX = Game::Get().CellSizeX;
	int cellY = Game::Get().CellSizeY;
	std::string line;
	std::ifstream streamFile(name.data());
	if (!streamFile.is_open()) {
		LOG_ERROR("Falla abrir el fichero de mapa");
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			std::istringstream streamLine(line);
			m_mapWidth = line.length() * cellX; // Ancho del mapa en pixels
			// Por car�cter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				//std::cout << character;
				float x = cellX / 2 + j * cellX; // x central
				float y = cellY + i * cellY; // y suelo
				loadMapObj(character, x, y);
			}

			//std::cout << character << std::endl;
		}
	}
	streamFile.close();
}


void GameLayer::loadMapObj(char character, int x, int y)
{
	
	switch (character) {

	case 'B': {
		auto tile = new Tile("rcs/tiles/tile_bricks.png", x, y);
		// modificaci�n para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space.AddStaticEntity(tile);
		break;
	}
	case '1': {
		player = new Player(x, y);
		// modificaci�n para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space.AddDynamicEntity(player);
		// keep reference that all classes can access;
		Game::Get().player = player;
		[[fallthrough]];
	}
	case '.': {
		int tex = Game::Get().randomInt(1, 4);
		std::string grass = "rcs/tiles/tile_grass" + std::to_string(tex) + ".png";
		auto tile = new Tile(grass, x, y);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
	}
	}
}
