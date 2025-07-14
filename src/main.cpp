#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Entities.hpp"

int main(){
    InitWindow(screenWidth, screenHeight, "2D RPG");
    SetTargetFPS(60);

    GameStartup(); 
    
    while(!WindowShouldClose())
    {

            GameUpdate();     
            BeginDrawing();  
            
            if(inMenu)
            {
                GameMenu();
            }
            else if(inTutorial)
            {
                Tutorial();
            }
            else if (inCharacterSelect)
            {
                CharacterSelect();
            }
            else if(inOptions)
            {
                OptionsMenu();
            }
            else if(isDead)
            {
                DeathMenu();
            }
            else{
            
                ClearBackground({34,35,35,255});
                GameRender();
                EndDrawing();
            }
    }
    GameShutdown();
    return 0;
}

