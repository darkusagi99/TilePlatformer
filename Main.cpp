//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	// Event and Exit management
	int quit = 0;
	SDL_Event event;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Tile Platformer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

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
								//alien_xvel = -1;
								break;
							case SDLK_RIGHT:
								//alien_xvel = 1;
								break;
							case SDLK_UP:
								//alien_yvel = -1;
								break;
							case SDLK_DOWN:
								//alien_yvel = 1;
								break;
							case SDLK_x:
								//alien_yvel = 1;
								break;
							case SDLK_c:
								//alien_yvel = 1;
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
								//alien_xvel = -1;
								break;
							case SDLK_RIGHT:
								//alien_xvel = 1;
								break;
							case SDLK_UP:
								//alien_yvel = -1;
								break;
							case SDLK_DOWN:
								//alien_yvel = 1;
								break;
							case SDLK_x:
								//alien_yvel = 1;
								break;
							case SDLK_c:
								//alien_yvel = 1;
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

				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x11, 0x11, 0xDD));

				//Update the surface
				SDL_UpdateWindowSurface(window);

			}

		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}