#include "scene.hpp"
#include "game_object.hpp"

void Scene::detectCollisions(float deltaTime) {
    const std::vector<GameObject*>& game_objects = this->game_objects;
    if (game_objects[0]->getType() == GameObjectType::Ball) {
        for (size_t i = 1; i < game_objects.size(); ++i) {
            GameObject* obj = game_objects[i];
            if (obj->getType() == GameObjectType::Wall || obj->getType() == GameObjectType::Brick) {
                // Check for collision between the ball and the wall/brick
                if(obj->getType() == GameObjectType::Brick){
                    obj = static_cast<Brick*>(game_objects[i]);
                } else {
                    obj = static_cast<Wall*>(game_objects[i]);
                }
                Ball* ball = static_cast<Ball*>(game_objects[0]);
                HitBox* ballHitbox = ball->getComponent<HitBox>();
                HitBox* objHitbox = obj->getComponent<HitBox>();

                float ballLeft = ball->transform.x;
                float ballRight = ball->transform.x + ballHitbox->get_width();
                float ballTop = ball->transform.y;
                float ballBottom = ball->transform.y + ballHitbox->get_height();

                float objLeft = obj->transform.x;
                float objRight = obj->transform.x + objHitbox->get_width();
                float objTop = obj->transform.y;
                float objBottom = obj->transform.y + objHitbox->get_height();

                float* velocity = ball->getVelocity();

                if (ballRight > objLeft && ballLeft < objRight &&
                    ballBottom > objTop && ballTop < objBottom) {

                    //SDL_Log("Collision detected");

                    float overlapX = std::min(ballRight, objRight) - std::max(ballLeft, objLeft);
                    float overlapY = std::min(ballBottom, objBottom) - std::max(ballTop, objTop);

                    float newVel[2] = { velocity[0], velocity[1] };

                    if (overlapX < overlapY)
                        newVel[0] *= -1;
                    else
                        newVel[1] *= -1;

                    ball->setVelocity(newVel[0], newVel[1]);

                    // If it's a brick, remove it from the scene
                    if (obj->getType() == GameObjectType::Brick) {
                        Brick* brick = static_cast<Brick*>(obj);
                        brick->destroy();
                    }
                }
            }      
        }
    }
}