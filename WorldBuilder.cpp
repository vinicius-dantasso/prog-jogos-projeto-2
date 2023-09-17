
#include "WorldBuilder.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Wall.h"

WorldBuilder::WorldBuilder(const char* path)
{
	unsigned char* image = stbi_load(path, &width, &height, &channels, 3);

	for (int xx = 0; xx < width; xx++)
	{

		for (int yy = 0; yy < height; yy++)
		{

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				// Cor Branca Adicionar ...
				Wall* wall = new Wall(xx * 32, yy * 32);
				DebugLevel::scene->Add(wall, STATIC);

			}

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 0
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				// Cor Vermelha Adicionar ...
				DungeonGame::player->MoveTo(xx * 32, yy * 32);
			}

		}

	}

	stbi_image_free(image);
}

WorldBuilder::~WorldBuilder()
{}