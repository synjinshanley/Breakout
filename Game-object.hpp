#ifndef __HPP_GAME_OBJECTS__
#define __HPP_GAME_OBJECTS__

#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include "component.hpp"
#include <cstdlib>

#pragma once

// struct to hold the x and y values of a game object
struct Transform {
    float x = 0.5; // default value
    float y = 0.5; // default value
};


class GameObject {
    public:

        std::vector<std::unique_ptr<Component>> components;
        Transform transform;

        virtual void update(float delta) = 0;
};


class Pit: public GameObject {
    public:
        Pit() {
            transform.x = 0;
            transform.y = 1;

            components.push_back(std::make_unique<HitBox>(this, 1.0, 0.1));

            // this line depends on what the ma_engine object is called
            // it also depends on what the sound file is called
            components.push_back(std::make_unique<Audio>(this, MA_ENG*, "pit.mp4")); 
        }
}


class Brick: public GameObject {
    public:
        Brick(float h, float w, float x, float y, SDL_Color c) {
            transform.x = x;
            transform.y = y;
            components.push_back(std::make_unique<HitBox>(this, h, w));
            components.push_back(std::make_unique<Sprite>(this, c, h, w));

            // this line depends on what the ma_engine object is called
            // it also depends on what the sound file is called
            components.push_back(std::make_unique<Audio>(this, MA_ENG*, "brick.mp4")); 
        }
}

#endif
