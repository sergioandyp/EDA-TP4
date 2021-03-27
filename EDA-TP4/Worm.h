#ifndef _WORM_H_

#define _WORM_H_

#include "Point.h"

typedef enum WORM_STATE { WALKING, JUMPING, STAND_BY };		// FALTA COMPLETAR

typedef enum DIRECTION { LEFT, RIGHT };

class Worm {
public:

	// getters
	unsigned int getX();
	unsigned int getY();
	unsigned int getTickCount();
	unsigned int getStates();
	unsigned int getDirection();

	// setters (devuelve 1 si hubo error)
	bool setX(unsigned int x);
	bool setY(unsigned int y);
	bool setWalkImages(void* w_images);
	bool setJumpImages(void* j_images);

	// Movement
	bool jump();		// Setea estado a JUMP
	bool walk();		// Setea estado a WALK

	bool update();

	// Devuelve un puntero a la posicion de la imagen en el arreglo.
	// La imagen corresponde al estado actual del worm
	void* getImage(unsigned int Imagesize);

	// Ejemplo de llamada:
	//ALLEGRO_BITMAP* actualImage = (ALLEGRO_BITMAP *) getImage(sizeof(ALLEGRO_BITMAP*))

private:
	Point pos;		// La posicion se referencia en la esquina inferior izquierda
	unsigned int tickCount;		// Contador de ticks para las animaciones.
	WORM_STATE state;
	DIRECTION dir;
	double speed[2];	// {x, y}
	void* jumpingImages;
	void* walkingImages;
};

#endif