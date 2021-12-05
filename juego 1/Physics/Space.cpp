#include "Space.h"

Space::Space()
{
}


void Space::AddDynamicEntity(Entity* entity) { dynamicEntities.push_back(entity); }
void Space::AddStaticEntity(Entity* entity) { staticEntities.push_back(entity); }
void Space::RemoveDynamicEntity(Entity* entity) { dynamicEntities.remove(entity); }
void Space::RemoveStaticEntity(Entity* entity) { staticEntities.remove(entity); }

void Space::AddProjectile(Entity* proj) { projectiles.push_back(proj);  }

void Space::RemoveProjectile(Entity* proj) { projectiles.remove(proj); }

void Space::Clear()
{
	dynamicEntities.clear();
	staticEntities.clear();
	projectiles.clear();
}

void Space::Update() {
	for (auto const& entity : dynamicEntities) {

		// MoverDerecha / izquierda
		updateMoveRight(entity);
		updateMoveLeft(entity);
		updateMoveTop(entity);
		updateMoveDown(entity);
	}
	auto itr = projectiles.begin();
	while (itr != projectiles.end())
	{
		Entity* p = *itr;
		if (p->Deleted)
			projectiles.erase(itr++);
		else {
			updateMoveRightProj(p);
			updateMoveLeftProj(p);
			updateMoveTopProj(p);
			updateMoveDownProj(p);
			itr++;
		}
	}

}

void Space::updateMoveTop(Entity* dynamicAct) {
	if (dynamicAct->Vec.y < 0) {
		float possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntities) {
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((topDynamic + dynamicAct->Vec.y) <= downStatic
				&& downDynamic > topStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= downStatic - topDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = downStatic - topDynamic;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.y = possibleMovement;
	}
}


void Space::updateMoveDown(Entity* dynamicAct) {
	if (dynamicAct->Vec.y > 0) {
		
		float possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntities) {
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((downDynamic + dynamicAct->Vec.y) >= topStatic
				&& topDynamic < downStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= topStatic - downDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = topStatic - downDynamic;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.y = possibleMovement;
	}
}

void Space::updateMoveRightProj(Entity* dynamicAct)
{
	if (dynamicAct->Vec.x > 0) {
		float possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntities) {
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;

			float leftStatic = staticAct->x - staticAct->width / 2;
			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((rightDynamic + dynamicAct->Vec.x) >= leftStatic
				&& rightDynamic <= leftStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= leftStatic - rightDynamic) {
					dynamicAct->Deleted = true;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.x = possibleMovement;
	}
}

void Space::updateMoveLeftProj(Entity* dynamicAct)
{
	if (dynamicAct->Vec.x < 0) {
		float possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntities) {
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((leftDynamic + dynamicAct->Vec.x) <= rightStatic
				&& leftDynamic >= rightStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= rightStatic - leftDynamic) {
					dynamicAct->Deleted = true;
				}

			}

		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.x = possibleMovement;
	}
}

void Space::updateMoveTopProj(Entity* dynamicAct)
{


	if (dynamicAct->Vec.y < 0) {
		float possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntities) {
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((topDynamic + dynamicAct->Vec.y) <= downStatic
				&& downDynamic > topStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= downStatic - topDynamic) {
					dynamicAct->Deleted = true;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.y = possibleMovement;
	}
}


void Space::updateMoveDownProj(Entity* dynamicAct)
{
	if (dynamicAct->Vec.y > 0) {

		float possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntities) {
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float leftStatic = staticAct->x - staticAct->width / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((downDynamic + dynamicAct->Vec.y) >= topStatic
				&& topDynamic < downStatic
				&& leftDynamic < rightStatic
				&& rightDynamic > leftStatic) {
				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= topStatic - downDynamic) {
		
					dynamicAct->Deleted = true;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->y = dynamicAct->y + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.y = possibleMovement;
	}
}



void Space::updateMoveRight(Entity* dynamicAct) {
	if (dynamicAct->Vec.x > 0) {
		float possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntities) {
			float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;

			float leftStatic = staticAct->x - staticAct->width / 2;
			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((rightDynamic + dynamicAct->Vec.x) >= leftStatic
				&& rightDynamic <= leftStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement >= leftStatic - rightDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = leftStatic - rightDynamic;
				}
			}
		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.x = possibleMovement;
	}
}


void Space::updateMoveLeft(Entity* dynamicAct) {
	if (dynamicAct->Vec.x < 0) {
		float possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntities) {
			float leftDynamic = dynamicAct->x - dynamicAct->width / 2;
			float topDynamic = dynamicAct->y - dynamicAct->height / 2;
			float downDynamic = dynamicAct->y + dynamicAct->height / 2;
			float rightStatic = staticAct->x + staticAct->width / 2;
			float topStatic = staticAct->y - staticAct->height / 2;
			float downStatic = staticAct->y + staticAct->height / 2;

			// Alerta!, Elemento est�tico en la trayectoria.
			if ((leftDynamic + dynamicAct->Vec.x) <= rightStatic
				&& leftDynamic >= rightStatic
				&& topStatic < downDynamic
				&& downStatic > topDynamic) {

				// Comprobamos si la distancia al est�tico es menor
				// que nuestro movimientoPosible actual
				if (possibleMovement <= rightStatic - leftDynamic) {
					// La distancia es MENOR que nuestro movimiento posible
					// Tenemos que actualizar el movimiento posible a uno menor
					possibleMovement = rightStatic - leftDynamic;
				}

			}

		}
		// Ya se han comprobado todos los est�ticos
		dynamicAct->x = dynamicAct->x + possibleMovement;
		// Restringir la velocidad actual (opcional)
		dynamicAct->Vec.x = possibleMovement;
	}
}



