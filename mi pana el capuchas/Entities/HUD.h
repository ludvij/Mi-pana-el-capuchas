#pragma once
#include "Entity.h"
#include "Player.h"
#include <vector>
class HUD
{
public:
	HUD();
	~HUD();

	void Draw();

	void UpdateHearts(Player* player);
	void UpdateFrame(Player* player);

private:
	std::vector<Entity*> hearts;
	Entity frame;
	Weapon* currWeapon = nullptr;
};

