
#include "Door.h"
#include "DungeonGame.h"
#include "Level1.h"
#include <string>

Door::Door(float posX, float posY, uint types)
{
	tile = new TileSet("Resources/Door.png", 64, 44, 2, 2);
	anim = new Animation(tile, 0.12f, false);

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	uint SeqClose[1] = { 0 };
	uint SeqOpen[1] = { 1 };

	anim->Add(DOORCLOSE, SeqClose, 1);
	anim->Add(DOOROPEN, SeqOpen, 1);

	type = types;
	state = DOORCLOSE;

	BBox(new Rect(-32, -32, 32, 24));
	MoveTo(posX, posY);
}

Door::~Door()
{
	delete tile;
	delete anim;
}

void Door::OnCollision(Object* obj)
{
	if (state == DOOROPEN && obj->Type() == PLAYER)
	{
		DungeonGame::floorNum++;
		DungeonGame::player->goingTo = true;
	}
}

void Door::Update()
{
	if (type == DOOROPENNED && DungeonGame::enemiesTotal <= 0)
		state = DOOROPEN;

	anim->Select(state);
	anim->NextFrame();
}

void Door::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);
	std::string str = std::to_string(state);
	font->Draw(x, y + 40.0f, str, white, Layer::FRONT, 0.3f);

	if (type == DOORCLOSED)
		anim->Draw(x, y, Layer::MIDDLE);
	else
		anim->Draw(x, y, Layer::FRONT);
}