#pragma once

#include "Entities/Entity.h"
#include <list>

class Space
{
public:
	Space();
	void Update();


	void AddDynamicEntity(Entity* entity);
	void AddStaticEntity(Entity* entity);
	void RemoveDynamicEntity(Entity* entity);
	void RemoveStaticEntity(Entity* entity);

	void Clear();

private:
	void updateMoveRight(Entity* dynamicAct);
	void updateMoveLeft(Entity* dynamicAct);
	void updateMoveTop(Entity* dynamicAct);
	void updateMoveDown(Entity* dynamicAct);

	std::list<Entity*> dynamicEntities;
	std::list<Entity*> staticEntities;
};

