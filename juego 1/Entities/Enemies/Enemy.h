#pragma once
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Entities/Animation.h"

class Enemy : public Entity
{
public:
	Enemy(std::string_view filename, int x, int y, int width, int height);

	virtual void Draw(float scrollX = 0) override;

	virtual Projectile* Update();

	int Health = 0;
	int ShotTime = -1;

protected:
	Animation* m_animation = nullptr;
};

