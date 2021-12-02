#pragma once

#include "Entities/Entity.h"
#include <list>

class Space
{
public:
	Space();
	void update();

	void updateMoveRight(Entity* dynamicAct);
	void updateMoveLeft(Entity* dynamicAct);
	void updateMoveTop(Entity* dynamicAct);
	void updateMoveDown(Entity* dynamicAct);

	void addDynamicEntity(Entity* entity);
	void addStaticEntity(Entity* entity);
	void removeDynamicEntity(Entity* entity);
	void removeStaticEntity(Entity* entity);

private:
	std::list<Entity*> dynamicEntitys;
	std::list<Entity*> staticEntitys;
};

