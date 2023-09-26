
#include "Transition.h"

Transition::Transition()
{
	transition = new Sprite("Resources/Transition.png");
	MoveTo(window->CenterX(), window->CenterY());
}

Transition::~Transition()
{
	delete transition;
}

void Transition::Update()
{
	if (y <= window->CenterY())
	{
		upper += 10.0f;
		lower -= 10.0f;

		Translate(0.0f, upper * gameTime);
	}
	else
		finalized = true;
}

void Transition::Draw()
{
	transition->Draw(window->CenterX(), -360.0f + upper, Layer::FRONT);
	transition->Draw(window->CenterX(), (window->Height() + 360.0f) - lower, Layer::FRONT);
}