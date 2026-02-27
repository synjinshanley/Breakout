#include "game_object.hpp"
#include "components.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>

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
	transform.x += velocity[0] * deltaTime * 2;
	transform.y += velocity[1] * deltaTime * 2;
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

GameData::GameData() {
   Engine& engine = Engine::instance();
   SDL_Renderer* engineRenderer = engine.getRenderer();
   SDL_GetWindowSize(engine.window, &width, &height);
   std::string text = "Score: " + std::to_string(score);

    auto* spriteComponent = addComponent<SpriteComponent>();

    spriteComponent->loadText(engineRenderer,
                              const_cast<char*>(text.c_str()),
                              width / 8,
                              height / 20);

    rect = spriteComponent->getRect();
 }

 void GameData::update_score(){
   this->Add_Score(10);
 }

 void GameData::update_text(float height, float width) {
    removeComponent<SpriteComponent>(); // Remove the old score text
    Engine& engine = Engine::instance();
    SDL_Renderer* engineRenderer = engine.getRenderer();

    std::string text = "Score: " + std::to_string(score);

    auto* spriteComponent = addComponent<SpriteComponent>();

    spriteComponent->loadText(engineRenderer,
                              const_cast<char*>(text.c_str()),
                              width / 8,
                              height / 20);

    rect = spriteComponent->getRect();
}

 void GameData::update(float deltaTime){
   update_score();
   update_text(height, width);
   GameObject::update(deltaTime);
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

Pit::Pit(float x, float y, float w, float h){
    transform.x = x;
    transform.y = y;
    auto* hitBoxComponent = addComponent<HitBox>();
    hitBoxComponent->set_width(w);
    hitBoxComponent->set_height(h);
    //components.push_back(std::make_unique<Audio>(this, MA_ENG*, "pit.mp4"));
}

void Pit::update(float deltaTime){
  GameObject::update(deltaTime);
}
