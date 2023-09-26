
#include "Heart.h"
#include "Scripts.h"
#include "DungeonGame.h"

Heart::Heart(float posX, float posY)
{
	sprite = new Sprite("Resources/Heart.png");

	quant = 3;

	MoveTo(posX, posY);
}

Heart::~Heart()
{
	delete sprite;
}

void Heart::Update()
{
	float dist = Scripts::distance_to_object(this, DungeonGame::player) <= 60;
	bool keyBuy = window->KeyPress('F');
	bool coins = DungeonGame::coinTotal >= 10;
	bool playerLife = DungeonGame::player->Life() < DungeonGame::player->MaxLife();

	if (dist && keyBuy && coins && playerLife && quant > 0)
	{
		quant--;
		DungeonGame::coinTotal -= 10;
		DungeonGame::player->SetLife(1);
	}

	if (quant <= 0)
		DungeonGame::sceneMain->Delete(this, STATIC);
}

void Heart::Draw()
{
	sprite->Draw(x,y,Layer::FRONT, 0.6f);
}