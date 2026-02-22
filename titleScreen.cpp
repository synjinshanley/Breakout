#include "titleScreen.hpp"
#include "game.hpp"
#include "game_object.hpp"
#include <SDL3/SDL.h>

// Constructor
TitleScreen::TitleScreen(){
	TitleScreen::Message("Welcome to Breakout!", 100, 100);
	TitleScreen::Message("This game is made by Synjin Shanley, Spencer Lincicum, and Jason Bos", 100, 200);
	
}

void TitleScreen::Message(char* message, int x, int y) {
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


void TitleScreen::start() {
    Engine& engine = Engine::instance();

    // Create a new scene for the game
    Scene* gameScene = new Scene();

    // Add your game objects
    //Game* game = new Game();
    //gameScene->addObject();

    // Switch scenes
    engine.setScene(gameScene);
}