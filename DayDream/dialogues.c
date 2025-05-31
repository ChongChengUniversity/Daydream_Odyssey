// dialogues.c
#include "dialogues.h"
#include "story.h" // 為了使用 DialogueLine 結構體

// 開場劇情
DialogueLine openingDialogue[] = {
    {"", "A long time ago, or perhaps, just yesterday..."},
    {"", "Someone walked into an endless daydream."},
    {"", "No door, no exit, only key after key, guiding him deeper."},
    {"", "He forgot who he was, and why he came here."},
    {"", "Only remembering someone said: \"Find the last key, and you can wake up.\""},
    {"", "But how did the dream begin?"},
    {"", "And what does it mean to wake up?"},
    {"", "Those familiar scenes, repeatedly appeared in different seasons."},
    {"", "Everything is too real, so real... one dares not to doubt."},
    {"", "Now, the journey will begin again."},
    {"", "He will search for an exit in the maze,"},
    {"", "But does not know if he is chasing..."},
    {"", "An exit, or a reason to escape."}
};
const int openingDialogueCount = sizeof(openingDialogue) / sizeof(openingDialogue[0]);

// 每關拿到鑰匙時的對話
DialogueLine keyAcquiredDialogue_L1[] = {
    {"", "This place is strange, but I'm not afraid. In fact... there's a sense of peace."}
};
const int keyAcquiredDialogue_L1_Count = sizeof(keyAcquiredDialogue_L1) / sizeof(keyAcquiredDialogue_L1[0]);

DialogueLine keyAcquiredDialogue_L2[] = {
    {"", "Another key? I feel like I've forgotten something important..."}
};
const int keyAcquiredDialogue_L2_Count = sizeof(keyAcquiredDialogue_L2) / sizeof(keyAcquiredDialogue_L2[0]);

DialogueLine keyAcquiredDialogue_L3[] = {
    {"", "Although this place is unfamiliar, it's much gentler than the outside world."}
};
const int keyAcquiredDialogue_L3_Count = sizeof(keyAcquiredDialogue_L3) / sizeof(keyAcquiredDialogue_L3[0]);

DialogueLine keyAcquiredDialogue_L4[] = {
    {"", "The season changed? Summer always made me think of stress, competition... and that parting."}
};
const int keyAcquiredDialogue_L4_Count = sizeof(keyAcquiredDialogue_L4) / sizeof(keyAcquiredDialogue_L4[0]);

DialogueLine keyAcquiredDialogue_L5[] = {
    {"", "Right, I once saw a scene like this in a dream... No, was it really a dream?"}
};
const int keyAcquiredDialogue_L5_Count = sizeof(keyAcquiredDialogue_L5) / sizeof(keyAcquiredDialogue_L5[0]);

DialogueLine keyAcquiredDialogue_L6[] = {
    {"", "Is it only in dream that I can pretend nothing ever happened?"}
};
const int keyAcquiredDialogue_L6_Count = sizeof(keyAcquiredDialogue_L6) / sizeof(keyAcquiredDialogue_L6[0]);

DialogueLine keyAcquiredDialogue_L7[] = {
    {"", "These winds, these fallen leaves... just like that day."}
};
const int keyAcquiredDialogue_L7_Count = sizeof(keyAcquiredDialogue_L7) / sizeof(keyAcquiredDialogue_L7[0]);

DialogueLine keyAcquiredDialogue_L8[] = {
    {"", "I thought I had forgotten, but actually, I just didn't want to remember."}
};
const int keyAcquiredDialogue_L8_Count = sizeof(keyAcquiredDialogue_L8) / sizeof(keyAcquiredDialogue_L8[0]);

DialogueLine keyAcquiredDialogue_L9[] = {
    {"", "If the truth is painful, I'd rather this dream... never end."}
};
const int keyAcquiredDialogue_L9_Count = sizeof(keyAcquiredDialogue_L9) / sizeof(keyAcquiredDialogue_L9[0]);

DialogueLine keyAcquiredDialogue_L10[] = {
    {"", "Reaching here... I realized this adventure wasn't about escaping, it was about choosing."},
    {"", "I can continue to be a dreamer who remembers nothing, or... open my eyes and face the me who once gave up."}
};
const int keyAcquiredDialogue_L10_Count = sizeof(keyAcquiredDialogue_L10) / sizeof(keyAcquiredDialogue_L10[0]);

// 換季時的對話
DialogueLine seasonChange_SpringStart[] = {
    {"???", "You've finally arrived."},
    {"You", "......Where is this?"},
    {"???", "No hurry, walk slowly. You'll see, as long as you are still willing."}
};
const int seasonChange_SpringStart_Count = sizeof(seasonChange_SpringStart) / sizeof(seasonChange_SpringStart[0]);

DialogueLine seasonChange_SummerStart[] = {
    {"You", "(Opens eyes, sweat on forehead): How... did the weather change?"},
    {"???", "Have you forgotten? That unavoidable parting, that unspoken word."},
    {"You", "I... don't remember."},
    {"???", "That's what you chose to forget. But memories don't just disappear."}
};
const int seasonChange_SummerStart_Count = sizeof(seasonChange_SummerStart) / sizeof(seasonChange_SummerStart[0]);

DialogueLine seasonChange_AutumnStart[] = {
    {"You", "(Steps on fallen leaves): The sound here, it's like... I've heard it somewhere before."},
    {"???", "You once left an unsent letter here."},
    {"You", "Whose is it?"},
    {"???", "If you don't open it, you'll never know."}
};
const int seasonChange_AutumnStart_Count = sizeof(seasonChange_AutumnStart) / sizeof(seasonChange_AutumnStart[0]);

DialogueLine seasonChange_WinterStart[] = {
    {"You", "It's so cold here..."},
    {"???", "This is the end of the dream."},
    {"You", "So... who exactly are you?"},
    {"???", "I am you."},
    {"You", "Impossible!!"},
    {"Boss", "Denial is useless, I am the you who enjoys escaping, indulging in dreams, rejecting responsibility."},
    {"You", "If I defeat the boss, I can wake up... right?"},
    {"Boss", "(Spreading arms): Hahaha! What if you wake up?"},
    {"Boss", "You chose to fall asleep, coming here to seek my protection, and I can build a paradise for you."},
    {"Boss", "You can stay here forever, no longer bothered by reality, come!"},
    {"You", "I don't need you. I can go back."},
    {"Boss", "Are you sure?"},
    {"Boss", "When you wake up, you'll still face all those unresolved issues, the people you avoided, and the never-good-enough self."},
    {"You", "(Silent for a moment) I know. But even if it hurts, reality is more worth living than a dream."},
    {"Boss", "......Then come and take the last key I guard. But remember—defeating me won't make you perfect. It just means you're finally willing to admit that you can live even if you're not perfect."}
};
const int seasonChange_WinterStart_Count = sizeof(seasonChange_WinterStart) / sizeof(seasonChange_WinterStart[0]);

// door needs key to unlock hint
DialogueLine keyHint[] = {
    {"Hint:", "I need to find the key first."}
};
const int keyHint_Count = sizeof(keyHint) / sizeof(keyHint[0]);

// 結局對話
DialogueLine ending_True[] = {
    {"You", "I don't know how difficult the world will be when I wake up."},
    {"You", "But I want to try... not to escape anymore."},
    {"", "The dream won't help you unlock the shackles of reality, but it can remind you—you've always held the key to walk out."},
    {"", "You are still you, carrying wounds, carrying memories, continuing to walk forward."}
};
const int ending_True_Count = sizeof(ending_True) / sizeof(ending_True[0]);

DialogueLine ending_Good[] = {
    {"You", "Perhaps... this is enough. No responsibility, no pain. Only... me."},
    {"", "Not everyone is ready to wake up. Some choose to stay in the dream, because it doesn't force them to remember."},
    {"", "And you, chose to quietly sleep, becoming an eternal traveler in the infinitely prolonged gentle lie."}
};
const int ending_Good_Count = sizeof(ending_Good) / sizeof(ending_Good[0]);

DialogueLine ending_Bad[] = {
    {"", "Something in my memory dissipated, I seem to have forgotten something very important."},
    {"", "Bad end"}
};
const int ending_Bad_Count = sizeof(ending_Bad) / sizeof(ending_Bad[0]);