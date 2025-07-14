#include "StoryLine.hpp"
#include "GameFunctions.hpp"
#include "Items.hpp"
#include <iostream>

bool inDialogue = false;
bool inDialogueWithOptions = false;
std::vector<std::string> dialogueLines;
size_t currentDialogueLine = 0;
size_t dialogueCharIndex = 0;
float dialogueTimer = 0.0f;
bool dialogueSkipped = false;

bool YesorNo; 

bool Act1_HermitInteracted = false, Act1_WoundedKnightInteracted = false;
bool Act1_Introduced = false;
bool Act1_firstTimeInDungeon;

bool dungeonKey = false, plainsKey = false;

//rects
Rectangle boxOutline = {32, 312, 736, 240};
Rectangle dialogueBox = {48, 328, 704, 208};
Rectangle yesBox = {dialogueBox.x + 5, dialogueBox.y +150, 70, 40};
Rectangle noBox = {dialogueBox.x + 100, dialogueBox.y +150, 70, 40};

Color boxColor = {99, 75, 32, 255};

//Dialogue Settings
void StartDialogue(const std::vector<std::string>& lines) 
{
    if (lines.empty()) return;

    dialogueLines = lines;
    currentDialogueLine = 0;
    dialogueCharIndex = 0;
    dialogueTimer = 0.0f;
    dialogueSkipped = false;
    inDialogue = true;
}

void StartDialogueWithOptions(const std::vector<std::string> &lines)
{  
    if (lines.empty()) return;

    dialogueLines = lines;
    currentDialogueLine = 0;
    dialogueCharIndex = 0;
    dialogueTimer = 0.0f;
    dialogueSkipped = false;
    inDialogueWithOptions = true;
}

void UpdateDialogue()
{
    if(!inDialogue) return;


    if(dialogueCharIndex < dialogueLines[currentDialogueLine].length())
    {
        dialogueTimer += GetFrameTime();
        if(dialogueTimer >= 0.04f)
        {
            dialogueTimer = 0;
            dialogueCharIndex++;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();
        if(CheckCollisionPointRec(mousePos, dialogueBox))
        {
            if(dialogueCharIndex < dialogueLines[currentDialogueLine].length())
            {
                dialogueCharIndex = dialogueLines[currentDialogueLine].length();
            }
            else
            {
                currentDialogueLine++;
                if(currentDialogueLine >= dialogueLines.size())
                {
                    inDialogue = false;
                }
                else
                {
                    dialogueCharIndex = 0;
                }
            }

        }
    }
}

void UpdateDialogueWithOptions()
{
    if(!inDialogueWithOptions) return;

    if(dialogueCharIndex < dialogueLines[currentDialogueLine].length())
    {
        dialogueTimer += GetFrameTime();
        if(dialogueTimer >= 0.03f)
        {
            dialogueTimer = 0;
            dialogueCharIndex++;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePos = GetMousePosition();

        if(CheckCollisionPointRec(mousePos, yesBox))
        {   
            PlaySound(sounds[SOUND_COINS]);
            inDialogueWithOptions = false;
            YesorNo = true;
            return;
        } 
        else if (CheckCollisionPointRec(mousePos, noBox))
        { 
            PlaySound(sounds[SOUND_HOVER_ITEMS]);
            inDialogueWithOptions = false;
            YesorNo = false;
            return;
        }
        

    }

    return;
}

void RenderDialogue()
{
    if (!inDialogue) return;

    DrawRectangleRec(boxOutline, boxColor);
    DrawRectangleRec(dialogueBox, BLACK);

    std::string text = dialogueLines[currentDialogueLine].substr(0, dialogueCharIndex);
    DrawText(text.c_str(), dialogueBox.x + 10, dialogueBox.y + 10, 20, WHITE);

    if (dialogueCharIndex >= dialogueLines[currentDialogueLine].length())
    {
        DrawText("CLICK TO CONTINUE...", dialogueBox.x + 5, dialogueBox.y + 180, 20, WHITE);
    }
}

void RenderDialogueWithOptions()
{
 if (!inDialogueWithOptions) return;

    DrawRectangleRec(boxOutline, boxColor);
    DrawRectangleRec(dialogueBox, BLACK);

    std::string text = dialogueLines[currentDialogueLine].substr(0, dialogueCharIndex);
    DrawText(text.c_str(), dialogueBox.x + 10, dialogueBox.y + 10, 20, WHITE);

    if (dialogueCharIndex >= dialogueLines[currentDialogueLine].length())
    {
        // Highlight boxes on hover
        Vector2 mousePos = GetMousePosition();
        bool yesHovered = CheckCollisionPointRec(mousePos, yesBox);
        bool noHovered = CheckCollisionPointRec(mousePos, noBox);

        DrawRectangleRec(yesBox, yesHovered ? LIGHTGRAY : GRAY);
        DrawText("YES", yesBox.x + 15, yesBox.y + 15, 20, BLACK);
        
        DrawRectangleRec(noBox, noHovered ? LIGHTGRAY : GRAY);
        DrawText("NO", noBox.x + 15, noBox.y + 15, 20, BLACK);
    }


}

//Stories - ACT1
void Act1_Introduction()
{
    if(Act1_Introduced) return;
    StartDialogue
    ({
        "Who... where am i?",
        "Why can't I remember anything?",
        "[You heard rustling in the distance]",
        "I don't know what happened to me, but my instinct tells \nme to be careful."
    });

    Act1_Introduced = true;
} 

void Act1_HermitLine() 
{
   if(!Act1_HermitInteracted) StartDialogue
    ({
        "Hermit: Many have entered these woods... few return.",
        "Hermit: If you're heading to the dungeon, take this...",
        "[Potions Obtained]",
        "Hermit: Farewell..."
    });
    else StartDialogue({"Go!", "I have nothing more to say."});

    Act1_HermitInteracted = true;
}

void Act1_WoundedKnight()
{
    if(!Act1_WoundedKnightInteracted)StartDialogue
    ({
        "Wounded Knight: The dungeon...",
        "Wounded Knight: it was supposed to be sealed.",
        "Wounded Knight: Something has awakened inside...",
        "Wounded Knight: Something ancient.",
        "Wounded Knight: I won't live long, take this...",
        "[Obtained Food]",
    });
    else StartDialogue({"....."});

    Act1_WoundedKnightInteracted = true;
}

void Act1_Dungeon1()
{
    if(currentGameState == IN_DUNGEON && !Act1_firstTimeInDungeon)
    {
        StartDialogue({
            "This dungeon feels ominous..."
        });
        Act1_firstTimeInDungeon = true;
    }
}

void Act1_GoldenRing()
{
    if(currentGameState == IN_DUNGEON && goldenRing.IsPickedUp() == false)
    {
        StartDialogue({
            "Do you wish to pick this ring?"
        });
    }
}