
#ifndef _WALL_H_
#define _WALL_H_

#include "Types.h"
#include "Object.h"
#include "Sprite.h"

enum WallType {PAREDE, TETO, MURO, CERCA};

class Wall : public Object
{
private:
	Sprite* sprite = nullptr;
	int spriteType;

public:
	Wall(float posX, float posY, int spritetypes, int types);
	~Wall();

	void Update();
	void Draw();
};

#endif // !_WALL_H_
