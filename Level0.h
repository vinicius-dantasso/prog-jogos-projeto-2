
#ifndef _LEVEL0_H_
#define _LEVEL0_H_

#include "Game.h"
#include "WorldBuilder.h"
#include "Sign.h"
#include "Scene.h"

class Level0 : public Game
{
private:
	WorldBuilder * builder; // Leitor de imagem para gerar a Cena
	Sign * sign; // Placa com informações

public:
	static Scene* scene; // Cena do Level

	void Init();
	void Finalize();
	void Update();
	void Draw();
};

#endif // !_LEVEL_MANAGER_H_
