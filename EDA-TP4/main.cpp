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

	redraw(mundo.worms);
	cout << "OK draw" << endl;

	EVENT evento = TICK;

	while (evento != QUIT) {

		evento = getEvent();

		// Debugger de eventos
		if(evento != EMPTY && evento != TICK)
			cout << "Evento: \t" << evento << endl;

		 if (evento == TICK) {

			mundo.worms[0].update(mundo.walkSpeed, mundo.jumpSpeed, mundo.gravity);	//Actualizo ambos worms segun su estado
			mundo.worms[1].update(mundo.walkSpeed, mundo.jumpSpeed, mundo.gravity);
			redraw(mundo.worms);			//Draw
		}
		else {

			mundo.dispatcher(evento);
		}
	}

	shutdownAllegro();
	cout << "OK destroy" << endl;

	//testImages();

}

/*
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
		redraw(&worm);
	}
	cout << "Lo freno" << endl;
	worm.stopWalking();
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
	worm.stopJumping();
	for (int i = 0; i < 70; i++) {
		cout << *(int*)worm.getImage(sizeof(walk[0])) << endl;
		worm.update(0, 0);
	}

	cout << "FIN" << endl;

}
*/

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