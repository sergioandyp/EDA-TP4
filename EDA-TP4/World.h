#ifndef _WORLD_H_

#include "Worm.h"

typedef enum EVENT { QUIT, KEY_A, KEY_W, KEY_D, KEY_UP, KEY_LEFT, KEY_RIGHT };

class World {
public:
	Worm worms[2];
	double gravity;
	double walkSpeed;
	double jumpSpeed;

	void dispatcher(EVENT event);

};

#endif