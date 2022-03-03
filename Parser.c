#include <stdio.h>
#include "Parse.h"

int bmpToTexture(const char *file_name, SDL_Renderer *renderer, SDL_Texture **static_texture)
{
    Sint8 *content;
    if (openFile(file_name, &content)) return -1;

    Sint32 bmp_file_size;
    SDL_memcpy(&bmp_file_size, content + 2, 4);
    SDL_Log("The BMP file size is %llu bytes", bmp_file_size);//Total size of img in bytes

    Sint32 image_size[2];
    SDL_memcpy(image_size, content + 18, 8);
    SDL_Log("The BMP size is %llux%llu", image_size[0], image_size[1]);//Whidth and Height of img in px

    Sint32 row_size = image_size[0] * sdl_channels;
    SDL_Log("The BMP row size is %llu", row_size);//Width * channels

    Sint32 padded_row_size = (row_size / sdl_alignment) * sdl_alignment;
    if (row_size % sdl_alignment) padded_row_size += sdl_alignment;
    SDL_Log("The BMP padded row size  is %llu", padded_row_size);

    Sint8 *head = startPoint(content);
    SDL_Log("the start point: %llu", *head);//Content+offset(where the pixels bytes starts)

    Sint8 *pixels = SDL_malloc(image_size[0]*image_size[1]*sdl_channels);
    SDL_Log("total amount of pixels bytes: %llu", *pixels);//Content+offset(where the pixels bytes starts)

    if (!pixels)
    {
        SDL_Log("Pixels allocation failure : %s", SDL_GetError());
        return -1;
    }

    *static_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, image_size[0], image_size[1]);

    if (!*static_texture)
    {
        SDL_Log("Texture creation failure : %s", SDL_GetError());
        SDL_free(pixels);
        return -1;
    }

    for (Sint32 y=0; y<image_size[1]; y++)
    {
        SDL_memcpy(pixels+(image_size[1]-y-1)*row_size,
                   head+y*padded_row_size,
                   row_size);
    }
    
    SDL_UpdateTexture(*static_texture, NULL, pixels, row_size);
    SDL_free(pixels);
    return 0;
}

Sint8 *startPoint(Sint8 *content)
{
    Sint32 *offset = (Sint32*)(content+10);
    return content + *offset;
}

int openFile(const char* file_name, Sint8 **content)
{
    SDL_RWops *file = SDL_RWFromFile(file_name, "rb");
    if (!file)
    {
        SDL_Log("File open failure : %s", SDL_GetError());
        return -1;
    }

    Sint64 file_size = SDL_RWsize(file);
    *content = SDL_malloc(file_size);
    if (!*content)
    {
        SDL_Log("Allocation failure : %s", SDL_GetError());
        SDL_RWclose(file);
        return -1;
    }

    SDL_RWread(file, *content, file_size, 1);
    SDL_RWclose(file);
    return 0;
}