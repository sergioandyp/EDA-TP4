#ifndef _WORLD_H_
#define _WORLD_H_

#include "Worm.h"

enum EVENT { QUIT,
					DOWN_KEY_A, DOWN_KEY_W, DOWN_KEY_D, DOWN_KEY_UP, DOWN_KEY_LEFT, DOWN_KEY_RIGHT,
					UP_KEY_A, UP_KEY_W, UP_KEY_D, UP_KEY_UP, UP_KEY_LEFT, UP_KEY_RIGHT
};

class World {
public:

	//constructor
	World();

	Worm worms[2];
	double gravity;
	double walkSpeed;
	double jumpSpeed;

	void* backgroundImg;

	void dispatcher(EVENT event);

};

#endif