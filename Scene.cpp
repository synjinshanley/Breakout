#include "Scene.hpp"
#include "game_object.hpp"
#include "Game.hpp"
#include "components.hpp"
#include "titleScreen.hpp"

void Scene::detectCollisions(float deltaTime) {
    const std::vector<GameObject*>& game_objects = this->game_objects;
    if (game_objects[0]->getType() == GameObjectType::Ball) {
        for (size_t i = 1; i < game_objects.size(); ++i) {
            GameObject* obj = game_objects[i];
            if (obj->getType() == GameObjectType::Wall || obj->getType() == GameObjectType::Brick || obj->getType() == GameObjectType::Bar || obj->getType() == GameObjectType::Pit) {
                // Check for collision between the ball and the wall/brick
                if(obj->getType() == GameObjectType::Brick){
                    obj = static_cast<Brick*>(game_objects[i]);
                } else if(obj->getType() == GameObjectType::Wall){
                    obj = static_cast<Wall*>(game_objects[i]);
                } else if(obj->getType() == GameObjectType::Bar){
                    obj = static_cast<Bar*>(game_objects[i]);
                } else if(obj->getType() == GameObjectType::Pit){
                    obj = static_cast<Pit*>(game_objects[i]);
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
                        float x = ball->getVelocity()[0];
                        float y = ball->getVelocity()[1];
                        if (y < 0.0f) {
                            y *= (-1.0f);
                        }
                        if (y < 1.2f) { // Cap the speed increase to prevent it from getting too fast
                            //SDL_Log("Increasing ball speed, current velocity: (%f, %f)", x, y);
                            ball->setVelocity(ball->getVelocity()[0] * 1.05f, ball->getVelocity()[1] * 1.05f); // Increase speed by 10% after hitting a brick
                        }
                        for (size_t i = 1; i < game_objects.size(); ++i) {
                            GameObject* obj = game_objects[i];
                            if (obj->getType() == GameObjectType::GameData) {
                                GameData* gameData = static_cast<GameData*>(obj);
                                gameData->update_score();
                            }
                        }
                    }
                    if (obj->getType() == GameObjectType::Bar) {
                        Bar* bar = static_cast<Bar*>(obj);
                        float barCenterX = bar->transform.x + bar->getComponent<HitBox>()->get_width() / 2;
                        float ballCenterX = ball->transform.x + ballHitbox->get_width() / 2;
                        float offset = (ballCenterX - barCenterX) / (bar->getComponent<HitBox>()->get_width() / 2);
                        float newVelX = offset * 0.3f; // Adjust the horizontal velocity based on where the ball hits the bar
                        ball->setVelocity(newVelX, ball->getVelocity()[1]);
                    }

                    if (obj->getType() == GameObjectType::Pit) {
                        SDL_Delay(500); // Pause for a moment to show the ball falling into the pit
                        Engine& engine = Engine::instance();
                        int windowWidth = 0;
                        int windowHeight = 0;
                        SDL_GetWindowSize(engine.window, &windowWidth, &windowHeight);
                        ball->transform.x = windowWidth / 2;
                        ball->transform.y = windowHeight / 2;
                        ball->setVelocity(0.2f, 0.2f);
                        for (size_t i = 1; i < game_objects.size(); ++i) {
                            GameObject* obj = game_objects[i];
                            if (obj->getType() == GameObjectType::GameData) {
                                GameData* gameData = static_cast<GameData*>(obj);
                                gameData->lives -= 1;
                                if(gameData->lives <= 0){
                                    Scene* scene = new Scene();
	                                TitleScreen* title = new TitleScreen();

	                                scene->addObject(title);
	                                engine.setScene(scene);
                                }
                            }
                        }
                    }
                }
            }      
        }
    }
}
