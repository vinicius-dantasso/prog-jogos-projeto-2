#ifndef _Level4_H_
#define _Level4_H_

#include "Game.h"
#include "WorldBuilder.h"
#include "Scene.h"

class Level4 : public Game
{
private:
	WorldBuilder* builder; // Leitor de imagem para gerar a Cena

public:
	static Scene* scene; // Cena do Level

	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_Level4_H_

