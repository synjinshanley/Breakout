#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#pragma once

#include <SDL3/SDL.h>
#include "miniaudio.h"


// Forward declaration
class GameObject;

class Component {
public:
    GameObject* owner = nullptr;

    Component(GameObject* o);
    virtual ~Component();

    virtual void draw(SDL_Renderer* renderer);
    virtual void play_sound();
};

class HitBox : public Component {
    private:
        float height;
        float width;

    public:
        HitBox(GameObject* owner, float w, float h);

        float get_height() const;
        float get_width() const;

        void set_height(float h);
        void set_width(float w);
};

class Sprite: public Component {
    private:
        SDL_Color c;
        float h;
        float w;

    public:
        Sprite(GameObject* owner, SDL_Color color, float height, float width);
        void draw(SDL_Renderer* renderer) override;
};


class Audio: public Component {
    private:
        ma_sound sound;
        ma_engine* engine; // engine should be made in the game class and should be global

    public:
        Audio(GameObject* owner, ma_engine* eng, const char* filepath);
        ~Audio();
        void play_sound() override;
};

#endif
