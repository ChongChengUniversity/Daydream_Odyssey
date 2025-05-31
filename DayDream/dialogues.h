// dialogues.h

#ifndef DIALOGUES_H
#define DIALOGUES_H

#include "story.h" // 為了使用 DialogueLine 結構體

// 開場劇情
extern DialogueLine openingDialogue[];
extern const int openingDialogueCount;

// 每關拿到鑰匙時的對話
extern DialogueLine keyAcquiredDialogue_L1[];
extern const int keyAcquiredDialogue_L1_Count;
extern DialogueLine keyAcquiredDialogue_L2[];
extern const int keyAcquiredDialogue_L2_Count;
extern DialogueLine keyAcquiredDialogue_L3[];
extern const int keyAcquiredDialogue_L3_Count;
extern DialogueLine keyAcquiredDialogue_L4[];
extern const int keyAcquiredDialogue_L4_Count;
extern DialogueLine keyAcquiredDialogue_L5[];
extern const int keyAcquiredDialogue_L5_Count;
extern DialogueLine keyAcquiredDialogue_L6[];
extern const int keyAcquiredDialogue_L6_Count;
extern DialogueLine keyAcquiredDialogue_L7[];
extern const int keyAcquiredDialogue_L7_Count;
extern DialogueLine keyAcquiredDialogue_L8[];
extern const int keyAcquiredDialogue_L8_Count;
extern DialogueLine keyAcquiredDialogue_L9[];
extern const int keyAcquiredDialogue_L9_Count;
extern DialogueLine keyAcquiredDialogue_L10[];
extern const int keyAcquiredDialogue_L10_Count;

// 換季時的對話
extern DialogueLine seasonChange_SpringStart[];
extern const int seasonChange_SpringStart_Count;
extern DialogueLine seasonChange_SummerStart[];
extern const int seasonChange_SummerStart_Count;
extern DialogueLine seasonChange_AutumnStart[];
extern const int seasonChange_AutumnStart_Count;
extern DialogueLine seasonChange_WinterStart[]; // 魔王關前的對話
extern const int seasonChange_WinterStart_Count;

// key hint dialogue
extern DialogueLine keyHint[];
extern const int keyHint_Count;

// 結局對話
extern DialogueLine ending_True[];
extern const int ending_True_Count;
extern DialogueLine ending_Good[];
extern const int ending_Good_Count;
extern DialogueLine ending_Bad[]; // 如果有實現Bad End
extern const int ending_Bad_Count;

#endif // DIALOGUES_H