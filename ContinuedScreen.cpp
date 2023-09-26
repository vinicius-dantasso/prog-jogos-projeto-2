
#include "ContinuedScreen.h"
#include "DungeonGame.h"
#include "MenuScreen.h"

void ContinuedScreen::Init()
{
	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	down = 0.0f;
	frames = 0;
	maxFrames = 25;
}

void ContinuedScreen::Finalize()
{
	delete font;
}

void ContinuedScreen::Update()
{
	if (window->KeyPress(VK_RETURN))
		window->Close();

	if (down <= (window->Height() / 2.0f) - 100.0f)
		down += 2.0f;

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

void ContinuedScreen::Draw()
{
	Color white(1.0f, 1.0f, 1.0f, 1.0f);
	Color black(0.0f, 0.0f, 0.0f, 1.0f);

	font->Draw(window->CenterX() - 420.0f, (-10.0f + down), "Thanks For Playing The Demo!", white, Layer::FRONT, 0.4f);

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
}