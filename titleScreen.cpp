#include "titleScreen.hpp"
#include "Game.hpp"
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
	Ball* ball = new Ball(windowWidth/2, windowHeight/2, windowWidth/80, windowHeight/60); // Ball in the center
	Bar* bar = new Bar(windowWidth/2, 9*windowHeight/10, windowWidth/8, windowHeight/60);
	Pit* pit = new Pit(0, 98*windowHeight/100, windowWidth, windowHeight/60);
	//GameData* gameData = new GameData();
	gameScene->addObject(ball);
	std::vector<uint32_t> colors = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF, 0xFF00FFFF}; // Red, Green, Blue, Yellow, Magenta
	for (int j = 0; j < 5; ++j) {
		for (int i = 0; i < 16; ++i) {
			Brick* brick = new Brick((windowWidth/10 + i * windowWidth/20) + 2, windowHeight/10 + (j+2) * windowHeight/30, windowWidth/21, windowHeight/31, colors[j]); // Red bricks
			gameScene->addObject(brick);
		}
	}
    gameScene->addObject(leftWall);
    gameScene->addObject(rightWall);
    gameScene->addObject(topWall);
	gameScene->addObject(bar);
	gameScene->addObject(pit);
	//gameScene->addObject(gameData);
	//SDL_Log("Scene created with %d objects", gameScene->getObjects().size());

    // Switch scenes
    engine.setScene(gameScene);
}
