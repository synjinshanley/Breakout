#include "components.hpp"
#include "game_object.hpp"

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

GameObject* Component::getOwner() const {
    return owner;
}

void Component::setOwner(GameObject* go) {
    owner = go;
}


void SpriteComponent::setX(int x) {
    destRect.x = x;
}

void SpriteComponent::setY(int y) {
    destRect.y = y;
}

void SpriteComponent::createColorTexture(SDL_Renderer* renderer, uint32_t color, float x, float y, float w, float h) {
    this->renderer = renderer;
    // Create an SDL_Surface first
    SDL_Surface* surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA8888);
    if (!surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        return;
    }

    // Fill the surface with the color
    SDL_FillSurfaceRect(surface, nullptr, color);

    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;

    // Create a texture from the surface
    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    if (!sprite) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
    }

    // Free the surface since we no longer need it
    SDL_DestroySurface(surface);
}

bool SpriteComponent::loadText(SDL_Renderer* renderer, char* message, int x, int y) {
    this->renderer = renderer;
    if (TTF_Init() < 0) {
        SDL_Log("TTF init error: %s", SDL_GetError());
        return 1;
    }
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        SDL_Log("Font load error: %s", SDL_GetError());
        return 1;
    }

    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface* surface = TTF_RenderText_Blended(font, message, 0, white);
    if (!surface) {
        SDL_Log("TTF_RenderText_Blended Error: %s", SDL_GetError());
        return false;
    };

    destRect.x = x;
    destRect.y = y;
    destRect.w = surface->w;
    destRect.h = surface->h;

    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    if (!sprite) {
    SDL_Log("Texture creation failed: %s", SDL_GetError());
}
    SDL_DestroySurface(surface);

    return sprite != nullptr;

}

// Sometimes we might need to get the image.
SDL_Texture* SpriteComponent::getSprite() {
    return sprite;
}

void SpriteComponent::update(float) {
    if (!SDL_RenderTexture(renderer, sprite, nullptr, &destRect)){
        SDL_Log("RenderTexture failed: %s", SDL_GetError());
    };
}

// The destRect is where and how much of the image will be drawn.
SDL_FRect* SpriteComponent::getRect(){
    return &destRect;
}

