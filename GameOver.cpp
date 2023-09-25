
#include "GameOver.h"
#include "Level0.h"
#include "MenuScreen.h"
#include "DungeonGame.h"

void GameOver::Init()
{
	title = new Sprite("Resources/GameOverTitle.png");
	font = new Font("Resources/m5x7.png");
	font->Spacing(85);
}

void GameOver::Finalize()
{
	delete title;
	delete font;
}

void GameOver::Update()
{
	if (window->KeyPress(VK_RETURN))
		DungeonGame::NextLevel<Level0>();

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

void GameOver::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);
	Color black(0.0f, 0.0f, 0.0f, 1.0f);

	if (canDraw)
	{
		font->Draw(window->CenterX() - 215.0f, window->CenterY() + 50.0f, "> PRESS ENTER <", black, Layer::LOWER, 0.4f);
		font->Draw(window->CenterX() - 220.0f, window->CenterY() + 50.0f, "> PRESS ENTER <", white, Layer::UPPER, 0.4f);

		frames++;
		if (frames >= maxFrames)
		{
			frames = 0;
			canDraw = false;
		}
	}

	title->Draw(window->CenterX(), window->CenterY() - 100.0f);
}