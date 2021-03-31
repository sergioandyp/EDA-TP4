#include <iostream>
#include "World.h"
#include "grafica.h"

using namespace std;

int main() {

	World mundo;		// Creamos el mundo a ejecutar

	if (initAllegro())	// Iniciamos allegro
	{
		return -1;		// Si hay error, finalizamos el programa
	}


	if (loadImages(mundo.worms))	// Cargamos las imagenes de los worms	
	{
		return -1;		// Si hay error, finalizamos el programa
	}

	redraw(mundo.worms);	// Dibujamos la pantalla inicial

	EVENT evento = EMPTY;	// Inicializamos evento actual como nulo.

	while (evento != QUIT) {

		evento = getEvent();	// Tomamos el siguiente evento

		 if (evento == TICK) {

			mundo.worms[0].update(mundo.walkSpeed, mundo.jumpSpeed, mundo.gravity);	//Actualizo ambos worms según su estado
			mundo.worms[1].update(mundo.walkSpeed, mundo.jumpSpeed, mundo.gravity);
			redraw(mundo.worms);			//Draw
		}
		else {
			mundo.dispatcher(evento);	// Si no me pidieron dibujar, el dispacher se encarga de determinar
										// que hacer según el evento recibido.
		}
	}


	shutdownAllegro();	// Destruimos los recursos

	return 0;
}
