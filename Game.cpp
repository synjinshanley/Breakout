#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <random>
#define FPS 60
 
int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
 
    SDL_Window* window = SDL_CreateWindow(
            "RGB Color Cycle",
            800, 600,
            SDL_WINDOW_FULLSCREEN
            );
 
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
 
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
 
    SDL_SetRenderVSync(renderer, 0);
    Uint64 targetFrameTime = 1000 / FPS;
 
    SDL_Surface* surface = IMG_Load("PixelCar5.png");
    if (!surface) {
        printf("IMG_Load Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
 
    SDL_Texture* sprite = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
 
    if (!sprite) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
 
    SDL_FRect destRect = { 100, 100, 64, 64 };
 
    bool running = true;
    SDL_Event event;
    Uint8 r = 0, g = 0, b = 0;
 
    Uint64 frameStart = 0;
    Uint64 fpsLastTime = SDL_GetTicks();
    unsigned int frameCount = 0;
 
    while (running) {
        frameStart = SDL_GetTicks();
        frameCount++;
 
        // FPS counter (check every second)
        if(frameStart - fpsLastTime >= 1000){
            float fps = frameCount / ((frameStart - fpsLastTime) / 1000.0f);
            SDL_Log("FPS: %.2f", fps);
            frameCount = 0;
            fpsLastTime = frameStart;  // Only update here
        }
 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_W){
                    destRect.y--;
                }
                if(event.key.key == SDLK_S){
                    destRect.y++;
                }
                if(event.key.key == SDLK_A){
                    destRect.x--;
                }
                if(event.key.key == SDLK_D){
                    destRect.x++;
                }
            }
        }
 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        SDL_RenderTexture(renderer, sprite, NULL, &destRect);
 
        SDL_RenderPresent(renderer);
 
        // Frame limiting
        Uint64 frameTime = SDL_GetTicks() - frameStart;
 
        if(frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    }
 
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}