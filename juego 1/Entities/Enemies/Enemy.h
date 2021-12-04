#pragma once
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Entities/Animation.h"

class Enemy : public Entity
{
public:
	Enemy(std::string_view filename, int x, int y, int width, int height);

	virtual Projectile* Attack() = 0;

	virtual void Draw(float scrollX = 0) override;

	virtual void Update();

	int Health = 0;

protected:
	Animation* m_animation = nullptr;
};

