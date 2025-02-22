#include "GameFunctions.hpp"


int main(){
    InitWindow(screenWidth, screenHeight, "2D RPG");
    SetTargetFPS(60);

    GameStartup();

    while(!WindowShouldClose()){

        GameUpdate();

        BeginDrawing();
        ClearBackground(BLACK);

        GameRender();

        EndDrawing();
    }

    GameShutdown();
    return 0;
}

