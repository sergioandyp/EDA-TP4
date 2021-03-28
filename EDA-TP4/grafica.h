#ifndef GRAFICA
#define GRAFICA

#include "Worm.h"
#include "World.h"

/***************************************************************************
*                      Definiciones de constantes
***************************************************************************/
#define ERROR   1
#define OK      0

/**************************************************************************/

/***************************************************************************
* SHUTDOWNALLEGRO
*	Destruye todos los recursos y desinstala los addons.
*	Recibe: nada
*	Retorna: nada
***************************************************************************/
void shutdownAllegro(void);


/***************************************************************************
* INITALLEGRO
*	Inicializa todos los recursos e instala los addons.
*	Recibe: nada
*	Retorna: ERROR si hubo error.
*			 OK si no hubo error.	
***************************************************************************/
bool initAllegro(void);


/***************************************************************************
* REDRAW
*	Dibuja en pantalla los worns y el fondo.
*	Recibe: - worms[]: arreglo de worms del juego. 
*	Retorna: nada
***************************************************************************/
void redraw(Worm worms[]);


/***************************************************************************
* LOADIMAGES
*	Carga las fotos de salto y caminata de los worms, el fondo y el mapa. 
*	Recibe: - worms[]: arreglo de worms del juego.
*	Retorna: ERROR si hubo error.
*			 OK si no hubo error.
***************************************************************************/
bool loadImages(Worm worms[]);

/***************************************************************************
* GETEVENT
*	Traduce los eventos de Allegro a eventos admitidos por el main.
*	Recibe: nada
*	Retorna: EMPTY si no hubo eventos nuevos.
*			 El evento si hubo algun evento nuevo.
***************************************************************************/
EVENT getEvent();

#endif //GRAFICA