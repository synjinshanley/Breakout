#include "titleScreen.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include <SDL3/SDL.h>

// Constructor
TitleScreen::TitleScreen(char* message, int x, int y){
	auto* spriteComponent = addComponent<SpriteComponent>();
	spriteComponent->loadText(Engine::instance().getRenderer(), message, x ,y);
	rect = spriteComponent->getRect();

}

// Called once per frame
void TitleScreen::update(float deltaTime) {
	// Call the parent class to notify components
	GameObject::update(deltaTime);
	for(auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it){
		if(it->key.key == SDLK_RETURN){
			start();
	    }
    }
}


void TitleScreen::start(){
	return;
}