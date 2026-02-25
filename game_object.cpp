#include "game_object.hpp"
#include "components.hpp"
#include "game.hpp"

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