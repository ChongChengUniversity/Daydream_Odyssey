// CardBase.h
#pragma once
#include "raylib.h"

// �e�V�ŧi�]���F�i�H�� CardBase* ���С^
typedef struct CardBase CardBase;

// �w�q�d���@�q���c
struct CardBase {
    Rectangle bounds;           
    bool isRevealed;            
    void (*reset)(CardBase* self);    
    void (*draw)(CardBase* self);     
    void (*onReveal)(CardBase* self); 
    void (*onInteract)(CardBase* self); 
    int indexInArray;
    void* data;
};
