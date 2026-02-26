#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>

#include "titleScreen.hpp"
#include "Game.hpp"
#include "game_object.hpp"

// Want to share these.  Easiest (and quick) way
// is with a static data structure.
std::vector<SDL_Event> Engine::keyEvents;

Engine::Engine() { init(); }

SDL_Renderer* Engine::getRenderer() { return this->renderer; };


void Engine::run() {
	running = true;
    Uint64 frameStart = 0;
    Uint64 fpsLastTime = SDL_GetTicks();
    unsigned int frameCount = 0;
	while (running) {
        frameStart = SDL_GetTicks();
        frameCount++;

        // FPS counter (check every second)
        if(frameStart - fpsLastTime >= 1000){
            float fps = frameCount / ((frameStart - fpsLastTime) / 1000.0f);
            SDL_Log("FPS: %.2f", fps);
            frameCount = 0;
            fpsLastTime = frameStart;  // Only update here
        }
		// Clear the events from the last frame first.
		Engine::keyEvents.clear();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
            frameStart = SDL_GetTicks();
            frameCount++;
    
            // FPS counter (check every second)
            if(frameStart - fpsLastTime >= 1000){
                float fps = frameCount / ((frameStart - fpsLastTime) / 1000.0f);
                SDL_Log("FPS: %.2f", fps);
                frameCount = 0;
                fpsLastTime = frameStart;  // Only update here
            }
			if (event.type == SDL_EVENT_QUIT) {
				SDL_Log("Shutting down...");
				running = false;
			}
			if (event.type == SDL_EVENT_KEY_DOWN) {
				// Since we are storing copies of events, this
				// works.  Would not work if we were storing pointers
				// as event is a local variable to this function and
				// would always have the same address.
				Engine::keyEvents.push_back(event);
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		Engine::instance().update(targetFrameTime);
		SDL_RenderPresent(renderer);
		// Frame limiting
        Uint64 frameTime = SDL_GetTicks() - frameStart;
 
        if(frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    }
}

bool Engine::init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	// Gotta draw somewhere....
	window = SDL_CreateWindow("Breakout", 800, 600, SDL_WINDOW_FULLSCREEN);

	if (!window) {
		SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	// Who is in charge of drawing?
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	return true;
}

void Engine::shutdown() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
 
int main(int argc, char* argv[]) {
    // Create the objects that make up our game, and start the run.
    Engine& engine = Engine::instance();

    Scene* scene = new Scene();
	TitleScreen* title = new TitleScreen();

	scene->addObject(title);
	engine.setScene(scene);
    engine.run();
}
