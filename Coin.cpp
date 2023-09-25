
#include "Coin.h"
#include "DungeonGame.h"
#include "Scripts.h"

Coin::Coin(float posX, float posY)
{
	tile = new TileSet("Resources/Coin2.png", 14, 16, 4, 4);
	anim = new Animation(tile, 0.12f, true);

	uint SeqCoin[4] = { 0,1,2,3 };

	anim->Add(COINITEM, SeqCoin, 4);

	spd = 100.0f;
	state = COINITEM;
	type = COIN;

	BBox(new Rect(-10, -10, 12, 12));
	MoveTo(posX, posY);
}

Coin::~Coin()
{
	delete tile;
	delete anim;
}

void Coin::OnCollision(Object* obj)
{
	if (obj->Type() == PLAYER)
	{
		DungeonGame::coinTotal++;
		DungeonGame::sceneMain->Delete(this, STATIC);
	}
}

void Coin::Update()
{
	if (Scripts::distance_to_object(this, DungeonGame::player) <= 60.0f)
	{
		float dir = Scripts::point_direction(x, y, DungeonGame::player->X(), DungeonGame::player->Y());
		hSpd = Scripts::lengthdir_x(spd, dir);
		vSpd = Scripts::lengthdir_y(spd, dir);

		Translate(hSpd * gameTime, vSpd * gameTime);
	}

	anim->Select(state);
	anim->NextFrame();
}

void Coin::Draw()
{
	anim->Draw(x, y, Layer::MIDDLE);
}