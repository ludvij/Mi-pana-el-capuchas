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
	// drop rate is 20%
	int rnd = Game::Get().randomInt(1, 100);
	if (rnd <= 10) {
		return new Bow(x, y);
	}
	if (rnd <= 20) {
		return new TripleWand(x, y);
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
