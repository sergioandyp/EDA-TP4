#include "World.h"


World::World() {

	//Worm de la izquierda
	this->worms[0].setX(685);	
	this->worms[0].setY(616);
	this->worms[0].setDirection(RIGHT);

	//Worm de la derecha
	this->worms[1].setX(1170);
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

		/*
		//					EVENTOS DE MOVIMIENTO LATERAL
		*/

	case DOWN_KEY_A:

		if (this->worms[0].getStates() == STAND_BY)
		{
			this->worms[0].setDirection(LEFT);
			this->worms[0].walk();	//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_A:

		if (this->worms[0].getStates() == WALKING)
			this->worms[0].stopWalking();	
		break;

	case DOWN_KEY_LEFT:

		if (this->worms[1].getStates() == STAND_BY)
		{
			this->worms[1].setDirection(LEFT);
			this->worms[1].walk();	//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_LEFT:

		if (this->worms[1].getStates() == WALKING)
			this->worms[1].stopWalking();
		break;

	case DOWN_KEY_D:

		if (this->worms[0].getStates() == STAND_BY)
		{
			this->worms[0].setDirection(RIGHT);
			this->worms[0].walk();	//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_D:

		if (this->worms[0].getStates() == WALKING)
			this->worms[0].stopWalking();
		break;

	case DOWN_KEY_RIGHT:

		if (this->worms[1].getStates() == STAND_BY)
		{
			this->worms[1].setDirection(RIGHT);
			this->worms[1].walk();	//cambio el estado a Walking y reinicio el tickCount
		}
		break;

	case UP_KEY_RIGHT:

		if (this->worms[1].getStates() == WALKING)
			this->worms[1].stopWalking();
		break;
	
		/*
						EVENTOS DE SALTO
		*/

	case DOWN_KEY_W:

		if(this->worms[0].getStates() == STAND_BY)
			this->worms[0].jump();
		break;

	case UP_KEY_W:

		if (this->worms[0].getStates() == JUMPING)
			this->worms[0].stopJumping();
		break;

	case DOWN_KEY_UP:

		if (this->worms[1].getStates() == STAND_BY)
			this->worms[1].jump();
		break;

	case UP_KEY_UP:

		if (this->worms[1].getStates() == JUMPING)
			this->worms[1].stopJumping();
		break;

		/*
		// OTROS EVENTOS
		*/

	case QUIT:
		break;

	case EMPTY:
		break;
	}
}