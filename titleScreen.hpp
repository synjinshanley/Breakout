#ifndef		__HPP_TITLESCREEN__
#define		__HPP_TITLESCREEN__

#include "game_object.hpp"
#include <SDL3/SDL.h>

class TitleScreen : public GameObject {
	public:
		TitleScreen();
		void Message(char* message, int x, int y);
		void start();
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
};

class Wall: public GameObject {
    public:
        Wall(float x, float y, float w, float h);
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
};


#endif
