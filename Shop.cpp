
#include "Shop.h"
#include "DungeonGame.h"
#include "ContinuedScreen.h"

Scene* Shop::scene = nullptr;

void Shop::Init()
{
	font = new Font("Resources/m5x7.png");
	font->Spacing(85);

	scene = new Scene();
	DungeonGame::sceneMain = scene;
	DungeonGame::onShop = true;

	scene->Add(DungeonGame::player, MOVING);
	DungeonGame::player->MoveTo(864.0f, 640.0f);

	scene->Add(DungeonGame::pistol, STATIC);
	scene->Add(DungeonGame::gui, STATIC);

	builder = new WorldBuilder("Resources/Shop.png");

	DungeonGame::bomb = new Bomb(window->CenterX() + 130.0f, window->CenterY() - 55.0f, BOMBITEM);
	scene->Add(DungeonGame::bomb, MOVING);

	heart = new Heart(window->CenterX() + 320.0f, window->CenterY() - 50.0f);
	scene->Add(heart, STATIC);

	DungeonGame::player->goingTo = false;
}

void Shop::Finalize()
{
	delete builder;
	delete font;

	// Remover Player, Arma e UI antes de deletar a cena do Level
	scene->Remove(DungeonGame::player, MOVING);
	scene->Remove(DungeonGame::pistol, STATIC);
	scene->Remove(DungeonGame::gui, STATIC);
	delete scene;
}

void Shop::Update()
{
	if (DungeonGame::player->goingTo)
	{
		// Caso Player esteja indo para próximo nível
		DungeonGame::NextLevel<ContinuedScreen>();
	}
	else
	{
		// Caso contrário, verique Update e Colisão da Cena
		scene->Update();
		scene->CollisionDetection();
	}
}

void Shop::Draw()
{
	scene->Draw();

	Color white (1.0f, 1.0f, 1.0f, 1.0f);

	font->Draw(window->CenterX() + 100.0f, window->CenterY(), "30 Moedas", white, Layer::FRONT, 0.1f);
	font->Draw(window->CenterX() + 300.0f, window->CenterY(), "10 Moedas", white, Layer::FRONT, 0.1f);

	if (DungeonGame::viewBBox)
		scene->DrawBBox();
}