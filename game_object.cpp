#include "game_object.hpp"
#include "components.hpp"
#include "Game.hpp"
#include <iostream>

// Our component-based system needs to ensure
// all components update each frame.
void GameObject::update(float deltaTime) {
  for (auto &c : components){
    c->update(deltaTime);
  }
}

Wall::Wall(float x, float y, float w, float h) {
	auto* spriteComponent = addComponent<SpriteComponent>();
  auto* hitbox = addComponent<HitBox>();
	spriteComponent->createColorTexture(Engine::instance().getRenderer(), 0x808080FF, x, y, w, h);
  transform.x = x;
  transform.y = y;
  hitbox->set_height(h);
  hitbox->set_width(w);
	rect = spriteComponent->getRect();
}

void Wall::update(float deltaTime) {
	GameObject::update(deltaTime);
}

Brick::Brick(float x, float y, float w, float h, uint32_t c) {
	auto* spriteComponent = addComponent<SpriteComponent>();
  auto* hitbox = addComponent<HitBox>();
	spriteComponent->createColorTexture(Engine::instance().getRenderer(), c, x, y, w, h);
  transform.x = x;
  transform.y = y;
  hitbox->set_height(h);
  hitbox->set_width(w);
	rect = spriteComponent->getRect();
}

void Brick::update(float deltaTime) {
	GameObject::update(deltaTime);
}

void Brick::destroy() {
    // Mark the brick as destroyed by setting its type to a special value
    // or by removing it from the scene's game object list.
    // For simplicity, we can just set its type to a special value here.
    // In a more complex implementation, you might want to handle this differently.
    rect->w = 0; // Make it invisible
    rect->h = 0; // Make it invisible
    transform.x = 0.0; // Moves the hitbox out of the way
    transform.y = 0.0; // Moves the hitbox out of the way
}

Ball::Ball(float x, float y, float w, float h) {
  velocity[0] = 0.2f; // default x velocity
  velocity[1] = -0.2f; // default y velocity
	auto* spriteComponent = addComponent<SpriteComponent>();
  auto* hitbox = addComponent<HitBox>();
	spriteComponent->createColorTexture(Engine::instance().getRenderer(), 0xFFFFFFFF, x, y, w, h);
  transform.x = x;
  transform.y = y;
  hitbox->set_height(h);
  hitbox->set_width(w);
	rect = spriteComponent->getRect();
}

void Ball::update(float deltaTime) {
	GameObject::update(deltaTime);
	transform.x += velocity[0] * deltaTime;
	transform.y += velocity[1] * deltaTime;
  rect->x = transform.x;
  rect->y = transform.y;
}

void Ball::setVelocity(float x, float y) {
  velocity[0] = x;
  velocity[1] = y;
}

float* Ball::getVelocity() {
  return velocity;
}

Bar::Bar(float x, float y, float w, float h){
    transform.x = x;
    transform.y = y;
    auto* hitBoxComponent = addComponent<HitBox>();
    hitBoxComponent->set_width(w);
    hitBoxComponent->set_height(h);
    auto spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->createColorTexture(Engine::instance().getRenderer(), 0x00FFFFFF, x, y, w, h);
    rect = spriteComponent->getRect();
}

void Bar::update(float deltaTime) {
  GameObject::update(deltaTime);
  Engine& engine = Engine::instance();
  float mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  transform.x = static_cast<float>(mouseX);
  //std::cout << transform.x;
  int width, height;
  SDL_GetWindowSize(engine.window, &width, &height);
  if(transform.x < width/10){transform.x = width/10;}
  if(transform.x > 9*width/10 - width/8){transform.x = 9*width/10 - width/8;}
  rect->x = transform.x;
  rect->y = transform.y;
  
  
}

// GameData::GameData(){
//   //std::string text = "Score: 0"; // \nLives: 3
//   int lives = 3;
//   int score = 0;
//   int width, height;
//   TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
//   Engine& engine = Engine::instance();
//   engineRenderer = engine.getRenderer();
//   SDL_GetWindowSize(engine.window, &width, &height);
//   spriteComponent = addComponent<SpriteComponent>();
//   std::cout << typeid(spriteComponent).name();
// 	spriteComponent->loadText(engineRenderer, "Score: 0", width/8, height/20);
//   rect = spriteComponent->getRect();

// }

// void GameData::lose_life(){
//   lives -= 1;
// }

// int GameData::get_score(){
//   return score;
// }

// void GameData::set_score(int s){
//   score = s;
//   SDL_Log("Worked up to here2");
//   update_score_text();
// }

// void GameData::update_score_text(){
//   std::string t = "Score: " + std::to_string(score);
//   SDL_Log("Worked up to here3");
//   const char* t2 = t.c_str();
//   char* text = const_cast<char*>(t2);
//   SDL_Log("Worked up to here4");
//   rect = spriteComponent->getRect();
//   spriteComponent->loadText(engineRenderer, text, width/8, height/20);
// }

// void GameData::update(float deltaTime){
//   GameObject::update(deltaTime);
//   // std::string t = "Score: " + std::to_string(score) + "\nLives: " + std::to_string(lives);
//   // const char* t2 = t.c_str();
//   // text = const_cast<char*>(t2);
//   // auto* spriteComponent = addComponent<SpriteComponent>();
// 	// spriteComponent->loadText(Engine::instance().getRenderer(), text, 100, 200);
//   // rect = spriteComponent->getRect();
// }
