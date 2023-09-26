
#ifndef _DOOR_H_
#define _DOOR_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"

enum DoorState {DOORCLOSE, DOOROPEN};

class Door : public Object
{
private:
	TileSet* tile;
	Animation* anim;

public:
	uint state;

	Door(float posX, float posY, uint types);
	~Door();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_DOOR_H_
