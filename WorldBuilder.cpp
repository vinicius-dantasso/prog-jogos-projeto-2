
#include "WorldBuilder.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "DungeonGame.h"
#include "Wall.h"
#include "Floor.h"
#include "Trap.h"
#include "Bee.h"
#include "Mage.h"
#include "BugHole.h"
#include "Bug.h"
#include "Door.h"

WorldBuilder::WorldBuilder(const char* path)
{
	unsigned char* image = stbi_load(path, &width, &height, &channels, 3);

	for (int xx = 14; xx < width; xx++)
	{

		for (int yy = 0; yy < height; yy++)
		{

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// TETO COLISÃO HORIZONTAL
				Wall* wall1 = new Wall(xx * 32.0f, yy * 32.0f, TETO, HWALL);
				DungeonGame::sceneMain->Add(wall1, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 188
				)
			{
				// TETO COLISÃO VERTICAL
				Wall* wall1 = new Wall(xx * 32.0f, yy * 32.0f, TETO, VWALL);
				DungeonGame::sceneMain->Add(wall1, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 188
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// MURO
				Wall* wall = new Wall(xx * 32.0f, yy * 32.0f, MURO, WALL);
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);
				DungeonGame::sceneMain->Add(wall, STATIC);
				DungeonGame::sceneMain->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 200
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE COLISÃO VERTICAL
				Wall* wall = new Wall(xx * 32.0f, yy * 32.0f, PAREDE, VWALL);
				DungeonGame::sceneMain->Add(wall,STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 188
				&& image[3 * (xx + (yy * width)) + 1] == 178
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// PAREDE COM CERCA
				Wall* wall = new Wall(xx * 32.0f, yy * 32.0f, CERCA, WALL);
				DungeonGame::sceneMain->Add(wall, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 76
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// CHÃO LIMPO
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);
				DungeonGame::sceneMain->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 76
				&& image[3 * (xx + (yy * width)) + 1] == 170
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// CHÃO PEDRA
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, PEDRA);
				DungeonGame::sceneMain->Add(floor, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 0
				&& image[3 * (xx + (yy * width)) + 1] == 38
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// ARMADILHA DE ESPINHOS
				Trap* trap = new Trap(xx * 32.0f, yy * 32.0f);
				DungeonGame::sceneMain->Add(trap, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 0
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// INIMIGO ABELHA
				Bee* bee = new Bee(xx * 32.0f, yy * 32.0f);
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);
				DungeonGame::sceneMain->Add(bee, MOVING);
				DungeonGame::sceneMain->Add(floor, STATIC);
				DungeonGame::enemiesTotal++;
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 100
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// INIMIGO MAGO
				Mage* mage = new Mage(xx * 32.0f, yy * 32.0f);
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);
				DungeonGame::sceneMain->Add(mage, MOVING);
				DungeonGame::sceneMain->Add(floor, STATIC);
				DungeonGame::enemiesTotal++;
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 0
				&& image[3 * (xx + (yy * width)) + 2] == 125
				)
			{
				// INIMIGO INSETO
				Bug* bug = new Bug(xx * 32.0f, yy * 32.0f);
				BugHole* bugHole = new BugHole(xx * 32.0f, yy * 32.0f);
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);

				DungeonGame::sceneMain->Add(bug, MOVING);
				DungeonGame::sceneMain->Add(bugHole, MOVING);
				DungeonGame::sceneMain->Add(floor, STATIC);
				DungeonGame::enemiesTotal++;
			}

			else if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 216
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// PORTA QUE IRÁ ABRIR
				Door* door = new Door(xx * 32.0f, yy * 32.0f, DOOROPENNED);
				Floor* floor = new Floor(xx * 32.0f, yy * 32.0f, LIMPO);
				DungeonGame::sceneMain->Add(floor, STATIC);
				DungeonGame::sceneMain->Add(door, STATIC);
			}

			else if (image[3 * (xx + (yy * width))] == 206
				&& image[3 * (xx + (yy * width)) + 1] == 148
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// PORTA QUE PERMACE FECHADA
				Door* door = new Door(xx * 32.0f, yy * 32.0f, DOORCLOSED);
				DungeonGame::sceneMain->Add(door, STATIC);
			}

		}

	}

	stbi_image_free(image);
}

WorldBuilder::~WorldBuilder()
{}