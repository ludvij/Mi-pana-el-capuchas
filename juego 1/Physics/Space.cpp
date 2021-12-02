#include "Space.h"

Space::Space()
{
}


void Space::addDynamicEntity(Entity* entity) { dynamicEntitys.push_back(entity); }
void Space::addStaticEntity(Entity* entity) { staticEntitys.push_back(entity); }
void Space::removeDynamicEntity(Entity* entity) { dynamicEntitys.remove(entity); }
void Space::removeStaticEntity(Entity* entity) { staticEntitys.remove(entity); }

void Space::update() {
	for (auto const& entity : dynamicEntitys) {

		// MoverDerecha / izquierda
		updateMoveRight(entity);
		updateMoveLeft(entity);
		updateMoveTop(entity);
		updateMoveDown(entity);
	}
}

void Space::updateMoveTop(Entity* dynamicAct) {
	if (dynamicAct->Vec.y < 0) {
		int possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntitys) {
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;
			int rightStatic = staticAct->x + staticAct->width / 2;
			int leftStatic = staticAct->x - staticAct->width / 2;

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
		
		int possibleMovement = dynamicAct->Vec.y;
		// El mejor "idealmente" Vec.y partimos de ese

		for (auto const& staticAct : staticEntitys) {
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;

			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;
			int rightStatic = staticAct->x + staticAct->width / 2;
			int leftStatic = staticAct->x - staticAct->width / 2;

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



void Space::updateMoveRight(Entity* dynamicAct) {
	if (dynamicAct->Vec.x > 0) {
		int possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntitys) {
			int rightDynamic = dynamicAct->x + dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;

			int leftStatic = staticAct->x - staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

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
		int possibleMovement = dynamicAct->Vec.x;
		// El mejor "idealmente" Vec.x partimos de ese

		for (auto const& staticAct : staticEntitys) {
			int leftDynamic = dynamicAct->x - dynamicAct->width / 2;
			int topDynamic = dynamicAct->y - dynamicAct->height / 2;
			int downDynamic = dynamicAct->y + dynamicAct->height / 2;
			int rightStatic = staticAct->x + staticAct->width / 2;
			int topStatic = staticAct->y - staticAct->height / 2;
			int downStatic = staticAct->y + staticAct->height / 2;

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



