#include "DungeonGame.h"
#include "GameOver.h"
#include "Level5.h"
#include "Shop.h"

Scene* Level5::scene = nullptr;

void Level5::Init()
{
	// Instanciando cena do Level
	scene = new Scene();

	// Cena Principal apontando para cena do Level
	DungeonGame::sceneMain = scene;

	// Adi��o do Player, Arma e Interface de Usu�rio � cena e sua posi��o inicial no novo Level
	scene->Add(DungeonGame::player, MOVING);
	DungeonGame::player->MoveTo(864.0f, 640.0f);

	scene->Add(DungeonGame::pistol, STATIC);
	scene->Add(DungeonGame::gui, STATIC);

	// Setando vari�vel do Player para passar para outro n�vel como False
	DungeonGame::player->goingTo = false;

	// Instanciando builder para ler arquivo de imagem
	builder = new WorldBuilder("Resources/Level_5.png");
}

void Level5::Finalize()
{
	delete builder;

	// Remover Player, Arma e UI antes de deletar a cena do Level
	scene->Remove(DungeonGame::player, MOVING);
	scene->Remove(DungeonGame::pistol, STATIC);
	scene->Remove(DungeonGame::gui, STATIC);
	delete scene;
}

void Level5::Update()
{
	if (DungeonGame::player->goingTo)
	{
		// Caso Player esteja indo para pr�ximo n�vel 
		DungeonGame::NextLevel<Shop>();

	}
	else if (DungeonGame::player->isDead)
	{
		DungeonGame::NextLevel<GameOver>();
		DungeonGame::player->Reset();
	}
	else
	{
		// Caso contr�rio, verique Update e Colis�o da Cena
		scene->Update();
		scene->CollisionDetection();
	}
}

void Level5::Draw()
{
	scene->Draw();

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}