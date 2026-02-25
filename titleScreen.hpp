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
		GameObjectType getType() const override { return GameObjectType::TitleScreen; }
	private:
		SDL_FRect* rect;
};


#endif
