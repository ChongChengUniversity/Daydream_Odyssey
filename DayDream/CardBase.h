// CardBase.h
#pragma once
#include "raylib.h"

typedef struct CardBase CardBase;

typedef enum
{
    TYPE_DOOR,
    TYPE_ITEM,
    TYPE_ENEMY,
    TYPE_EMPTY,
    TYPE_KEY
} CardType;

struct CardBase {
    int row;
    int col;
    Rectangle bounds;           
    bool isRevealed;            
    void (*reset)(CardBase* self);    
    void (*draw)(CardBase* self);     
    void (*onReveal)(CardBase* self); 
    void (*onInteract)(CardBase* self); 
    int indexInArray;
    void* data;
    CardType type;
};

typedef struct {
    int row;
    int col;
} GridPos;

GridPos GetCardGridPosition(Rectangle bounds);

int GetCardIndexByGridPos(int row, int col);

CardBase* GetCardAt(int row, int col);
