
#include "Floor.h"

Floor::Floor(float posX, float posY, int type)
{
	switch (type)
	{
	case 0: sprite = new Sprite("Resources/Floor2.png"); break;
	case 1: sprite = new Sprite("Resources/Floor1.png"); break;
	}

	MoveTo(posX, posY);
}

Floor::~Floor()
{
	delete sprite;
}