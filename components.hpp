#ifndef __HPP_COMPONENTS__
#define __HPP_COMPONENTS__

#include <functional>
#include <SDL3/SDL.h>
#include <unordered_map>


class GameObject;

class Component {
	public:
		// We want these to be abstract (virtual in c++)
		virtual ~Component() = default;
		virtual void update(float deltaTime) {}

		GameObject* getOwner() const;

	private:
		void setOwner(GameObject* go);

		// Make it easier to share information with GameObjects
		// by letting them see our private data.
		friend class GameObject;

		// To which game object do we belong?
		GameObject* owner = nullptr;
};

class SpriteComponent : public Component {
	public:
		void setX(int x);
		void setY(int y);
		// Load an image from a file.  Normally we would
		// probably have multiple images per sprite for
		// animations.
		void createColorTexture(SDL_Renderer* renderer, uint32_t color, float x, float y, float w, float h);
        bool loadText(SDL_Renderer* renderer, char* message, int x, int y);
		SDL_Texture* getSprite();
		void update(float deltaTime) override;
		SDL_FRect* getRect();

	private:
		// For convenience we can keep track of the renderer
		// from the engine.
		SDL_Renderer* renderer = nullptr;
		SDL_FRect destRect{};
		SDL_Texture* sprite = nullptr;
};

class HitBox: public Component {
    private:
        float height;
        float width;
        
    public:
        // getters
        float get_height() const { return height; }
        float get_width() const { return width; }
        // setters
        void set_height(float h) {height = h;}
        void set_width(float w) {width = w;}
};


#endif

