#ifndef _WORM_H_
#define _WORM_H_

#include "Point.h"

enum WORM_STATE { WALKING, JUMPING, STAND_BY, STOP_WALKING, STOP_JUMPING};

enum DIRECTION { LEFT, RIGHT };

class Worm {
public:

	//constructor, no es la gran cosa porque despues uso el de World
	Worm();

	// getters
	double getX();
	double getY();
	unsigned int getTickCount();
	unsigned int getStates();
	unsigned int getDirection();

	// setters (devuelve 1 si hubo error)
	bool setX(unsigned int x);
	bool setY(unsigned int y);
	bool setDirection(DIRECTION dire);
	bool setWalkImages(void* w_images);
	bool setJumpImages(void* j_images);

	// Movement
	bool jump();		// Setea estado a JUMP
	bool walk();		// Setea estado a WALK
	bool stopWalking();		// OJO! ACA HABRIA QUE CONSIDERAR LA DIRECCION TAMBIEN
	bool stopJumping();

	bool update(double walkSpeed, double jumpSpeed, double gravity);

	// Devuelve un puntero a la posicion de la imagen en el arreglo.
	// La imagen corresponde al estado actual del worm
	void* getImage(unsigned int imagesize);

	// Ejemplo de llamada:
	//ALLEGRO_BITMAP* actualImage = (ALLEGRO_BITMAP *) getImage(sizeof(ALLEGRO_BITMAP*))

private:
	Point pos;		// La posicion se referencia en la esquina inferior izquierda
	unsigned int tickCount;		// Contador de ticks para las animaciones.
	WORM_STATE state;
	DIRECTION dir;
	double speed[2];	// {Vx, Vy}
	void* jumpingImages;
	void* walkingImages;
};

#endif