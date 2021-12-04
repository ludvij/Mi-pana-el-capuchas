#include "Enemy.h"

Enemy::Enemy(std::string_view filename, int x, int y, int width, int height)
	: Entity(filename, x, y, width, height)
{
}

void Enemy::Draw(float scrollX)
{
	m_animation->Draw(x - scrollX, y);
}

void Enemy::Update()
{
	bool endAnimation = m_animation->Update();
}
