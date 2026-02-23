#include "game_object.hpp"
#include "components.hpp"

// Our component-based system needs to ensure
// all components update each frame.
void GameObject::update(float deltaTime) {
  for (auto &c : components){
    c->update(deltaTime);
  }
}

Pit::Pit(float x, float y, float w, float h){
    transform.x = x;
    transform.y = y;
    auto* hitBoxComponent = addComponent<HitBox>();
    hitBoxComponent->set_width(w);
    hitBoxComponent->set_height(h);
    //components.push_back(std::make_unique<Audio>(this, MA_ENG*, "pit.mp4"));
}

void Pit::update(float deltatime){
    GameObject::update(deltatime);
}
