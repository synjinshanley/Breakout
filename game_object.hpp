#ifndef			__HPP_GAME_OBJECT__
#define			__HPP_GAME_OBJECT__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "components.hpp"

enum class GameObjectType {
    Ball,
    Wall,
    Brick,
    Bar,
    Pit,
    GameData,
    TitleScreen
};

struct Transform {
    float x = 0.5; // default value
    float y = 0.5; // default value
};

// Everything is a game object.  Game objects hold components
// that encapsulate behaviors.  PLEASE NOTICE THAT THIS CLASS
// USES TEMPLATES FOR GENERIC METHODS.  You will need to have the
// code in the header file so it can compile.
class GameObject {
public:
  // Components to be added are of different types, but still
  // are components.  This generic function allows for that.
  template <typename T, typename... Args> T *addComponent(Args &&...args) {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must derive from Component");

    // Making the component a unique pointer makes sure that it is
    // only owned by one GameObject, and that we can't accidentally
    // mess that up.  It also makes sure the object is deleted if
    // it goes out of scope.
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->setOwner(this);

    T *ptr = component.get();
    components.push_back(std::move(component));
    return ptr;
  }

  // Since the getter returns a variety of types (all derived from Component),
  // we need another generic method.
  template <typename T> T *getComponent() {
    for (auto &c : components) {
      if (auto casted = dynamic_cast<T *>(c.get()))
        return casted;
    }
    return nullptr;
  }

  virtual void update(float deltaTime);
  virtual GameObjectType getType() const = 0;
  Transform transform;

private:
  std::vector<std::unique_ptr<Component>> components;
};

class Wall: public GameObject {
    public:
        Wall(float x, float y, float w, float h);
		    void update(float deltaTime) override;
		    GameObjectType getType() const override { return GameObjectType::Wall; }
	private:
		SDL_FRect* rect;
};

class Brick: public GameObject {
    public:
        Brick(float x, float y, float w, float h, uint32_t c);
        void update(float deltaTime) override;
        void destroy();
        GameObjectType getType() const override { return GameObjectType::Brick; }
    private:
        SDL_FRect* rect;
};

class Ball: public GameObject {
    private:
      float velocity[2];
      SDL_FRect* rect;
    public:
      Ball(float x, float y, float w, float h);
      void update(float deltaTime) override;
      void setVelocity(float x, float y);
      float* getVelocity();
      GameObjectType getType() const override { return GameObjectType::Ball; }
};

class Bar: public GameObject {
  private:
    SDL_FRect* rect;
  public:
    Bar(float x, float y, float w, float h);
    void update(float deltaTime);
    GameObjectType getType() const override { return GameObjectType::Bar; }
};

class Pit: public GameObject {
  public:
    Pit(float x, float y, float w, float h);
    void update(float deltaTime);
    GameObjectType getType() const override { return GameObjectType::Pit; }
};

// class GameData: public GameObject {
//   private:
//     SDL_FRect* rect;
//     //char* text;
//     int lives;
//     int score;
//   public:
//     GameData();
//     int height;
//     int width;
//     SpriteComponent* spriteComponent;
//     SDL_Renderer* engineRenderer;
//     void lose_life();
//     int get_score();
//     void set_score(int s);
//     TTF_Font* font;
//     SDL_Surface* surface;
//     std::string get_text();
//     void update(float deltaTime);
//     void update_score_text();
//     GameObjectType getType() const override { return GameObjectType::GameData; }
// };


#endif
