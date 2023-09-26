#include "DungeonGame.h"
#include "GameOver.h"
#include "Level4.h"
#include "Level5.h"

Scene* Level4::scene = nullptr;

void Level4::Init()
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
	builder = new WorldBuilder("Resources/Level_4.png");
}

void Level4::Finalize()
{
	delete builder;

	// Remover Player, Arma e UI antes de deletar a cena do Level
	scene->Remove(DungeonGame::player, MOVING);
	scene->Remove(DungeonGame::pistol, STATIC);
	scene->Remove(DungeonGame::gui, STATIC);
	delete scene;
}

void Level4::Update()
{
	if (DungeonGame::player->goingTo)
	{
		// Caso Player esteja indo para próximo nível 
		DungeonGame::NextLevel<Level5>();

	}
	else if (DungeonGame::player->isDead)
	{
		DungeonGame::NextLevel<GameOver>();
		DungeonGame::player->Reset();
	}
	else
	{
		// Caso contrário, verique Update e Colisão da Cena
		scene->Update();
		scene->CollisionDetection();
	}
}

void Level4::Draw()
{
	scene->Draw();

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}