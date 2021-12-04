#pragma once

#include "Entities/Entity.h"
#include "Entities/Projectile.h"
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


	void AddProjectile(Projectile* proj);

	void Clear();


private:
	void updateMoveRight(Entity* dynamicAct);
	void updateMoveLeft(Entity* dynamicAct);
	void updateMoveTop(Entity* dynamicAct);
	void updateMoveDown(Entity* dynamicAct);



	void updateMoveRightProj(Projectile* dynamicAct);
	void updateMoveLeftProj(Projectile* dynamicAct);
	void updateMoveTopProj(Projectile* dynamicAct);
	void updateMoveDownProj(Projectile* dynamicAct);


	std::list<Entity*> dynamicEntities;
	std::list<Entity*> staticEntities;
	std::list<Projectile*> projectiles;
};

