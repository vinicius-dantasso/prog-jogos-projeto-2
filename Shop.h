
#ifndef _SHOP_H_
#define _SHOP_H_

#include "Game.h"
#include "Scene.h"
#include "Heart.h"
#include "Font.h"
#include "WorldBuilder.h"

class Shop : public Game
{
private:
	WorldBuilder* builder;
	Heart* heart;
	Font* font;

public:
	static Scene* scene;

	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_SHOP_H_
