#include "Enemy.h"
#include "Entities/Weapons/TripleWand.h"
#include "Entities/Weapons/Bow.h"

Enemy::Enemy(uint32_t sprite_x, uint32_t sprite_y, int x, int y, int width, int height)
	: Entity(sprite_x, sprite_y, x, y, width, height)
{
}

Enemy::~Enemy()
{
	delete m_aIdle;
	delete m_aDying;
}

void Enemy::Draw(float scrollX)
{
	m_animation->Draw(x - scrollX, y);
}

Weapon* Enemy::Drop()
{
	// drop rate is 15%
	int rnd = Game::Get().randomInt(1, 100);
	if (rnd <= 15) {
		int w = Game::Get().randomInt(1, 2);
		if (w == 1)
			return new TripleWand(x, y);
		else
			return new Bow(x, y);

	}
	return nullptr;
}

Projectile* Enemy::Update()
{
	bool endAnimation = m_animation->Update();
	if (Health <= 0) {
		state = State::DYING;
		m_animation = m_aDying;
	}
	if (endAnimation) {
		state = State::DEAD;
	}
	return nullptr;
}
