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

	int windowWidth = 0;
	int windowHeight = 0;
	SDL_GetWindowSize(engine.window, &windowWidth, &windowHeight);

	// Add game objects
	Wall* leftWall = new Wall(0, 0, windowWidth/10, windowHeight); // Left wall
	Wall* rightWall = new Wall(windowWidth - windowWidth/10, 0, windowWidth/10, windowHeight); // Right wall
	Wall* topWall = new Wall(0, 0, windowWidth, windowHeight/10); // Top wall
    gameScene->addObject(leftWall);
    gameScene->addObject(rightWall);
    gameScene->addObject(topWall);

    // Switch scenes
    engine.setScene(gameScene);
}