#ifndef			__HPP_GAME__
#define			__HPP_GAME__

#include <SDL3/SDL.h>
#include "Scene.hpp"

#define FPS 60
#define MAX_EVENTS 128
#define targetFrameTime 1000.0 / FPS

class Scene;

// Singleton pattern to ensure we only have one
// instance of Engine at a time.
class Engine {
	public:
		// Returns the instance.
		static Engine& instance(){
			static Engine instance;
			return instance;
		}

		// Delete copy operators.  No copies!
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

		SDL_Renderer* getRenderer();
		void run();

		Engine();
		~Engine() = default;

		bool init();

		void shutdown();

		void setScene(Scene* scene) {
        	nextScene = scene;  // don't switch immediately
    	}

		void update(float deltaTime) {
			if (currentScene)
				currentScene->updateScene(deltaTime);

			// AFTER update loop finishes
			if (nextScene != nullptr) {
				delete currentScene;
				currentScene = nextScene;
				nextScene = nullptr;
			}
		}

		SDL_Window* window;
		SDL_Renderer* renderer;
		bool running = false;
		// Notice that we are storing copies of the
		// events, not pointers or references.
		static std::vector<SDL_Event> keyEvents;
		Scene* currentScene = nullptr;
    	Scene* nextScene = nullptr;

};

#endif
