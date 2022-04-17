#pragma once
#include "Entity.h"
#include <list>

class Projectile : public Entity
{

public:
	Projectile(uint32_t sprite_x, uint32_t sprite_y, int x, int y, int width, int height, float angle, int pierce, Vector2D velocity, int dmg);

	virtual void Draw(float scrollX =0) override;
	void Update();

	virtual bool IsOverlap(Entity* ent) override;

	int Pierce;
	float Angle;
	int Dmg;
	bool HarmPlayer = false;


private:
	std::list<Entity*> m_pierced;
};

