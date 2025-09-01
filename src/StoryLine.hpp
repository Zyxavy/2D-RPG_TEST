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

extern bool Act2_VillageChiefInteracted, Act2_VillagerInteracted,  Act2_WeirdManInteracted, mutantFrogKilled;
extern bool Act2_VillageChiefRewardClaimed, Act2_BasementCleared, Act2_WeirdManRewardClaimed;

extern bool Act3_IslanderInteracted, Act3_IslandersQuestCompleted;
extern bool Act3_LostTrinketFound, Act3_MonsterSquidKilled;

extern bool Act4_LostTempleIntroduced, Act4_OldHermitInteracted;
extern bool Act4_LostTempleLevel1Cleared, Act4_SpecialGolemKilled;
extern bool Act4_AllItemsCollected, Act4_WeirdManSecondMeetingInteracted, Act4_BadEndingAchieved, Act4_GoodEndingAchieved;
extern bool Ending_GuardianKilled;

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
void Act2_WeirdMan();

//Act 3 Island of Aurmir
void Act3_Islander();

//ACT 4 Lost Temple
void Act4_LostTempleIntroduction();
void Act4_oldHermit();

void Act4_WeirdManSecondMeeting();

void Act4_BadEnding();
void Act4_GoodEnding();

void Ending_Banished();
void Ending_Ascended();

void Ending_VillagePraises();

#endif // STORY_LINE_HPP