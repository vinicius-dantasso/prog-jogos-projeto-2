
#include "Level0.h"
#include "DungeonGame.h"
#include "Level1.h"

Scene* Level0::scene = nullptr;

void Level0::Init()
{
	// Instanciando cena do Level
	scene = new Scene();

	// Cena Principal apontando para cena do Level
	DungeonGame::sceneMain = scene;

	// Adição do Player, Arma e Interface de Usuário à cena
	scene->Add(DungeonGame::player, MOVING);
	scene->Add(DungeonGame::pistol, STATIC);
	scene->Add(DungeonGame::gui, STATIC);

	// Instanciando builder para ler arquivo de imagem
	builder = new WorldBuilder("Resources/Level_0.png");

	// Setando variável do Player para passar para outro nível como False
	DungeonGame::player->goingTo = false;

	// Instanciando placas
	sign = new Sign("Pressione F para interagir!");
	scene->Add(sign, STATIC);
	sign->MoveTo(window->CenterX() + 255.0f, window->CenterY() - 50.0f);

	sign = new Sign("SPACE para usar dash!");
	scene->Add(sign, STATIC);
	sign->MoveTo(window->CenterX() + 100.0f, 60.0f);

	sign = new Sign("G para usar bombas!");
	scene->Add(sign, STATIC);
	sign->MoveTo(window->CenterX() + 350.0f, 60.0f);
}

void Level0::Finalize()
{
	delete builder;

	// Remover Player, Arma e UI antes de deletar a cena do Level
	scene->Remove(DungeonGame::player, MOVING);
	scene->Remove(DungeonGame::pistol, STATIC);
	scene->Remove(DungeonGame::gui, STATIC);
	delete scene;
}

void Level0::Update()
{
	if(DungeonGame::player->goingTo)
	{
		// Caso Player esteja indo para próximo nível
		DungeonGame::NextLevel<Level1>();
	}
	else
	{
		// Caso contrário, verique Update e Colisão da Cena
		scene->Update();
		scene->CollisionDetection();
	}
}

void Level0::Draw()
{
	scene->Draw();

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}