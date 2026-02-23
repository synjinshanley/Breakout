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