
#ifndef _GUI_H_
#define _GUI_H_

#include "Object.h"
#include "Sprite.h"
#include "Font.h"

class Gui : public Object
{
private:
	Sprite* main;
	Sprite* gun;
	Sprite* ammo;
	Sprite* heart;
	Sprite* bombs;
	Sprite* coin;
	Font* font;

public:
	Gui();
	~Gui();

	void Update();
	void Draw();
};

#endif // !_GUI_H_
