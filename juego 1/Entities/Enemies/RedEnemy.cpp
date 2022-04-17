#include "RedEnemy.h"
#include "Entities/Player.h"
#include "Layers/GameLayer.h"

RedEnemy::RedEnemy(int x, int y)
	: Enemy(RED_ENEMY_POS, x, y, Game::Get().CellSizeX, Game::Get().CellSizeY)
{
	m_aIdle = new Animation("rcs/enemies/enemy_red_idle.png", width, height, 18, 3, true);
	m_aDying = new Animation("rcs/enemies/enemy_red_dying.png", width, height, 18, 3, false);
	m_animation = m_aIdle;
	collisionDMG = 3;
	Health = 1;
	type = "red";
}


Projectile* RedEnemy::Update()
{
	Enemy::Update();
	if (state != State::MOVING) {
		Vec = { 0 };
		return nullptr;
	}
	Player* p = ((GameLayer*)Game::Get().gameLayer)->player;
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

bool RedEnemy::IsOverlap(Entity* ent)
{
	if (Entity::IsOverlap(ent)) {
		if (*ent == *((GameLayer*)Game::Get().layer)->player) {
			Health = 0;
		}
		return true;
	}
	return false;
}
