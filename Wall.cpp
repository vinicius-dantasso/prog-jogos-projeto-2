
#include "Wall.h"
#include "DungeonGame.h"

Wall::Wall(float posX, float posY)
{
	sprite = new Sprite("Resources/Wall.png");
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
	sprite->Draw(x, y, z);
}