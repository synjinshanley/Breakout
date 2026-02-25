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

Bar::Bar(float x, float y, float w, float h){
    transform.x = x;
    transform.y = y;
    auto* hitBoxComponent = addComponent<HitBox>();
    hitBoxComponent->setwidth(w);
    hitBoxComponent->setheight(h);
    auto spriteComponent = addComponent<SpriteComponent>();
    spriteComponent->createColorTexture(Engine::instance().getRenderer(), 0x00FFFFFF, x, y, w, h);
    rect = spriteComponent->getRect();
}

Bar::update(float deltaTime){
    void update(float delta) {
        for (auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it) {
		    if(it->key.key == SDL_MouseMotionEvent) {
                int width, height;
                SDL_GetWindowSize(engine->window, &width, &height);
                float = xrel_norm = it->key.key.xrel / width;
                if(transform.x + xrel_norm > 0.1 && transform.x + xrel_norm < 0.9) {
					transform.x += xrel_norm;
				}
	        }
        }
            
        // for (auto it = components.begin(); it != components.end(); ++it) {
        //     it.draw();
        // }
    }
}
