// CardBase.h
#pragma once
#include "raylib.h"

// �e�V�ŧi�]���F�i�H�� CardBase* ���С^
typedef struct CardBase CardBase;

// �w�q�d���@�q���c
struct CardBase {
    Rectangle bounds;           // �o�i�d������m�M�j�p�]x, y, width, height�^
    bool isRevealed;            // �o�i�d���ثe�O�_�w�g�Q½�}

    // �T�Ӵ��y�]�禡���С^
    void (*reset)(CardBase* self);    // ���m�d���]�\�^�h�^
    void (*draw)(CardBase* self);     // �e�ۤv�]�����έI���^
    void (*onReveal)(CardBase* self); // �Q½�}�ɭn������
    void (*onInteract)(CardBase* self); // �s�W�����y�I
};
