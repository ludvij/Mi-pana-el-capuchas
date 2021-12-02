#include "Layers/GameLayer.h"

GameLayer::GameLayer()
{
	Init();
}

GameLayer::~GameLayer()
{
	deleteAll();
}

// use to delete all resources in the class
void GameLayer::deleteAll()
{
	delete player;
}


void GameLayer::Init() {
	deleteAll();
	player = new Player(Game::Get().Width/2, Game::Get().Height/2);
}

void GameLayer::Draw()
{
	player->Draw();

	Game::Get().Present();
}

void GameLayer::Update() {

}

void GameLayer::ProcessControls(SDL_Event event)
{
	// if event.type ...
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
