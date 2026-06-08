#include <SDL3/SDL.h>
#include "..\client\client_connection.h"


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Mini World", 800, 600, 0);
    ClientConnection clientConnection{ "127.0.0.1", 8080 };
    clientConnection.makeSocket();
    clientConnection.startConnection();
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_KEY_DOWN)
            {
                SDL_Log("%s key pressed!", SDL_GetKeyName(e.key.key));
                clientConnection.sendData(SDL_GetKeyName(e.key.key));
            }
            if (e.type == SDL_EVENT_QUIT) running = false;
        }
    }

    clientConnection.stopConnection();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}