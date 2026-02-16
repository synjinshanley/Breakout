#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "miniaudio.h"

#pragma once


// forward declarations
class GameObject;
struct Transform;


class Component {
    public:
        GameObject* owner = nullptr;
        
        virtual ~Component() = default;
        Component(GameObject* o) : owner(o) {}
};


class HitBox: public Component {
    private:
        float height;
        float width;
        
    public:
        HitBox(GameObject* owner, float w, float h) 
            : height(h), width(w) {}

        // getters
        float get_height() const { return height; }
        float get_width() const { return width; }
        // setters
        void set_height(float h) {height = h;}
        void set_width(float w) {width = w;}
};


class Sprite: public Component {
    private:
        SDL_Color c;
        float h;
        float w;

    public:
        Sprite(GameObject* owner, SDL_Color color, float height, float width)
            : c(color), h(height), w(width) {}

        void draw(SDL_Renderer* renderer) {
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a); // choose color
            SDL_FRect rect{ owner->transform.x, owner->transform.y, w, h }; // create SDL_FRect
            SDL_RenderFillRectF(renderer, &rect); // draw the SDL_FRect
        }
};


class Audio: public Component {
    private:
        ma_sound sound;
        ma_engine* engine; // engine should be made in the game class and should be global

    public:
        Audio(GameObject* owner, ma_engine* eng, const char* filepath)
           : engine(eng) {

            if (ma_sound_init_from_file(engine, filepath, 0, nullptr, nullptr, &sound) != MA_SUCCESS) {
                printf("Failed to load audio: %s\n", filepath);
            }
        }

        ~Audio() {
            ma_sound_uninit(&sound);
        }

        void play_sound() {
            ma_sound_start(&sound);
        }
};

#endif