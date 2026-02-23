#include "Components.hpp"
#include "GameObject.hpp"

// Component
Component::Component(GameObject* o) : owner(o) {}
Component::~Component() = default;

void Component::draw(SDL_Renderer* renderer) {}
void Component::play_sound() {}


// HitBox
HitBox::HitBox(GameObject* owner, float w, float h)
    : Component(owner), height(h), width(w) {}

float HitBox::get_height() const { return height; }
float HitBox::get_width() const { return width; }

void HitBox::set_height(float h) { height = h; }
void HitBox::set_width(float w) { width = w; }


// Sprite
Sprite::Sprite(GameObject* owner, SDL_Color color, float height, float width)
    : Component(owner), c(color), h(height), w(width) {}

void Sprite::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); // choose color
    SDL_FRect rect{ owner->transform.x, owner->transform.y, w, h }; // create SDL_FRect
    SDL_RenderFillRectF(renderer, &rect); // draw the SDL_FRect
}


// Audio
Audio::Audio(GameObject* owner, ma_engine* eng, const char* filepath)
    : Component(owner), engine(eng) {

    if (ma_sound_init_from_file(engine, filepath, 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
        printf("Failed to load audio: %s\n", filepath);
    }
}

Audio::~Audio() {
    ma_sound_uninit(&sound);
}

void Audio::play_sound() {
    ma_sound_start(&sound);
}