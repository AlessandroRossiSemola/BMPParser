#include <SDL.h>

static const Sint32 sdl_alignment = 4;
static const Sint32 sdl_channels = 3;

int bmpToTexture(const char *file_name, SDL_Renderer *renderer, SDL_Texture **static_texture);

int openFile(const char* file_name, Sint8 **content);

Sint32 calc_padded_row(const Sint32 row_size);

void bmp_dim(const Sint8 *content, Sint32 *w, Sint32 *h);

Sint8 *startPoint(Sint8 *content);