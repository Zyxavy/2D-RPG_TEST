#ifndef STORY_LINE_HPP
#define STORY_LINE_HPP

#include <raylib.h>
#include <string>
#include <vector>

//externs
extern Rectangle boxOutline;
extern Rectangle dialogueBox;

extern bool inDialogue;
extern bool inDialogueWithOptions;
extern std::vector<std::string> dialogueLines;
extern size_t currentDialogueLine;
extern size_t dialogueCharIndex;
extern float dialogueTimer;
extern bool dialogueSkipped;

extern bool YesorNo; //  1 yes 2 no

extern bool Act1_HermitInteracted, Act1_WoundedKnightInteracted;
extern bool Act1_Introduced;
extern bool Act1_firstTimeInDungeon;

extern bool Act2_VillageChiefInteracted,Act2_VillagerInteracted, mutantFrogKilled;
extern bool Act2_VillageChiefRewardClaimed;

extern bool dungeonKey, plainsKey;

void StartDialogue(const std::vector<std::string>& lines);
void StartDialogueWithOptions(const std::vector<std::string>& lines);
void UpdateDialogue();
void UpdateDialogueWithOptions();
void RenderDialogue();
void RenderDialogueWithOptions();


//storylines -Act1 Forest of Beginnings
void Act1_Introduction();
void Act1_HermitLine();
void Act1_WoundedKnight();
void Act1_Dungeon1();
void Act1_GoldenRing();

//Act 2 Village of Emberdale
void Act2_Introduction();
void Act2_VillageCheif1();
void Act2_RandomVillager1();
void Act2_RandomVillager2();
void Act2_RandomVillager3();


#endif // STORY_LINE_HPP