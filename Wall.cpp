
#include "Wall.h"
#include "DungeonGame.h"

Wall::Wall(float posX, float posY, int types)
{
	spriteType = types;
	switch (spriteType)
	{
	case 0: sprite = new Sprite("Resources/Wall.png"); break;
	case 1: sprite = new Sprite("Resources/Teto3.png"); break;
	}

	type = WALL;

	BBox(new Rect(
		-1.0f * sprite->Width() / 2.0f,
		-1.0f * sprite->Height() / 2.0f,
		sprite->Width() / 2.0f,
		sprite->Height() / 2.0f));

	MoveTo(posX, posY);
}

Wall::~Wall()
{
	delete sprite;
}

void Wall::Update()
{

}

void Wall::Draw()
{
	switch (spriteType)
	{
	case 0: sprite->Draw(x, y, Layer::BACK); break;
	case 1: sprite->Draw(x, y, Layer::FRONT); break;
	}
}