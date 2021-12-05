#include "RedEnemy.h"
#include "Entities/Player.h"

RedEnemy::RedEnemy(int x, int y)
	: Enemy("rcs/enemies/enemy_red.png", x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_animation = new Animation("rcs/enemies/enemy_red_idle.png", width, height, 18, 3, true);
	Health = 1;
}


Projectile* RedEnemy::Update()
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

	Vector2D velocity = -dst;
	// add player speed vector
	velocity = velocity + p->Vec * 15;
	// normalization and give speed
	Vec = velocity / std::sqrtf(velocity.DistanceSquared()) * 5;

	return nullptr;
}
