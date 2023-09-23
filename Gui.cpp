
#include "Gui.h"
#include "DungeonGame.h"
#include <string>

Gui::Gui()
{
	main = new Sprite("Resources/GUI.png");
	gun = new Sprite("Resources/Pistol_Solo.png");
	ammo = new Sprite("Resources/Ammo.png");
	heart = new Sprite("Resources/Heart.png");

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);
	
	MoveTo(window->CenterX() - 410.0f, window->CenterY());
}

Gui::~Gui()
{
	delete main;
	delete gun;
	delete ammo;
	delete heart;
	delete font;
}

void Gui::Update()
{

}

void Gui::Draw()
{
	main->Draw(x, y, Layer::UPPER);

	Color black(0.0f, 0.0f, 0.0f, 1.0f);
	std::string level = std::to_string(DungeonGame::floorNum);

	font->Draw(250.0f, 200.0f, level, black, Layer::FRONT, 0.8f);

	if(DungeonGame::pistol->item)
	{
		gun->Draw(window->CenterX() - 430.0f, window->CenterY() + 120.0f, Layer::FRONT, 1.0f);

		for (int i = 1; i <= DungeonGame::pistol->ammo; i++)
			ammo->Draw((window->CenterX() - 585.0f) + ((i - 1) * 16), window->CenterY() + 217.0f, Layer::FRONT, 1.0f);
	}

	for (int i = 1; i <= DungeonGame::player->Life(); i++)
		heart->Draw((window->CenterX() - 560.0f) + ((i - 1) * 64), window->CenterY() - 20.0f, Layer::FRONT, 1.5f);
}