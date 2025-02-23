#include "GameFunctions.hpp"
#include "GameMenu.hpp"


int main(){
    InitWindow(screenWidth, screenHeight, "2D RPG");
    SetTargetFPS(60);

    GameStartup();

    while(!WindowShouldClose()){

            GameUpdate();


            BeginDrawing();

            if(inMenu)
            {
                GameMenu();
            }

            else{
            
                ClearBackground(BLACK);

                GameRender();

                EndDrawing();
            }
        
    }

    GameShutdown();
    return 0;
}

