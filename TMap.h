#pragma once
#include <SDL.h>

typedef unsigned char tileindex;

// Propri�t� pour chaque Tile
typedef struct
{
	SDL_Rect R;
	int collide;
} TileProp;

typedef struct
{
	int tilesNbX, tilesNbY;	// Nombre de tiles dans la d�finition
	SDL_Surface* tileset;
	TileProp* props;
	tileindex** schema;
	int worldTilesX, worldTilesY;
} Map;

Map* loadMap(const char* fic);
int showMap(Map* m, SDL_Surface* screen);
int freeMap(Map* m);