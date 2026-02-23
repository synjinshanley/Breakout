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
            components.push_back(std::make_unique<HitBox>(this, w, h));
            components.push_back(std::make_unique<Sprite>(this, c, h, w));

            // this line depends on what the ma_engine object is called
            // it also depends on what the sound file is called
            components.push_back(std::make_unique<Audio>(this, MA_ENG*, "brick.mp4")); 
        }
}

class Wall: public GameObject {
    public:
        Wall(float h, float w, float x, float y) {
            transform.x = x;
            transform.y = y;
            components.push_back(std::make_unique<HitBox>(this, w, h));
            components.push_back(std::make_unique<Sprite>(this,{255,255,255,255},w,h));
        }
}


class Bar: public GameObject {
    private:


    public:
        Bar() {
            transform.x = 0.5;
            transform.y = 0.9;
            components.push_back(std::make_unique<HitBox>(this, 0.1, 0.05));
            components.push_back(std::make_unique<Sprite>(this,{255,255,0,0},0.1,0.05));
            components.push_back(std::make_unique<Audio>(this, MA_ENG*, "bar.mp4");
        }

        // still working on this
        void update() {
            for(auto it = Engine::keyEvents.begin(); it != Engine::keyEvents.end(); ++it){
		        if(it->key.key == SDL_MouseMotionEvent) {
                    it->key.key.xrel
	            }
            }


        }

}


class Ball: public GameObject {
    private:
        float velocity[2];
    public:
        Ball() {
            transform.x = 0.5;
            transform.y = 0.15;
            components.push_back(std::make_unique<HitBox>(this, 0.05, 0.05));
            components.push_back(std::make_unique<Sprite>(this,{255,255,0,0},0.05,0.05));
            void setVelocity(float vel[]);
            float* getVelocity();
        }
}


class GameData: public GameObject {
    private:
        int lives = 3;
        int score = 0;
        int jason_contributions = 1;
    
        public:
            void lose_life() {
                lives--;
                return;
            }

            void add_points(int q=1){
                score += q;
                return;
            }

            int get_score() {
                return score;
            }

            int get_lives() {
                return lives;
            }

    
}


#endif
