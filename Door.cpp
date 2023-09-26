
#include "Door.h"
#include "DungeonGame.h"
#include "Level1.h"

Door::Door(float posX, float posY, uint types)
{
	tile = new TileSet("Resources/Door.png", 64, 44, 2, 2);
	anim = new Animation(tile, 0.12f, false);

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
		if (state != DOOROPEN){ 
			DungeonGame::audio->Play(OPENDOOR);
			state =	DOOROPEN;
		}

	anim->Select(state);
	anim->NextFrame();
}

void Door::Draw()
{
	if (type == DOORCLOSED)
		anim->Draw(x, y, Layer::MIDDLE);
	else
		anim->Draw(x, y, Layer::FRONT);
}