#pragma once
#include "Layers/Layer.h"
#include <Entities/Player.h>

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

private:

	void loadMap(std::string name);
	void loadMapObj(char character, float x, float y);



	// frees all resources
	void deleteAll();

	template <typename T>
	void deleteActors(std::list<T>& list);
};


