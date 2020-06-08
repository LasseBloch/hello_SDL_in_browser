#include <iostream>
#include <SDL.h>

static constexpr int screenHeight{600};
static constexpr  int screenWidth{800};
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool initSDL()
{
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL could not be initialized! SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	} else
	{
		// Create window
		window = SDL_CreateWindow("SDL local test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window) {
			// Create renderer for window_
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (!renderer) {
				SDL_Log("Could not create renderer! SDL_ERROR: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			}
		} else
		{
			SDL_Log("Could not create window! SDL_ERROR: ‰s \n", SDL_GetError());
			success = false;
		}
	}
	return success;
}


int main()
{
	if (!initSDL()) {
		return -1;
	}

	SDL_Surface * image = SDL_LoadBMP("../assets/trump_run.bmp");
	if (!image) {
		SDL_Log("Could not load image! SDL_ERROR: %s\n", SDL_GetError());
	}
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	auto spriteIndex = 0;

	auto frameTimeMs = 100;
	auto startTime = 0;
	auto endTime = 0;
	auto deltaTime = 0;

	bool quit = false;
	SDL_Event evt;
	while(!quit) {

		if (!startTime) {
			// ms since start
			startTime = SDL_GetTicks();
		}
		else {
			deltaTime = endTime - startTime; // how many ms for a frame
		}

		// Handle events
		while(SDL_PollEvent(&evt)) {
			switch (evt.type) {
			case SDL_QUIT:
				SDL_Log("Quit event\n");
				quit = true;
				break;
			default:
				break;
			}
		}

		// if less than 16ms, delay
		if (deltaTime < frameTimeMs) {
			SDL_Delay(frameTimeMs - deltaTime);
		}

		// We have 6 sprites
		spriteIndex++;
		if (spriteIndex == 6) {
			spriteIndex = 0;
		}


		SDL_Rect srcrect = { 100 * spriteIndex, 0, 100, 100 };


		SDL_Rect dstrect = {screenWidth / 2 - 50, screenHeight / 2 - 50, 100, 100 };
		SDL_SetRenderDrawColor(renderer, 168, 230, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
		SDL_RenderPresent(renderer);

		startTime = endTime;
		endTime = SDL_GetTicks();
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
