#include "World.h"


World::World() {

	//Worm de la izquierda
	this->worms[0].setX(701);	
	this->worms[0].setY(616);
	this->worms[0].setDirection(RIGHT);

	//Worm de la derecha
	this->worms[1].setX(1152);
	this->worms[1].setY(616);
	this->worms[1].setDirection(LEFT);

	this->gravity = 0.24;
	this->jumpSpeed = 4.5;	//Dada en pixeles por tick
	this->walkSpeed = 27;	//Dada pixeles por segundo
}

/*Maneja todos los eventos que no sean los de tick*/
void World::dispatcher(EVENT event) {

	//El worm de la izquierda se maneja con AWD y el de la derecha con las flechas

	switch (event) {

		/************************************************************************
		//					EVENTOS DE MOVIMIENTO LATERAL
		*************************************************************************/

	case DOWN_KEY_A:

		if (this->worms[0].getStates() == STAND_BY)	// Si aprietan A y no estaba haciendo nada
		{
			this->worms[0].setDirection(LEFT);		// Cambio la dirección
			this->worms[0].walk();					//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_A:
		if (this->worms[0].getStates() == WALKING)	// Si sueltan A y estaba caminado
			this->worms[0].stopWalking();			// Paro la caminata si no pasó le tiempo de confirmación
		break;

	case DOWN_KEY_LEFT:

		if (this->worms[1].getStates() == STAND_BY) // Si aprietan LEFT y no estaba haciendo nada
		{
			this->worms[1].setDirection(LEFT);		// Cambio la dirección
			this->worms[1].walk();					//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_LEFT:

		if (this->worms[1].getStates() == WALKING)	// Si sueltan LEFT y estaba caminado
			this->worms[1].stopWalking();			// Paro la caminata si no pasó le tiempo de confirmación
		break;

	case DOWN_KEY_D:

		if (this->worms[0].getStates() == STAND_BY) // Si aprietan D y no estaba haciendo nada
		{
			this->worms[0].setDirection(RIGHT);		// Cambio la dirección
			this->worms[0].walk();					// cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_D:

		if (this->worms[0].getStates() == WALKING)	// Si sueltan D y estaba caminado
			this->worms[0].stopWalking();			// Paro la caminata si no pasó le tiempo de confirmación
		break;

	case DOWN_KEY_RIGHT:

		if (this->worms[1].getStates() == STAND_BY)	// Si aprietan RIGHT y no estaba haciendo nada
		{
			this->worms[1].setDirection(RIGHT);		// Cambio la dirección
			this->worms[1].walk();					// cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_RIGHT:

		if (this->worms[1].getStates() == WALKING)	// Si sueltan RIGHT y estaba caminado
			this->worms[1].stopWalking();			// Paro la caminata si no pasó le tiempo de confirmación
		break;

		/********************************************************************************
						EVENTOS DE SALTO
		********************************************************************************/

	case DOWN_KEY_W:

		if (this->worms[0].getStates() == STAND_BY)		// Si aprietan W y no estaba haciendo nada
			this->worms[0].jump();						// Comienzo la secuencia salto en el worm 0
		break;

	case UP_KEY_W:

		if (this->worms[0].getStates() == JUMPING)	// Si suelta W y no estaba haciendo nada
			this->worms[0].stopJumping();			// Paro el salto si no pasó el tiempo de confirmación

		break;

	case DOWN_KEY_UP:

		if (this->worms[1].getStates() == STAND_BY)		// Si aprietan UP y no estaba haciendo nada
			this->worms[1].jump();						// Comienzo la secuencia salto en el worm 1
		break;

	case UP_KEY_UP:

		if (this->worms[1].getStates() == JUMPING)		// Si suelta UP y no estaba haciendo nada
			this->worms[1].stopJumping();				// Paro el salto si no pasó el tiempo de confirmación
		break;


	default:
		break;
	}
}