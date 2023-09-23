
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Player.h"
#include "Pistol.h"
#include "Gui.h"
#include "WorldBuilder.h"

WorldBuilder * builder = nullptr;

void DebugLevel::Init()
{
	DungeonGame::scene = new Scene();

	DungeonGame::scene->Add(DungeonGame::player, MOVING);
	
	DungeonGame::scene->Add(DungeonGame::pistol, STATIC);

	DungeonGame::scene->Add(DungeonGame::gui, STATIC);

	builder = new WorldBuilder("Resources/DebugMap.png");
}

void DebugLevel::Finalize()
{
	DungeonGame::scene->Remove(DungeonGame::player, MOVING);
	delete DungeonGame::scene;
	delete builder;
}

void DebugLevel::Update()
{
	DungeonGame::scene->Update();
	DungeonGame::scene->CollisionDetection();
}

void DebugLevel::Draw()
{
	DungeonGame::scene->Draw();

	if (DungeonGame::viewBBox)
		DungeonGame::scene->DrawBBox();
}
