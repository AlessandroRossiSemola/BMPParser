#include "Parse.h"

#pragma region Methods

void parseBmpSdl(SDL_Renderer *renderer, const char *file_name)
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//BG Color
        SDL_RenderClear(renderer);

        SDL_Rect target_rect = {128, 128, 128, 128};//The rect for the img
        SDL_RenderCopy(renderer, static_texture, NULL, &target_rect);

        SDL_RenderPresent(renderer);
    }
}

#pragma endregion

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Parse_bmp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);
	if (!window) goto quit;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) goto quit;

    char *file_name = "Capture.bmp";
    parseBmpSdl(renderer, file_name);

quit:
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
