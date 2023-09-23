
#include "Level0.h"
#include "DungeonGame.h"

void Level0::Init()
{
	DungeonGame::scene = new Scene();

	DungeonGame::scene->Add(DungeonGame::player, MOVING);
	DungeonGame::scene->Add(DungeonGame::pistol, STATIC);
	DungeonGame::scene->Add(DungeonGame::gui, STATIC);

	builder = new WorldBuilder("Resources/Level_0.png");
}

void Level0::Finalize()
{
	DungeonGame::scene->Remove(DungeonGame::player, MOVING);
	delete DungeonGame::scene;
	delete builder;
}

void Level0::Update()
{
	if(DungeonGame::player->Life() > 0)
	{
		DungeonGame::scene->Update();
		DungeonGame::scene->CollisionDetection();
	}
}

void Level0::Draw()
{
	DungeonGame::scene->Draw();

	if (DungeonGame::viewBBox)
		DungeonGame::scene->DrawBBox();
}