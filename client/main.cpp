#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "..\client\client_connection.h"


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Mini World", 800, 600, 0); //create window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr); //create renderer

    //create socket and connect to server
    ClientConnection clientConnection{ "127.0.0.1", 8080 };
    clientConnection.makeSocket();
    clientConnection.startConnection();
    
    //create SDL event
    bool running = true;
    SDL_Event e;

    //player data
    float posX = 400;
    float posY = 300;
    float speed = 5.0f;

    while (running) {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_EVENT_QUIT) running = false;
            if (e.type == SDL_EVENT_KEY_DOWN)
            {
                //SDL_Log("%s key pressed!", SDL_GetKeyName(e.key.key));
                clientConnection.sendData(SDL_GetKeyName(e.key.key));
            }
            
        }
        //movement
        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_W]) posY -= speed;
        if (keys[SDL_SCANCODE_S]) posY += speed;
        if (keys[SDL_SCANCODE_A]) posX -= speed;
        if (keys[SDL_SCANCODE_D]) posX += speed;

        //render
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); //background
        SDL_RenderClear(renderer);//clear renderer per iteration

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //make player red
        SDL_FRect playerRect{ posX, posY, 50, 50 }; //create rectangle
        SDL_RenderFillRect(renderer, &playerRect); //fill rectangle
        SDL_RenderPresent(renderer); //present to screen
    }

    clientConnection.stopConnection();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}