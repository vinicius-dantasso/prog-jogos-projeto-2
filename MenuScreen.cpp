
#include "MenuScreen.h"
#include "DungeonGame.h"
#include "Level0.h"

void MenuScreen::Init()
{
	background = new Sprite("Resources/Menu_Screen.png");

	font = new Font("Resources/m5x7.png");
	font->Spacing(85);
}

void MenuScreen::Finalize()
{
    delete background;
	delete font;
}

void MenuScreen::Update()
{
	if (window->KeyDown(VK_RETURN)){
		DungeonGame::audio->Play(TRANSITION, false);
		DungeonGame::NextLevel<Level0>();
	}

	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	if (!canDraw)
	{
		frames++;
		if (frames >= maxFrames)
		{
			frames = 0;
			canDraw = true;
		}
	}
}

void MenuScreen::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);
	Color black(0.0f, 0.0f, 0.0f, 1.0f);

	if (canDraw)
	{
		font->Draw(window->CenterX() - 215.0f, window->CenterY() + 10.0f, "> PRESS ENTER <", black, Layer::LOWER, 0.4f);
		font->Draw(window->CenterX() - 220.0f, window->CenterY() + 10.0f, "> PRESS ENTER <", white, Layer::UPPER, 0.4f);

		frames++;
		if (frames >= maxFrames)
		{
			frames = 0;
			canDraw = false;
		}
	}

    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}