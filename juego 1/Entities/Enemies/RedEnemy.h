#pragma once
#include "Enemy.h"
class RedEnemy : public Enemy
{
public:
	RedEnemy(int x, int y);

	virtual Projectile* Update() override;
};

