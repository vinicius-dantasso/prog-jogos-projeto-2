
#include "Sign.h"
#include "Scripts.h"
#include "DungeonGame.h"

Sign::Sign(string write)
{
	sprite = new Sprite("Resources/Sign.png");
	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	text = write;
}

Sign::~Sign()
{
	delete sprite;
	delete font;
}

void Sign::Update()
{
	if (Scripts::distance_to_object(this, DungeonGame::player) <= 40.0f)
		canDraw = true;
	else
		canDraw = false;
}

void Sign::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);

	if (canDraw)
		font->Draw(x - 50.0f, y - 20.0f, text, white, Layer::FRONT, 0.1f);

	sprite->Draw(x, y, z);
}