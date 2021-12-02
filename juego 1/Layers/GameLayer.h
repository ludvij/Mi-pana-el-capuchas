#pragma once

#include "Layers/Layer.h"
#include "Entities/Player.h"
#include "Physics/space.h"

#include <list>

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

private:

	void loadMap(std::string name);
	void loadMapObj(char character, float x, float y);

	void keysToControls(SDL_Event event);
	void gamepadToControls(SDL_Event event);

	// frees all resources
	void deleteAll();

	template <typename T>
	void deleteActors(std::list<T>& list);

private:
	int m_controlMoveX = 0;
	int m_controlMoveY = 0;
};


