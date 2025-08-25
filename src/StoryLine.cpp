#include "StoryLine.hpp"
#include "GameFunctions.hpp"
#include "GameMenu.hpp"
#include "Items.hpp"
#include "Heroes.hpp"
#include "Entities.hpp"
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

bool Act2_VillageChiefInteracted = false, Act2_VillagerInteracted = false, Act2_WeirdManInteracted = false, mutantFrogKilled = false;
bool Act2_VillageChiefRewardClaimed = false, Act2_BasementCleared = false, Act2_WeirdManRewardClaimed = false;

bool Act3_IslanderInteracted = false, Act3_IslandersQuestCompleted = false;
bool Act3_LostTrinketFound = false, Act3_MonsterSquidKilled = false;

bool Act4_LostTempleIntroduced = false, Act4_OldHermitInteracted = false;
bool Act4_LostTempleLevel1Cleared = false, Act4_SpecialGolemKilled = false;
bool Act4_AllItemsCollected = false, Act4_WeirdManSecondMeetingInteracted = false, Act4_BadEndingAchieved = false, Act4_GoodEndingAchieved = false;


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
        "Wounded Knight: I won't last long...",
        "Wounded Knight: I was attacked by a monster...",
        "Wounded Knight: I tried to fight it, but it was too strong...",
        "Wounded Knight: Please, take this...",
        "[Obtained Food]",
        "Wounded Knight: I hope you fare better than I did...",
    });
    else StartDialogue({"....."});

    Act1_WoundedKnightInteracted = true;
}

void Act1_Dungeon1()
{
    if(currentGameState == IN_DUNGEON && !Act1_firstTimeInDungeon)
    {
        StartDialogue({
            "This place is dark and eerie...",
            "I can feel the presence of monsters lurking around.",
            "I must be careful, I don't know what awaits me here.",
            "I should find a way to get out of here as soon as possible."
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

//act 2
void Act2_Introduction()
{
    if(currentGameState == IN_PLAINS)
    {
        StartDialogue({
            "Finally, I made it out of that dungeon.",
            "This place seems peaceful, but I must stay alert.",
            "I should explore this village and see if anyone needs help.",
        });
    }
}

void Act2_VillageCheif1()
{
    if(!Act2_VillageChiefInteracted)StartDialogue
    ({
        "Village Chief: Please help us...",
        "Village Chief: A frog monster has been attacking our \nvillage recently.",
        "Village Chief: Many of us are scared to even come out...",
        "Village Chief: If you manage to kill that...thing.",
        "Village Chief: I will reward you handsomely.",
        "[Objective: Kill the Mutant Frog]",
    });
    else StartDialogue({"Is it gone?"});

    if(mutantFrogKilled && !Act2_VillageChiefRewardClaimed) StartDialogue
    ({
        "Thank you, kind hero...",
        "Here take this.",
        "[Obtained 2300 Gold]",
        "[Obtained 7 Health Potions]",
        "[Obtained 5 Foods]"
    });

    Act2_VillageChiefInteracted = true;
}

void Act2_RandomVillager1()
{
    if(!Act2_VillagerInteracted)StartDialogue
    ({
        "Random Villager: Hi there!",
        "Random Villager: I'm in charge of keeping this village safe \nfrom that monster.",
        "Random Villager: I may not look strong, but I can handle myself.",
        "Random Villager: Talk to the village chief if you need something.",
        "Random Villager: ...",
        "Random Villager: Scram!",
    });
    else StartDialogue({"What?"});

    Act2_VillagerInteracted = true;
}

void Act2_WeirdMan()
{
    if(!Act2_WeirdManInteracted) StartDialogue
    ({
        "Weird Man: We are all cursed...",
        "Weird Man: We are all doomed...",
        "Weird Man: We are all lost...",
        "Weird Man: We are all...",
        "Weird Man: We are all...",
        "Weird Man: We are all... dead.",
        "[Eliminate all the enemies in the basement]"
    });
    else 
    {
        StartDialogue
        ({
            "Weird Man: Hehe...",
            "Weird Man: Hehehhehehhehehhehhhehhehehhehehhehheh",
        });
    }   

    if(Act2_BasementCleared && !Act2_WeirdManRewardClaimed)
    {
        StartDialogue
        ({
            "Weird Man: ahhh... you...",
            "Weird Man: MONSTER!",
            "Weird Man: You killed them all!",
            "Weird Man: You killed my friends!",
            "Weird Man: You killed my family!",
            "Weird Man: You killed my... Please... Please... don't hurt me...",
            "Weird Man: Here take this... Please... don't kill me...",
            "[Obtained Green Heart of Aurmir]",
            
        });

        Act2_WeirdManRewardClaimed = true;
        greenHeart.SetPickedUpState(true);
    }
    Act2_WeirdManInteracted = true;
}

//act 3
void Act3_Islander()
{

    if(Act3_IslandersQuestCompleted)
    {
        StartDialogue
        ({
            "Islander: Talk to me again if you want to buy something.",
            
        });

        inShop = true;
        return;
    }

    if(Act3_LostTrinketFound && !Act3_IslandersQuestCompleted)
    {
        StartDialogue
        ({
            "Islander: You found it!",
            "Islander: Thank you so much!",
            "Islander: Here, take this as a reward.",
            "[Obtained 10x Health Potions]",
            "[Obtained 7x Foods]",
            "Islander: I'll let you in on a deal, there's even a discount for you.",
            "Islander: talk to me again if you want to buy something.",
        });

        Player.SetHealthPotions(Player.GetRemainingHealthPotions() + 10);
        Player.SetEnergyFoods(Player.GetRemainingEnergyFoods() + 7);
        Act3_IslandersQuestCompleted = true;
        return;
    }

    if(!Act3_IslanderInteracted) StartDialogue
    ({
        "Islander: Hello there, stranger.",
        "Islander: I am the islander of this place.",
        "Islander: I can help you with your journey, but first, \nI need you to do something for me.",
        "Islander: I lost my trinket somewhere, \ncan you find it for me?",
        "[Objective: Find the Lost Trinket]",
    });
    else StartDialogue({"Have you found it?"});

    Act3_IslanderInteracted = true;

}

//act 4
void Act4_LostTempleIntroduction()
{
    if(currentGameState == IN_LOST_TEMPLE_ENTRANCE && !Act4_LostTempleIntroduced)
    {
        StartDialogue({
            "This place feels ancient...",
            "I wonder what secrets it holds..."
        });
        Act4_LostTempleIntroduced = true;
    }
}

void Act4_oldHermit()
{
    if(!Act4_OldHermitInteracted) StartDialogue
    ({
        "Old Hermit: Oho! if it isn't you!",
        "Old Hermit: You have come far.",
        "Old Hermit: This temple holds many secrets.",
        "Old Hermit: But beware, not all is as it seems.",
        "Old Hermit: If you seek the truth, you must be \nprepared to face the darkness within.",

    });
    else StartDialogue({
        "Old Hermit: I have nothing more to say.",
        "Old Hermit: What lies ahead is not for the faint of heart."});

    Act4_OldHermitInteracted = true;
}

void Act4_WeirdManSecondMeeting()
{

    if(goldenRing.IsPickedUp() && cursedGoldenKey.IsPickedUp() && greenHeart.IsPickedUp()
       && eyeCore.IsPickedUp() && pitchFork.IsPickedUp())
    {
        Act4_AllItemsCollected = true;
    }
    else Act4_AllItemsCollected = false;


    if(!Act4_WeirdManSecondMeetingInteracted) 
    {StartDialogue
    ({
        "Weird Man?: We have met again... hehehe...",
        "Weird Man?: I see you have grown stronger... hehehe...",
        "Weird Man?: But strength alone will not save you...",
        "Weird Man?: The Guardian of this temple is not to be trifled with...\n\nhehehe...",
        "Weird Man?: Let me tell you a tale... hehehe...",
        "Weird Man?: long ago, this temple was built to protect a great power...\n\nhehehe...",
        "Weird Man?: A power that could change the fate of the world...",
        "Weird Man?: Many have tried to claim it... hehehe...\n\nBut none have succeeded...Because they were not worthy...",
        "Weird Man?: The only way to defeat the Guardian is by collecting \n\nall the sacred items...\nhehehe...",
        "Weird Man?: Only then will you be able to face it and claim \n\nthe power within... \nhehehe...",
        "Weird Man?: So... do you have all the items? hehehe...",
    });
     Act4_WeirdManSecondMeetingInteracted = true;
    }
    else if (Act4_WeirdManSecondMeetingInteracted && !Act4_AllItemsCollected)
    {
        StartDialogue
        ({
            "Weird Man: Hehehe...",
            "Weird Man: Hehehehhehehhehehhehhhehhehehhehehhehheh",
            "Weird Man: AHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA\nHAHAHHAHAHHAHAHHAHAHAHA!!",
            "Weird Man: You are not worthy... hehehe...\n\nyou are just like the others...",
            "Weird Man: You will never defeat the Guardian... hehehe...",
            "Weird Man: You will never defeat me... hehehe...",
        });

        Act4_BadEndingAchieved = true;
    }
    else if (Act4_WeirdManSecondMeetingInteracted && Act4_AllItemsCollected)
    {
        StartDialogue
        ({
            "Weird Man: I see you have collected all the items... hehehe...",
            "Weird Man: You are indeed worthy... hehehe...",
            "Weird Man: Do not disappoint me now... hehehe...",
            "Weird Man: Go forth and claim your destiny.",
        });

        Act4_GoodEndingAchieved = true;
    }
}

void Act4_BadEnding()
{
    Player.SetZone(ZONE_LOST_TEMPLE_BAD_ENDING);
    currentGameState = IN_LOST_TEMPLE_BAD_ENDING;

    StartDialogue
    ({
        "????: Foolish mortal...",
        "????: Where do you think you're going?",
        "????: You are not worthy of the power you seek...",
        "????: You shall suffer the same fate as those before you...",
    });

}

void Act4_GoodEnding()
{
    Player.SetZone(ZONE_LOST_TEMPLE_GOOD_ENDING);
    currentGameState = IN_LOST_TEMPLE_GOOD_ENDING;

    StartDialogue
    ({
        "Guardian: You have proven yourself worthy...",
        "Guardian: The power you seek will be yours to command...",
        "Guardian: But first, you must take it from me...",
        "Guardian: Prepare yourself brave mortal.",
    });

}