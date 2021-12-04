#pragma once

#include "Layers/Layer.h"
#include "Entities/Player.h"
#include "Physics/space.h"
#include "Entities/Tile.h"
#include "Entities/Projectile.h"

#include <list>

constexpr int MAX_POS = 30000;
constexpr int MIN_POS = 4000;

constexpr int MAX_MAP_POS = 50;
constexpr int MIN_MAP_POS = 1;

class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void Init()            override;
	virtual void Draw()            override;
	virtual void Update()          override;
	virtual void ProcessControls(SDL_Event event) override;


public: // maybe change it to private
	Player* player;
	SDL_GameController* controller;
	Space space;
	std::list<Tile*> tiles;
	std::list<Projectile*> projectiles;


private:

	void loadMap(std::string_view name);
	void loadMapObj(char character, int x, int y);

	void keysToControls(SDL_Event event);
	void gamepadToControls(SDL_Event event);

	// frees all resources
	void deleteAll();

	template <typename T>
	void deleteActors(std::list<T>& list);

	int mapRangeControls(int stick);

	void updateCollisions();


private:
	int m_controlMoveX = 0;
	int m_controlMoveY = 0;

	bool m_controlShoot = false;

	int m_mapWidth;
	int m_mapHeight;
};


