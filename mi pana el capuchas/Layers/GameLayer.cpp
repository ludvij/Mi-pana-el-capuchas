#include "Layers/GameLayer.h"
#include "Entities/Enemies/RedEnemy.h"
#include "Entities/Enemies/CyanEnemy.h"
#include "Entities/Enemies/CyanVeteranEnemy.h"

#include "Entities/SpriteSheet.h"

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
	delete player;
	if (controller) {
		SDL_GameControllerClose(controller);
	}
}

void GameLayer::keysToControls(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			Game::Get().Stop();
			break;
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

	int motionX = event.motion.x; /// game->scaleLower;
	int motionY = event.motion.y; /// game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEMOTION) {
		Vector2D dst = { player->x - motionX, player->y - motionY };
		float tangent = std::atan2f(dst.y, dst.x) * 180.0f / static_cast<float>(M_PI);
		player->Weapon->Angle = tangent;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN) {
		m_controlShoot = true;
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

void GameLayer::createEnemies()
{
	// every 45 seconds we add another enemy
	// game runs 60 fps so 60 * 45
	int enemyN = 5 + time / 2700 + level / 3;
	//enemies can't appear in an area that is 3 cells close to the player
	Vector2D Mindst = { Game::Get().CellSizeX * 5, Game::Get().CellSizeY * 5};

	while (enemyN != 0) {
		int x = Game::Get().randomInt(Game::Get().CellSizeX + 50, Game::Get().CellSizeX * 17 - 50);
		int y = Game::Get().randomInt(Game::Get().CellSizeY + 50, Game::Get().CellSizeY * 17 - 50);
		bool placeable = true;
		for (const auto& t : tiles) {
			// can be placed
			if (t->isPointInBounds(x, y)) {
				placeable = false;
			}
		}
		if (!placeable) {
			continue;
		}
		else {
			Vector2D dst = { player->x - x, player->y - y };
			if (dst.DistanceSquared() > Mindst.DistanceSquared()) {
				int rnd = Game::Get().randomInt(1, 100);
				if (rnd <= 50) {
					auto e = new CyanEnemy(x, y);
					e->Health += level / 3;
					enemies.push_back(e);
					space.AddDynamicEntity(e);
				}
				else if (rnd <= 80) {
					auto e = new CyanVeteranEnemy(x, y);
					e->Health += level / 3;
					enemies.push_back(e);
					space.AddDynamicEntity(e);
				}
				else {
					auto e = new RedEnemy(x, y);
					e->Health += level / 3;
					enemies.push_back(e);
					space.AddDynamicEntity(e);
				}
				enemyN--;
			}
		}
	}
}

// use to delete all resources in the class
void GameLayer::deleteAll()
{
	space.Clear();				    
	while (!tiles.empty())          delete tiles.back(),          tiles.pop_back();
	while (!tilesBG.empty())        delete tilesBG.back(),        tilesBG.pop_back();
	while (!enemies.empty())        delete enemies.back(),        enemies.pop_back();
	while (!projectiles.empty())    delete projectiles.back(),    projectiles.pop_back();
	while (!droppedWeapons.empty()) delete droppedWeapons.back(), droppedWeapons.pop_back();
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
				player->Health--;
				hud.UpdateHearts(player);
			}
		}
		else {
			for (const auto& e : enemies) {
				if (e->state == State::MOVING && p->IsOverlap(e)) {
					e->Health -= p->Dmg;
				}
			}
		}
	}
	for (const auto& e : enemies) {
		if (!e->IsInrender()) {
			e->Deleted = true;
		}
		if (e->state == State::DEAD) {
			e->Deleted = true;
			auto drop = e->Drop();
			if (drop != nullptr) {
				droppedWeapons.push_back(drop);
			}
		}
		else if (e->state == State::MOVING) {
			if (e->IsOverlap(player)) {
				player->Health -= e->collisionDMG;
				hud.UpdateHearts(player);
			}
		}
	}
	auto itr = droppedWeapons.begin();
	while (itr != droppedWeapons.end())
	{
		Weapon* ent = *itr;
		if (player->IsOverlap(ent))
		{
			ent->cadence = player->cadence;
			ent->damage = player->dmg;
			player->Weapon = ent;
			droppedWeapons.erase(itr++);	
		}
		else {
			itr++;
		}
	}
	deleteActors(projectiles);
	deleteActors(enemies);
}


void GameLayer::Init() {
	deleteAll();
	space = Space();
	loadMap("rcs/maps/map" + std::to_string(level % 3 + 1));
	hud.UpdateHearts(player);
	player->Weapon->cadence = player->cadence;
	player->Weapon->damage = player->dmg;
	createEnemies();
	
}

void GameLayer::Draw()
{

	for (const auto& tile : tilesBG) {
		tile->Draw();
	}
	for (const auto& tile : tiles) {
		tile->Draw();
	}
	for (const auto& d : droppedWeapons) {
		d->Draw();
	}

	for (const auto& enemy : enemies) {
		enemy->Draw();
	}
	player->Draw();
	for (const auto& p : projectiles) p->Draw();
	hud.Draw();
	Game::Get().Present();
}


std::ostream& operator<< (std::ostream& os, const std::list<Enemy*>& vector) {
	os << "\n";
	for (const auto& e : vector) {
		os << e->type << " [" << e->x << ", " << e->y << "]\n";
	}
	return os;
}

void GameLayer::Update()
{
	// level cleared
	if (enemies.size() == 0) {
		level++;
		Init();
		if ((level) % 3 == 0 && level != 0) {
			Game::Get().layer = Game::Get().intersectionLayer;
		}


	}
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
	hud.UpdateFrame(player);

	updateCollisions();
	if (player->Health <= 0) {
		Game::Get().layer = Game::Get().endLayer;

		Init();
	}
	time++;
}

void GameLayer::ProcessControls(SDL_Event event)
{
	// if event.type ...
	if (event.type == SDL_CONTROLLERDEVICEADDED) {
		controller = SDL_GameControllerOpen(0);
		if (controller == nullptr) {
			LOG_ERROR("error en GamePad");
		}
		else {
			LOG_INFO("Gamepad conectado");
		}
	}

	// Cambio automático de input
	switch (event.type) {
	case SDL_CONTROLLERBUTTONDOWN: [[fallthrough]];
	case SDL_CONTROLLERAXISMOTION: {
		if (!controller) {
			controller = SDL_GameControllerOpen(0);
			if (controller == nullptr) {
				LOG_ERROR("error en GamePad");
			}
			else {
				LOG_INFO("Gamepad conectado");
			}
		}
		Game::Get().Input = Input::CONTROLLER;
		break;
	}
	case SDL_MOUSEBUTTONDOWN: [[fallthrough]];
	case SDL_MOUSEMOTION:     [[fallthrough]];
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
		auto tile = new Tile(BRICK_TILE_POS, x, y);
		// modificaci�n para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space.AddStaticEntity(tile);
		break;
	}
	case '1': {
		if (player == nullptr) {
			player = new Player(x, y);
		}
		else {
			player->x = x;
		}
		// modificaci�n para empezar a contar desde el suelo.
		player->y = y - player->height / 2;
		space.AddDynamicEntity(player);
		[[fallthrough]];
	}
	case '.': {
		Tile* tile = nullptr;
		// ugly I now, i'll change it, maybe
		switch (Game::Get().randomInt(1, 4))
		{
		case 1:
			tile = new Tile(GRASS_TILE_1_POS, x, y);
			break;
		case 2:
			tile = new Tile(GRASS_TILE_2_POS, x, y);
			break;
		case 3:
			tile = new Tile(GRASS_TILE_3_POS, x, y);
			break;
		case 4:
			tile = new Tile(GRASS_TILE_4_POS, x, y);
			break;
		default:
			tile = new Tile(GRASS_TILE_1_POS, x, y);
			break;
		}
		tile->y = tile->y - tile->height / 2;
		tilesBG.push_back(tile);
	}
	}
}
