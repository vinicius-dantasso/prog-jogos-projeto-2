
#include "Level1.h"
#include "DungeonGame.h"

Scene* Level1::scene = nullptr;

void Level1::Init()
{
	// Instanciando cena do Level
	scene = new Scene();

	// Cena Principal apontando para cena do Level
	DungeonGame::sceneMain = scene;

	// Adição do Player, Arma e Interface de Usuário à cena e sua posição inicial no novo Level
	scene->Add(DungeonGame::player, MOVING);
	DungeonGame::player->MoveTo(864.0f, 640.0f);

	scene->Add(DungeonGame::pistol, STATIC);
	scene->Add(DungeonGame::gui, STATIC);

	// Setando variável do Player para passar para outro nível como False
	DungeonGame::player->goingTo = false;

	// Instanciando builder para ler arquivo de imagem
	builder = new WorldBuilder("Resources/Level_1.png");
}

void Level1::Finalize()
{
	delete builder;

	// Remover Player, Arma e UI antes de deletar a cena do Level
	scene->Remove(DungeonGame::player, MOVING);
	scene->Remove(DungeonGame::pistol, STATIC);
	scene->Remove(DungeonGame::gui, STATIC);
	delete scene;
}

void Level1::Update()
{
	if (DungeonGame::player->goingTo)
	{
		// Caso Player esteja indo para próximo nível 

	}
	else
	{
		// Caso contrário, verique Update e Colisão da Cena
		scene->Update();
		scene->CollisionDetection();
	}
}

void Level1::Draw()
{
	scene->Draw();

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}