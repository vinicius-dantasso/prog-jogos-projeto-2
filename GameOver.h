
#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "Game.h"
#include "Sprite.h"
#include "Font.h"

class GameOver : public Game
{
private:
	Sprite* title;
	Font* font;

	int frames = 0;
	int maxFrames = 25;
	bool canDraw = false;

public:
	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_GAME_OVER_H_
