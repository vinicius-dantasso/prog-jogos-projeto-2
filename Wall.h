
#ifndef _WALL_H_
#define _WALL_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

class Wall : public Object
{
private:
	Sprite* sprite = nullptr;

public:
	Wall(float posX, float posY);
	~Wall();

	void Update();
	void Draw();
};

#endif // !_WALL_H_
