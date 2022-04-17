#pragma once

#include "Enemy.h"

class CyanEnemy : public Enemy
{
public:
	CyanEnemy(int x, int y);

	virtual Projectile* Update() override;
};

