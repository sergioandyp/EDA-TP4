#include <iostream>
#include "World.h"
#include "grafica.h"

using namespace std;

int main() {

	World mundo;

	if (initAllegro())
	{
		return -1;
	}

	if (loadImages(mundo.worms))
	{
		return -1;
	}

	redraw(mundo.worms);

	EVENT evento = TICK;

	while (evento != QUIT) {

		evento = getEvent();

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
}