#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sdl_circle.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GROUND_Y SCREEN_HEIGHT * 0.75

typedef struct Table Table;
struct Table {
    int originX;
    int originY;
    int size;
};

void play(SDL_Renderer *renderer, Table* table, int* state_of_game);
void drawBoard(SDL_Renderer *renderer, Table *table);
void drawPieceOnBoard(SDL_Renderer *renderer, Table *table, int position, char shape);
void drawCross(SDL_Renderer *renderer, int crossSize, int x, int y);
int modifyStateOfGame(int* state_of_game, int position, int turn);
void resetStateOfGame(int* state_of_game, int* turn);
int positionOfClickOnBoard(Table* table, int mousePositionX, int mousePositionY);
int winnerOfRound(int* state_of_game);
void clearScreen(SDL_Renderer* renderer);
void drawMenu(SDL_Renderer *renderer, bool ai_mode);
void ai_play(int* state_of_game, char ia_piece);