#include "World.h"


World::World() {

	//Worm de la izquierda
	this->worms[0].setX(715);	
	this->worms[0].setY(616);
	this->worms[0].setDirection(RIGHT);

	//Worm de la derecha
	this->worms[0].setX(1185);
	this->worms[0].setY(616);
	this->worms[0].setDirection(LEFT);

	this->gravity = 0.24;
	this->jumpSpeed = 4.5;	//TODO: Nose en que esta dada	
	this->walkSpeed = 27;	//Dada pixeles por segundo
}

void World::dispatcher(EVENT event) {

	//El worm de la izquierda se maneja con AWD y el de la derecha con las flechas

	switch (event) {

		/*
		//	EVENTOS DE MOVIMIENTO LATERAL
		*/

	case DOWN_KEY_A:
	
		this->worms[0].setDirection(LEFT);	
		this->worms[0].walk();	//cambio el estado a Walking y reinicio el tickCount
	
		break;
	case UP_KEY_A:

		this->worms[0].stop();	

		break;
	case DOWN_KEY_LEFT:

		this->worms[1].setDirection(LEFT);
		this->worms[1].walk();	//cambio el estado a Walking y reinicio el tickCount

		break;
	case UP_KEY_LEFT:

		this->worms[1].stop();

		break;
	case DOWN_KEY_D:

		this->worms[0].setDirection(RIGHT);
		this->worms[0].walk();	//cambio el estado a Walking y reinicio el tickCount

		break;
	case UP_KEY_D:

		this->worms[0].stop();

		break;
	case DOWN_KEY_RIGHT:

		this->worms[1].setDirection(RIGHT);
		this->worms[1].walk();	//cambio el estado a Walking y reinicio el tickCount

		break;
	case UP_KEY_RIGHT:

		this->worms[1].stop();

		break;
	
		/*
		//	EVENTOS DE SALTO
		*/

	case DOWN_KEY_W:

		break;
	case UP_KEY_W:

		break;
	case DOWN_KEY_UP:

		break;
	case UP_KEY_UP:

		break;

		/*
		// OTROS EVENTOS
		*/

	case QUIT:

		break;
	}
}