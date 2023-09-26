
#include "Wall.h"
#include "DungeonGame.h"

Wall::Wall(float posX, float posY, int spriteTypes, int types)
{
	spriteType = spriteTypes;
	switch (spriteType)
	{
	case PAREDE: 
		sprite = new Sprite("Resources/Wall.png");
		break;
	case TETO: 
		sprite = new Sprite("Resources/Teto3.png");
		break;
	case MURO:
		sprite = new Sprite("Resources/Obstacle2.png");
		break;
	case CERCA:
		sprite = new Sprite("Resources/Fence_Wall2.png");
		break;
	}

	type = types;

	if(spriteTypes != CERCA)
		BBox(new Rect(
			-1.0f * sprite->Width() / 2.0f,
			-1.0f * sprite->Height() / 2.0f,
			sprite->Width() / 2.0f,
			sprite->Height() / 2.0f));
	else
		BBox(new Rect(
			-1.0f * sprite->Width() / 4.0f,
			-1.0f * sprite->Height() / 4.0f,
			sprite->Width() / 4.0f,
			sprite->Height() / 4.0f));

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
	case PAREDE: sprite->Draw(x, y, Layer::BACK); break;
	case TETO: sprite->Draw(x, y, Layer::LOWER); break;
	case MURO: sprite->Draw(x, y, Layer::UPPER); break;
	case CERCA: sprite->Draw(x, y, Layer::UPPER); break;
	}
}