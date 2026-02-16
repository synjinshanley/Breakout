#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>
#include "component.hpp"

#pragma once


// struct to hold the x and y values of a game object
struct Transform {
    float x = 0.5; // default value
    float y = 0.5; // default value
};


class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;

    public:
        Transform transform;

        virtual void update(float delta) = 0;
};
