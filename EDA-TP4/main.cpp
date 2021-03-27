#include <iostream>
#include "World.h"

using namespace std;

void testImages();

int main() {

	World mundo;

	testImages();

}

void testImages() {
	Worm worm;
	int walk[20];
	int jump[20];

	for (int i = 0; i < 20; i++) {
		walk[i] = i + 1;
		jump[i] = i + 1;
	}

	worm.setWalkImages(walk);
	worm.setJumpImages(jump);

	worm.walk();
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0,0);
	}
	cout << "Lo freno" << endl;
	worm.stop();
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0,0);
	}

	cout << "FIN" << endl;

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