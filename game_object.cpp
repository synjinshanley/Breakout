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
  hitbox->set_height(h);
  hitbox->set_width(w);
	rect = spriteComponent->getRect();
}

void Wall::update(float deltaTime) {
	GameObject::update(deltaTime);
}
