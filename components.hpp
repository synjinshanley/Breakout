#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "miniaudio.h"


class GameObject;

class HitBox {
    private:
        float height;
        float width;

    public:
        HitBox(float w, float h) 
            : height(h), width(w) {}

        // getters
        void get_width() const { return width; }
        float get_height() const { return height; }
};


class Sprite {
    private:
        SDL_Color c;
        float h;
        float w;
    public:
        Sprite(SDL_Color color, float height, float width) 
            : c(color), h(height), w(width) {}

        void draw(SDL_Renderer* renderer, Transform* t) {
            SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
            SDL_FRect rect{ t->x, t->y, w, h };
            SDL_RenderFillRectF(renderer, &rect);
        }
};


class Audio {
    private:
        ma_sound sound;
        ma_engine* engine; // engine should be made in the game class and should be global

    public:
        Audio(ma_engine* eng, const char* filepath)
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
