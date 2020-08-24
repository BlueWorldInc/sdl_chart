#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>

void SDL_Ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY);
void SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
void SDL_RenderFillHalfCircle(SDL_Renderer * renderer, int x, int y, int radius);