#pragma once
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Entities/Animation.h"
#include "Entities/Weapons/Weapon.h"

class Enemy : public Entity
{
public:
	Enemy(std::string_view filename, int x, int y, int width, int height);
	~Enemy();

	virtual void Draw(float scrollX = 0) override;

	Weapon* Drop();

	virtual Projectile* Update();

	int Health = 0;
	int ShotTime = -1;
	State state = State::MOVING;

protected:
	Animation* m_animation = nullptr;
	Animation* m_aIdle = nullptr;
	Animation* m_aDying = nullptr;
};

