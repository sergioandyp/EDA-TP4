#include "Worm.h"
#include <math.h>
# define PI           3.14159265358979323846  /* pi */
#define	LEFT_LIMIT	701
#define	RIGHT_LIMIT	1152
#define INF_LIMIT	616

//constructor
Worm::Worm(){
	
	this->tickCount = 1;
	this->state = STAND_BY;
	this->jumpingImages = 0;
	this->walkingImages = 0;
}

// getters
double Worm::getX() {
	return this->pos.x;
}
double Worm::getY() {
	return this->pos.y;
}
unsigned int Worm::getTickCount() {

	return this->tickCount;
}
unsigned int Worm::getStates() {

	return this->state;
}
unsigned int Worm::getDirection() {

	return this->dir;
}



// setters 
void Worm::setX(unsigned int x) {

	this->pos.x = x;
}
void Worm::setY(unsigned int y) {

	this->pos.y = y;
}
void Worm::setDirection(DIRECTION dire) {
	if (this->state == STAND_BY) {
		this->dir = dire;
	}
}
bool Worm::setWalkImages(void* w_images) {

	this->walkingImages = w_images;
	return 0;
}
bool Worm::setJumpImages(void* j_images) {
	
	this->jumpingImages = j_images;
	return 0;
}


// Movement
bool Worm::jump() {	// Setea estado a JUMP y reinicia tickCount

	if (this->state == STAND_BY) {
		this->state = JUMPING;
		this->tickCount = 1;
		return true;	
	}
	return false;
}
bool Worm::walk() {		// Setea estado a WALK y reinicia tickCount

	if (this->state == STAND_BY) {	//Solo le reinicio el contador si ya no estaba moviendose
		this->state = WALKING;		//Entonces si vos apretaste mientras ya se estaba moviendo va a terminar de moverse
		this->tickCount = 1;		//Y va a seguir moviendose hasta que sueltes la tecla
		return true;	
	}
	return false;
}

bool Worm::stopWalking() {		//Va a parar el movimiento del worm solamente si pasaron menos de 8 frames

	int error = 0;
	if (this->state == WALKING) {
		if (this->tickCount <= 5) {

			this->state = STAND_BY;
		}
		else if (this->tickCount <= 50) {

			this->state = STOP_WALKING;	//En este caso quiero avisar que el movimiento debe detenerse ni bien termine la animacion
		}
		else {
			
			error = 1;
		}
	}

	return error;
}

// Detiene el salto del worm.
// Si todavia no habia empezado el salto, no lo empieza
// Si ya habia empezado, lo termina y luego para de saltar
// Devuelve: 0 si estaba queriendo saltar, 1 si no.
bool Worm::stopJumping() {

	int error = 1;

	if (this->state == JUMPING) {	// Solo detengo el salto si esta saltando... LOGIC

		if (this->tickCount <= 5) {	// Si es antes del WARM_UP lo paro
			this->state = STAND_BY;
			this->tickCount = 0;
		}
		else{	// Si es despues aviso que se tiene que parar cuando termine
			this->state = STOP_JUMPING;
		}
		error = 0;	// Se logro detener la animacion de salto
	}

	return error;
}

/*Actualiza a partir de la velocidad y el estado de cada worm la posicion de los mismos*/
bool Worm::update(double walkSpeed, double jumpSpeed, double gravity) {

	int error = 0;

	if (this->state == WALKING || this->state == STOP_WALKING) {

		if (this->tickCount == 21 || this->tickCount == 35 || this->tickCount == 49) {	//Ticks donde me desplazo (-1 porque despues incremento tick)

			if (this->dir == RIGHT) {

				if (this->pos.x < RIGHT_LIMIT) {	//Checkeo no irme del borde
					this->pos.x += walkSpeed / 3;	//Lo muevo un cacho para la derecha, siguiendo la animacion 
													//si la velocidad es 27 se movera 3 veces 9
				}
			}
			else if (this->dir == LEFT) {

				if (this->pos.x > LEFT_LIMIT) {	//Checkeo no irme del borde
					this->pos.x -= walkSpeed / 3;	//Lo muevo un cacho para la izquierda, siguiendo la animacion 
													//si la velocidad es 27 se movera 3 veces 9
				}
			}
			else {

				error = 1;
			}
		}

		if (this->tickCount == 50) {	//Si llegue a los 50 lo reinicio
			if (this->state == WALKING){
				//Si llegue a los 50 ticks y todavia no se solto la tecla, vuelvo a empezar
				this->tickCount = 1;
			}
			else if (this->state == STOP_WALKING) {
				//Si llegue a los 50 ticks pidiendo parar el movimiento, lo detengo
				this->tickCount = 1;
				this->state = STAND_BY;
			}
		}
		else {
			this->tickCount++;
		}
	}
	else if (this->state == JUMPING || this->state == STOP_JUMPING) {

		if (this->tickCount == 1) {	//Si es el primer tick seteo la velocidad inicial

			this->speed[0] = jumpSpeed * cos(PI / 3);	//Vel en x
			this->speed[1] = jumpSpeed * sin(PI / 3);	//Vel en y
		}

		if (this->tickCount < 10 || this->pos.y >= INF_LIMIT) {	// Sumo ticks en el warm up y cuando cae (no durante el vuelo)
			this->tickCount++;
		}

		if (this->tickCount == 10)	// Solo actualizo la posicion durante el vuelo
		{

			if (this->dir == LEFT && this->pos.x > LEFT_LIMIT)		//Checkeo no irme del borde izquierdo
			{
				this->pos.x -= speed[0];	//Actualizo la posicion en X
			}
			else if (this->dir == RIGHT && this->pos.x < RIGHT_LIMIT)  //Checkeo no irme del borde derecho    , TODO: hardcode de la posicion del borde?
			{
				this->pos.x += speed[0];	//Actualizo la posicion en X
			}

			this->pos.y -= speed[1];	//Actualizo la posicion en Y

			speed[1] -= gravity;		//Aplico la gravedad

			if (this->pos.y >= INF_LIMIT) {	//Checkeo no irme del borde derecho
				this->pos.y = INF_LIMIT;
			}
		}
		
		if (this->tickCount > 15) {
			if (this->state == STOP_JUMPING) {
				this->state = STAND_BY;
			}
			this->tickCount = 1;
		}
	}
	else if (this->state == STAND_BY) {
		//do nothing
	}

	return error;
}

// Devuelve un puntero a la posicion de la imagen en el arreglo.
// La imagen corresponde al estado actual del worm
void* Worm::getImage(unsigned int imagesize) {

	char* image = ((char*)this->walkingImages);		// La de STAND_BY seria la primera

	switch (this->state) {
	case STAND_BY:
		// Es la default
		break;
	case WALKING:
	case STOP_WALKING:
		image = (char*)this->walkingImages;
		if (tickCount >= 6 && tickCount <= 8) {		// WARM_UP
			image += imagesize * (tickCount - 6);
		}
		else if (tickCount >= 9 && tickCount <= 50) {
			unsigned int frame = (tickCount - 9) % 14 + 1;		// Es el frame dentro del loop (los FX de la imagen)
																// Notar que frame es un numero entre 1 y 14
			if (frame <= 8) {
				image += imagesize * (2+frame);
			}
			else if (frame <= 13) {
				image += imagesize * (1 + frame);
			}
			else {	// frame == 14
				image += imagesize * 3;
			}
		}
		break;
	case JUMPING:
	case STOP_JUMPING:


		if (tickCount >= 6 && tickCount <= 15) {	// ------> ASUMO QUE LOS TICKS NO SE CUENTAN MIENTRAS ESTA EN EL AIRE <--------
			image = (char*) this->jumpingImages;
			image += imagesize * (tickCount - 6);
		}

		break;
	default:
		// Estado invalido
		break;
	}

	return image;

}

// Ejemplo de llamada:
//ALLEGRO_BITMAP* actualImage = (ALLEGRO_BITMAP *) getImage(sizeof(ALLEGRO_BITMAP*))