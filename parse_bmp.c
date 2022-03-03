#include "Parse.h"

#pragma region Methods

void parse_bmp_sdl(SDL_Renderer *renderer, const char *file_name)
{
    SDL_Texture *static_texture;
    if (bmpToTexture(file_name, renderer, &static_texture)) return;

    for (;;)
    {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) return;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect target_rect = {128, 128, 64, 64};
        SDL_RenderCopy(renderer, static_texture, NULL, &target_rect);

        SDL_RenderPresent(renderer);
    }
}

#pragma endregion

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    // SDL_RWops *rw = SDL_RWFromFile("Capture.bmp", "rb");

    // Sint64 file_size = SDL_RWsize(rw);

    // SDL_Log("The file size is %lld bytes", file_size);

    // Uint8 *content = SDL_malloc(file_size);

    // SDL_RWread(rw, content, file_size, 1);
    // SDL_RWclose(rw);

    //SDL_Log("First two chars: %c %c", content[0], content[1]);
    // Uint32 bmp_file_size;
    // SDL_memcpy(&bmp_file_size, content + 2, 4);

    // SDL_Log("The BMP file size is %llu bytes", bmp_file_size);

    // Uint32 bmp_pixels_offset;
    // SDL_memcpy(&bmp_pixels_offset, content + 10, 4);

    // SDL_Log("The BMP pixels are at offset %llu bytes", bmp_pixels_offset);

    // Uint32 image_size[2];
    // SDL_memcpy(image_size, content + 18, 8);

    // SDL_Log("The BMP size is %llux%llu", image_size[0], image_size[1]);

    // Uint32 pixels_data_size;
    // SDL_memcpy(&pixels_data_size, content + 34, 4);

    // SDL_Log("The BMP pixels data size is %llu", pixels_data_size);

    // const Uint32 alignment = 4;
    //Uint32 row_size = image_size[0] * 3;
    //SDL_Log("A BMP row is %llu bytes", row_size);
    // Uint32 padded_row_size = (row_size / alignment) * alignment;
    // if (row_size % alignment != 0)
    // {
    //     padded_row_size += alignment;
    // }

    // SDL_Log("A BMP padded row is %llu bytes", padded_row_size);

    // Uint32 full_padded_size = padded_row_size * image_size[1];
    // SDL_Log("A BMP padded pixel data is %llu bytes", full_padded_size);

	SDL_Window* window = SDL_CreateWindow("Parse_bmp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);
	if (!window) goto quit;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) goto quit;

    char *file_name = "Capture.bmp";
    parse_bmp_sdl(renderer, file_name);

quit:
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
