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


	void AddProjectile(Entity* proj);
	void RemoveProjectile(Entity* proj);

	void Clear();


private:
	void updateMoveRight(Entity* dynamicAct);
	void updateMoveLeft(Entity* dynamicAct);
	void updateMoveTop(Entity* dynamicAct);
	void updateMoveDown(Entity* dynamicAct);



	void updateMoveRightProj(Entity* dynamicAct);
	void updateMoveLeftProj(Entity* dynamicAct);
	void updateMoveTopProj(Entity* dynamicAct);
	void updateMoveDownProj(Entity* dynamicAct);


	std::list<Entity*> dynamicEntities;
	std::list<Entity*> staticEntities;
	std::list<Entity*> projectiles;
};

