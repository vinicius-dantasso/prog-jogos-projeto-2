
#ifndef _MENU_SCREEN_H_
#define _MENU_SCREEN_H_

#include "Game.h"
#include "Sprite.h"
#include "Resources.h"
#include "Font.h"

enum MenuID { START, EXIT };

class MenuScreen : public Game
{
private:
	Sprite * background = nullptr;
	Font * font = nullptr;

	int frames = 0;
	int maxFrames = 25;
	bool canDraw = false;

public:
	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_MENUSCREEN_H_
