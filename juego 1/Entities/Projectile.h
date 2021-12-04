#pragma once
#include "Entity.h"
#include <list>

class Projectile : public Entity
{

public:
	Projectile(std::string_view filename, int x, int y, int width, int height, float angle, int pierce, Vector2D velocity);

	virtual void Draw(float scrollX =0) override;
	void Update();

	virtual bool IsOverlap(Entity* ent) override;

	int Pierce;
	float Angle;
	bool HarmPlayer = false;


private:
	std::list<Entity*> m_pierced;
};

