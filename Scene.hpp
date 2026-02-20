#ifndef			__HPP_SCENE__
#define			__HPP_SCENE__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

#include "game_object.hpp"

class GameObject;

// A Scene is a simple collection for game objects. You may also
// want to keep other information in a scene, like background color, etc.
class Scene {
public:
  void addObject(GameObject *go) { game_objects.push_back(go); }
  void updateScene(float deltaTime) {
    for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
      (*it)->update(deltaTime);
    }
  }

private:
  std::vector<GameObject *> game_objects;
};

#endif