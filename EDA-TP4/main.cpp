#include <iostream>
#include "World.h"
#include "grafica.h"

using namespace std;

void testImages();

int main() {

	World mundo;


	if (initAllegro())
	{
		return -1;
	}

	cout << "OK init" << endl;

	if (loadImages(mundo.worms))
	{
		return -1;
	}
	cout << "OK load" << endl;

	mundo.worms[0].setX(0);
	mundo.worms[0].setY(600);
	mundo.worms[0].setDirection(RIGHT);
	mundo.worms[1].setX(1000);
	mundo.worms[1].setY(600);
	mundo.worms[1].setDirection(LEFT);

	redraw(mundo.worms);
	cout << "OK draw" << endl;

	shutdownAllegro();
	cout << "OK destroy" << endl;

	//testImages();

}

void testImages() {
	/*Worm worm;
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
		redraw(&worm);
	}
	cout << "Lo freno" << endl;
	worm.stop();
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0,0);
	}

	cout << endl << "Ahora salto:" << endl << endl;

	worm.jump();		// Todavia no esta implementado el jump
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0, 0);
	}
	cout << "Lo freno" << endl;
	worm.stop();
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0, 0);
	}

	cout << "FIN" << endl;*/

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