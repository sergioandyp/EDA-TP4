#include "Worm.h"


//constructor
Worm::Worm(){
	
	this->tickCount = 0;
	this->state = STAND_BY;
	this->jumpingImages = 0;
	this->walkingImages = 0;
}

// getters
unsigned int Worm::getX() {

	return this->pos.x;
}
unsigned int Worm::getY() {

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



// setters (devuelve 1 si hubo error)
bool Worm::setX(unsigned int x) {

	this->pos.x = x;
	return 0;	//TODO: Como puede tener esto un error?		//  Avisar si se toca un limite?
}
bool Worm::setY(unsigned int y) {

	this->pos.y = y;
	return 0;	//TODO: Como puede tener esto un error?
}
bool Worm::setDirection(DIRECTION dire) {

	this->dir = dire;
	return 0;	//TODO: Como puede tener esto un error?
}
bool Worm::setWalkImages(void* w_images) {

	this->walkingImages = w_images;
	return 0;	//TODO: Como puede tener esto un error?

}
bool Worm::setJumpImages(void* j_images) {
	
	this->jumpingImages = j_images;
	return 0;	//TODO: Como puede tener esto un error?

}


// Movement
bool Worm::jump() {	// Setea estado a JUMP y reinicia tickCount

	this->state = JUMPING;
	this->tickCount = 1;

	return true;	// No se chequea si estaba en movimiento??
}
bool Worm::walk() {		// Setea estado a WALK y reinicia tickCount

	this->state = WALKING;
	this->tickCount = 1;

	return true;	// No se chequea si estaba en movimiento??
}
bool Worm::stop() {		//Va a parar el movimiento del worm solamente si pasaron menos de 8 frames

	int error = 0;

	if (this->tickCount <= 8) {

		this->state = STAND_BY;
	}
	else if (this->tickCount <= 50 && this->state == WALKING){

		this->state = STOP_WALKING;	//En este caso quiero avisar que el movimiento debe detenerse ni bien termine la animacion
	}
	else {

	}

	return error;
}

bool Worm::update(double walkSpeed, double jumpSpeed) {

	int error = 0;

	if (this->state == WALKING || this->state == STOP_WALKING) {

		if (this->tickCount == 22 || this->tickCount == 36 || this->tickCount == 50) {	//Ticks donde me desplazo

			if (this->dir == RIGHT) {

				if (this->pos.x < 1212) {	//Checkeo no irme del borde, TODO: hardcode de la posicion del borde?
					this->pos.x += walkSpeed / 3;	//Lo muevo un cacho para la derecha, siguiendo la animacion 
													//si la velocidad es 27 se movera 3 veces 9
				}
			}
			else if (this->dir == LEFT) {

				if (this->pos.x > 701) {	//Checkeo no irme del borde
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
	else if (this->state == STAND_BY) {

		//do nothing
	}

	return 0;	// Creo que aca no hace falta devolver nada
}

// Devuelve un puntero a la posicion de la imagen en el arreglo.
// La imagen corresponde al estado actual del worm
void* Worm::getImage(unsigned int imagesize) {

	char* image = ((char*)this->walkingImages);		// La de STAND_BY seria la primera?

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
				image += imagesize * (3+frame);
			}
			else if (frame <= 13) {
				image += imagesize * (2 + frame);
			}
			else {	// frame == 14
				image += imagesize * 3;
			}
		}
		break;
	case JUMPING:
	case STOP_JUMPING:

		image = (char*) this->jumpingImages;

		if (tickCount >= 6 && tickCount <= 15) {	// ------> ASUMO QUE LOS TICKS NO SE CUENTAN MIENTRAS ESTA EN EL AIRE <--------
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