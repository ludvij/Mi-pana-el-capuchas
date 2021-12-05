#include "CyanEnemy.h"
#include "Layers/GameLayer.h"
#include "Entities/Player.h"

CyanEnemy::CyanEnemy(int x, int y)
	: Enemy("rcs/enemies/enemy_cyan.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_aIdle = new Animation("rcs/enemies/enemy_cyan_idle.png", width, height, 18, 3, true);
	m_aDying = new Animation("rcs/enemies/enemy_cyan_dying.png", width, height, 18, 3, false);
	m_animation = m_aIdle;
	Health = 3;
	ShotTime = 90;
}

Projectile* CyanEnemy::Update()
{
	Enemy::Update();
	if (state != State::MOVING) {
		Vec = { 0 };
		return nullptr;
	}
	Player* p = ((GameLayer*)Game::Get().layer)->player;
	// MOVEMENT
	Vector2D dst = {x - p->x, y - p->y};

	float maxDist = (5 * Game::Get().CellSizeX * 5 * Game::Get().CellSizeY);
	float twoCell = 2 * (Game::Get().CellSizeX - Game::Get().CellSizeX / 2) * 2 * (Game::Get().CellSizeY - Game::Get().CellSizeY / 2);
	float dstSQ = dst.DistanceSquared();

	// GET CLOSE
	if (dstSQ > maxDist + twoCell) {
		Vec = -dst / std::sqrtf(dst.DistanceSquared()) * 3;
	}
	// GET FAR
	else if (dstSQ < maxDist) {
		Vec = dst / std::sqrtf(dst.DistanceSquared()) * 3;
	}
	else {
		Vec = { 0, 0 };
	}

	// SHOT
	if (ShotTime <= 0) {
		ShotTime = 90;
		auto p =  new Projectile("rcs/player/weapons/projectile_wand.png",
			x, y, Game::Get().CellSizeX / 2, Game::Get().CellSizeY / 2, 0, 1, -dst / std::sqrtf(dst.DistanceSquared()) * 5);
		p->HarmPlayer = true;
		return p;
	}
	ShotTime--;
	return nullptr;
}
