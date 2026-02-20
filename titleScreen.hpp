#ifndef		__HPP_TITLESCREEN__
#define		__HPP_TITLESCREEN__

#include "game_object.hpp"
#include <SDL3/SDL.h>

class TitleScreen : public GameObject {
	public:
		TitleScreen(char* message, int x, int y);
		void start();
		void update(float deltaTime) override;
	private:
		SDL_FRect* rect;
		float pps = 10.0;
};


#endif
