
#include "WorldBuilder.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
				// Ao instanciar um objeto no mapa, sempre multiplicar
				// xx e yy por 32

			}

		}

	}

	stbi_image_free(image);
}

WorldBuilder::~WorldBuilder()
{}