
#ifndef _CONTINUED_SCREEN_H_
#define _CONTINUED_SCREEN_H_

#include "Game.h"
#include "Font.h"

class ContinuedScreen : public Game
{
private:
	Font* font;

	int frames;
	int maxFrames;
	float down;
	bool canDraw = false;

public:
	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_CONTINUED_SCREEN_H_
