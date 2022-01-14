//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int TILE_SIZE = 16;
const int SCREEN_BASE_OFFSET = 128;


// Number of level elements
const int LEVEL_WIDTH = 208;
const int LEVEL_HEIGHT = 15;
const int LEVEL_MAX_OFFSET = (LEVEL_WIDTH * TILE_SIZE) - SCREEN_WIDTH;

// Gameplay Const
const int CAT_MAX_JUMP = TILE_SIZE * 4;

// Character vars
int catX = 80;
int catY = 192;
int catMoveX = 0; // -1 gauche, 0 immobile, 1 droite
int catMoveY = 0; // 0 immobile, 1 saut en cours
int catJumpStock = CAT_MAX_JUMP;
int canJumpAgain = 1;
int catXOld = 80;
int catYOld = 192;

int levelOffset = 0;
int levelOffsetOld = 0;
int levelTileOffset = 0;


// FPS capping
int a, b, delta;

// Définition des ennemis
struct ennemy {
	int ennemyType = -1;
	int posX;
	int posY;
	int dir = -1;

	// Constructor
	ennemy(int x, int y) {
		posX = x;
		posY = y;
	}
};

// Définition du niveau
struct gameLevel {
	int levelTiles[LEVEL_HEIGHT][LEVEL_WIDTH] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 9,10,10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 0, 0, 9,10, 9,10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0,10, 0, 0,10, 0, 0,10, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0,10, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 9,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10, 0, 0,10,10, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10, 0, 0,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10, 0, 0,10,10,10, 0, 0, 0, 0, 0, 0,10,10,10,10, 0, 0,10,10,10, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0,10,10,10,10,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10, 0, 0,10,10,10,10, 0, 0, 0, 0,10,10,10,10,10, 0, 0,10,10,10,10, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7,10,10,10,10,10,10,10,10,10, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
		{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
	};

	ennemy levelEnnemy[16] = {
		ennemy(352, 192),
		ennemy(640, 192),
		ennemy(816, 192),
		ennemy(848, 192),
		ennemy(1296, 64),
		ennemy(1328, 64),
		ennemy(1568, 192),
		ennemy(1600, 192),
		ennemy(1840, 192),
		ennemy(1872, 192),
		ennemy(2000, 192),
		ennemy(2032, 192),
		ennemy(2064, 192),
		ennemy(2096, 192),
		ennemy(2720, 192),
		ennemy(2752, 192)
	};

	// Constructor
	gameLevel() {
	}

};

gameLevel* currentLevel;

// Remise à zéro des variables de jeu
void resetGame() {
	catX = 80;
	catY = 192;
	catMoveX = 0; // -1 gauche, 0 immobile, 1 droite
	catMoveY = 0; // 0 immobile, 1 saut en cours
	catJumpStock = CAT_MAX_JUMP;
	canJumpAgain = 1;
	catXOld = 80;
	catYOld = 192;
	levelOffset = 0;
	levelOffsetOld = 0;
	levelTileOffset = 0;

	currentLevel = new gameLevel();
}

// Méthode de gestion des collisions
bool levelCollision(int posx, int posy) {
	
	// Test et gestion des collisions avec le niveau -- TODO
						// Collision verticale -- TODO
	int currentTileXCheckMin = posx / TILE_SIZE;
	int hasCurrentTileCheckXMax = (posx % TILE_SIZE) > 0;

	if (currentTileXCheckMin > LEVEL_WIDTH) {
		currentTileXCheckMin = LEVEL_WIDTH;
	}

	int currentTileYCheckMin = posy / TILE_SIZE;
	int hasCurrentTileCheckYMax = (posy % TILE_SIZE) > 0;
	int collide = 0;

	for (int mx = 0; mx <= hasCurrentTileCheckXMax; mx++) {
		for (int my = 0; my <= hasCurrentTileCheckYMax; my++) {

			int currentFloorTile = currentLevel->levelTiles[currentTileYCheckMin + my][currentTileXCheckMin + mx];
			if (currentFloorTile > 6) {
				collide = 1;
			}
		}
	}

	return collide;

}

bool ennemyCollision(int p1x, int p1y, int p2x, int p2y) {
	int collide = 0;

	// Collision sur X
	if ((p2x >= p1x && p2x <= p1x + TILE_SIZE) || 
		(p2x + TILE_SIZE >= p1x && p2x + TILE_SIZE <= p1x + TILE_SIZE)) {
	
		// Collision sur Y
		if ((p2y >= p1y && p2y <= p1y + TILE_SIZE) ||
			(p2y + TILE_SIZE >= p1y && p2y + TILE_SIZE <= p1y + TILE_SIZE)) {

			collide = 1;
		}
	}

	return collide;

}


int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	// Event and Exit management
	int quit = 0;
	SDL_Event event;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	// Surfaces for tiles
	SDL_Surface* sLevel = SDL_LoadBMP("./resources/SMeowLevel.bmp");
	SDL_Surface* sChar = SDL_LoadBMP("./resources/SMeowChar.bmp");
	SDL_Surface* sFoe = SDL_LoadBMP("./resources/SMeowFoe.bmp");

	// Gestion de la transparence pour la surface
	Uint32 transparentColor = SDL_MapRGB(sChar->format, 255, 255, 255);
	int transCol = SDL_SetColorKey(sChar, SDL_TRUE, transparentColor);
	Uint32 transparentColor2 = SDL_MapRGB(sFoe->format, 255, 255, 255);
	int transCol2 = SDL_SetColorKey(sFoe, SDL_TRUE, transparentColor);

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Tile Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);


		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
		SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Textures loading
			SDL_Texture* tLevel = SDL_CreateTextureFromSurface(renderer, sLevel);
			SDL_Texture* tChar = SDL_CreateTextureFromSurface(renderer, sChar);
			SDL_Texture* tFoe = SDL_CreateTextureFromSurface(renderer, sFoe);
			SDL_SetTextureBlendMode(tChar, SDL_BLENDMODE_BLEND);
			SDL_SetTextureBlendMode(tFoe, SDL_BLENDMODE_BLEND);

			// Room loading
			currentLevel = new gameLevel();

			/* Loop until an SDL_QUIT event is found */
			while (!quit) {

				/* Poll for events */
				while (SDL_PollEvent(&event)) {

					switch (event.type) {
						/* Keyboard event */
						case SDL_KEYDOWN:
							/* Touche appuyée, changement de statut */
							switch (event.key.keysym.sym) {
							case SDLK_LEFT:
								catMoveX = -1;
								break;
							case SDLK_RIGHT:
								catMoveX = 1;
								break;
							case SDLK_UP:
								catMoveY = 1;
								canJumpAgain = 0;
								break;

							case SDLK_r:
								resetGame();
								break;
							case SDLK_ESCAPE:
								quit = 1;
								break;
							default:
								break;
							}


							break;
						/* Lorsque la touche est relachée, on annule le mouvement */
						case SDL_KEYUP:

							/* Touche appuyée, changement de statut */
							switch (event.key.keysym.sym) {
							case SDLK_LEFT:
								catMoveX = 0;
								break;
							case SDLK_RIGHT:
								catMoveX = 0;
								break;
							case SDLK_UP:
								catMoveY = 0;
								catJumpStock = 0;
								break;
							case SDLK_ESCAPE:
								quit = 1;
								break;
							default:
								break;
							}

							break;

						/* SDL_QUIT event (window close) */
						case SDL_QUIT:
							quit = 1;
							break;

						default:
							break;
					}

				}


				// Capping to 60 FPS
				a = SDL_GetTicks();
				delta = a - b;

				// Mesure si on peut passer à la frame suivante
				if (delta > 1000 / 120.0) {

					// FPS Management
					b = a;

					// Mise à jour de la position du chat (et animation)
					// Sauvegarde de la position actuelle
					catXOld = catX;
					levelOffsetOld = levelOffset;

					// Déplacement (horizontal)
					if (catMoveX == 1) {
						if (catX < SCREEN_BASE_OFFSET) {
							catX++;
						}
						else {
							if (levelOffset < LEVEL_MAX_OFFSET) {
								levelOffset++;
								levelTileOffset = levelOffset / TILE_SIZE;
							}
							else {
								if (catX < SCREEN_WIDTH - TILE_SIZE) {
									catX++;
								}
							}
						}
					}
					else {
						if (catMoveX == -1) {
							if (catX > 1) {
								catX--;
							}
						}
					}


					// Activation des ennemis
					// Parcours du tableau
					for (int eidx = 0; eidx < 16; eidx++) {

						// On prend en compte les ennemis actifs (ennemyType > 0)
						if (currentLevel->levelEnnemy[eidx].ennemyType < 0) {

							// Activation juste avant d'apparaître à l'écran
							if (currentLevel->levelEnnemy[eidx].posX < (levelOffset + SCREEN_WIDTH + TILE_SIZE)) {
								currentLevel->levelEnnemy[eidx].ennemyType = 1;
							}
						}

						// Actions sur les ennemis actifs
						if (currentLevel->levelEnnemy[eidx].ennemyType > 0) {

							// Desactivation des ennemis qui sont trop en arrière
							if (currentLevel->levelEnnemy[eidx].posX < (levelOffset - SCREEN_WIDTH)) {
								currentLevel->levelEnnemy[eidx].ennemyType = 0;
							}


							// Collision verticale
							if (!(levelCollision(currentLevel->levelEnnemy[eidx].posX + currentLevel->levelEnnemy[eidx].dir, currentLevel->levelEnnemy[eidx].posY + 1))) {
								currentLevel->levelEnnemy[eidx].posY++;
							}

							// Collision horisontale
							if (levelCollision(currentLevel->levelEnnemy[eidx].posX + currentLevel->levelEnnemy[eidx].dir, currentLevel->levelEnnemy[eidx].posY)) {
								currentLevel->levelEnnemy[eidx].dir = -currentLevel->levelEnnemy[eidx].dir;
							}


							// Déplacement des ennemis
							// On prend en compte les ennemis actifs (ennemyType > 0)
							if (currentLevel->levelEnnemy[eidx].ennemyType > 0) {

								// déplacement de l'ennemi
								currentLevel->levelEnnemy[eidx].posX += currentLevel->levelEnnemy[eidx].dir;
							}

							// Mort par chute
							if (currentLevel->levelEnnemy[eidx].posY >= TILE_SIZE * 14) {
								currentLevel->levelEnnemy[eidx].ennemyType = 0;
							}

							// Contrôle collision avec le chat
							if (ennemyCollision(catX + levelOffset,
												catY,
												currentLevel->levelEnnemy[eidx].posX,
												currentLevel->levelEnnemy[eidx].posY
							)) {

								if ((catY + (3 * TILE_SIZE / 4)) < currentLevel->levelEnnemy[eidx].posY) {
									// ennemi detruit
									currentLevel->levelEnnemy[eidx].ennemyType = 0;
								}
								else {
									// Reset du niveau
									resetGame();
								}
							}
						}
					}


					// Gestion de la gravité
					catYOld = catY;
					if (catMoveY && catJumpStock > 0) {
						catY--;
						catJumpStock--;
						if (catY < 0) { catY = 0; }
					}
					else {
						catY++;
					}

					// Mort par chute
					if (catY >= TILE_SIZE * 14) {
						resetGame();
					}

					// Contrôle collision Chat / Décors
					// Collision Verticale
					if (levelCollision(catXOld + levelOffsetOld, catY)) {
						// Si collision "saut" - arrêt du saut
						if (catYOld > catY && catMoveY == 1) {
							canJumpAgain = 1;
							if (catMoveY == 1) {
								catJumpStock = 0;
							}
						}

						// On touche le sol - reset du bouton de saut
						if (catYOld < catY && catMoveY == 0) {
							canJumpAgain = 1;
							catJumpStock = CAT_MAX_JUMP;
						}

						catY = catYOld;

					}

					// Collision Vertivale - catMoveX <> 0
					if (catMoveX) {

						if (levelCollision(catX + levelOffset, catY)) {
							catX = catXOld;
							levelOffset = levelOffsetOld;
						}
					}

					// Contrôle des collisions chat / ennemis -- TODO

					// Vider le cache pour les dessins
					SDL_RenderClear(renderer);

					// Dessiner le niveau - Zone courante
					int currentTileX = 0;
					int levelDrawOffset = levelOffset % TILE_SIZE;
					for (int xr = 0; xr < 17; xr++) {
						for (int yr = 0; yr < LEVEL_HEIGHT; yr++) {
							currentTileX = xr + levelTileOffset;
							if (currentTileX > LEVEL_WIDTH) {
								currentTileX = LEVEL_WIDTH;
							}

							SDL_Rect tilePosition = { (xr * TILE_SIZE) - levelDrawOffset, yr * TILE_SIZE, 16, 16 };
							int currentFloorTile = currentLevel->levelTiles[yr][currentTileX];

							SDL_Rect levelTile = { currentFloorTile * TILE_SIZE, 0, 16, 16 };
							SDL_RenderCopy(renderer, tLevel, &levelTile, &tilePosition);  // Dessin d'un sprite

						}
					}

					// Dessiner le Chat
					SDL_Rect catPosition = { catX, catY, 16, 16 };
					int currentCatTile = 0;

					SDL_Rect catTile = { currentCatTile * TILE_SIZE, 0, 16, 16 };
					SDL_RenderCopy(renderer, tChar, &catTile, &catPosition);  // Dessin d'un sprite

					// Dessiner les ennemis
					// Parcours du tableau
					for (int eidx = 0; eidx < 16; eidx++) {
						
						// On prend en compte les ennemis actifs (ennemyType > 0)
						if (currentLevel->levelEnnemy[eidx].ennemyType > 0) {

							// Dessin de l'ennemi
							SDL_Rect foePosition = { currentLevel->levelEnnemy[eidx].posX - levelOffset, currentLevel->levelEnnemy[eidx].posY, 16, 16 };
							int currentFoeTile = 0;

							SDL_Rect foeTile = { currentFoeTile * TILE_SIZE, 0, 16, 16 };
							SDL_RenderCopy(renderer, tFoe, &foeTile, &foePosition);  // Dessin d'un sprite
						}
					}

					SDL_RenderPresent(renderer); // Affichage


				}
			}

		}
		// Destroy renderer
		SDL_DestroyRenderer(renderer);

	}

;
	// Libération de la mémoire pour les Sprites
	SDL_FreeSurface(sLevel);
	SDL_FreeSurface(sChar);
	SDL_FreeSurface(sFoe);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}