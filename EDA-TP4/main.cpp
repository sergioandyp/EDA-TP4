#include <iostream>
#include "World.h"

int main() {

	World mundo;

}

/* CLASES:

	- Worm
		- constructor
		- jump()
		- move()
		- po
		- set/getX()
		- set/getY()
		- ALLEGRO_BITMAP images[]
		private:
			- tickCount
	- World
		- contructor
		- 
*/


/*
while (1){	//RedrawNow se maneja por un timer de allegro

	evento = getEvent();	//TECLA - TICK - TECLA
							
	if (eventoTECLA)..{		//PRE-DISPATCHER
		dispatcher();
	}

	if (eventoTICK)..{
		this->worms[0].update(this->walkSpeed, this->jumpSpeed);	//Actualizo ambos worms segun su estado
		this->worms[1].update(this->walkSpeed, this->jumpSpeed);
		Dibujar();			//Draw
	}
}
*/