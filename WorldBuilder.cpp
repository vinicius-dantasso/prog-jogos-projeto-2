
#include "WorldBuilder.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "DebugLevel.h"
#include "DungeonGame.h"
#include "Wall.h"
#include "Floor.h"

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
				Wall* wall1 = new Wall(xx * 32, yy * 32, TETO);
				DebugLevel::scene->Add(wall1, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 255
				&& image[3 * (xx + (yy * width)) + 1] == 200
				&& image[3 * (xx + (yy * width)) + 2] == 255
				)
			{
				Wall* wall = new Wall(xx * 32, yy * 32, PAREDE);
				DebugLevel::scene->Add(wall,STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 76
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 0
				)
			{
				Floor* floor = new Floor(xx * 32, yy * 32, LIMPO);
				DebugLevel::scene->Add(floor, STATIC);
			}

			if (image[3 * (xx + (yy * width))] == 0
				&& image[3 * (xx + (yy * width)) + 1] == 255
				&& image[3 * (xx + (yy * width)) + 2] == 33
				)
			{
				Floor* floor = new Floor(xx * 32, yy * 32, PEDRA);
				DebugLevel::scene->Add(floor, STATIC);
			}

		}

	}

	stbi_image_free(image);
}

WorldBuilder::~WorldBuilder()
{}