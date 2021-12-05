#include "CyanVeteranEnemy.h"
#include "Entities/Player.h"

CyanVeteranEnemy::CyanVeteranEnemy(int x, int y)
	: Enemy("rcs/enemies/enemy_cyan_veteran.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_animation = new Animation("rcs/enemies/enemy_cyan_veteran_idle.png", width, height, 18, 3, true);
	Health = 3;
	ShotTime = 90;
}

Projectile* CyanVeteranEnemy::Update()
{
	Enemy::Update();
	Player* p = (Player*)Game::Get().player;
	// MOVEMENT
	Vector2D dst = { x - p->x, y - p->y };

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
		Vector2D velocity = -dst;
		// magi number to predict movement
		velocity = velocity +p->Vec * 30;

		velocity = velocity / std::sqrtf(velocity.DistanceSquared()) * 7;
		auto p = new Projectile("rcs/player/weapons/projectile_triple_wand.png",
			x, y, Game::Get().CellSizeX / 2, Game::Get().CellSizeY / 2, 0, 1, velocity);
		p->HarmPlayer = true;
		return p;
	}
	ShotTime--;
	return nullptr;
}
