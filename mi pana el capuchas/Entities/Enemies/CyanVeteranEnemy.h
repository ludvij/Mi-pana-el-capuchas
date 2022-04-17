#pragma once
#include "Enemy.h"
class CyanVeteranEnemy : public Enemy
{
public:
	CyanVeteranEnemy(int x, int y);

	virtual Projectile* Update() override;
};

