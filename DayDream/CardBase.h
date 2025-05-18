// CardBase.h
#pragma once
#include "raylib.h"

typedef struct CardBase CardBase;

// Card's father type
struct CardBase
{
    Rectangle bounds;
    bool isRevealed;

    void (*reset)(CardBase *self);
    void (*draw)(CardBase *self);
    void (*onReveal)(CardBase *self);
    void (*onInteract)(CardBase *self);
    int indexInArray; // for what?
    void* data; // for what?
};
