// levelManager.h
#pragma once

#include<stdbool.h>

/// ��l�����d���A�]�Ҧp���s�}�l�C���^
void InitLevelManager();

/// �i�J�U�@���]�p�G�٦��U�@���^
void NextLevel();

/// ���o�ثe�����d�]1~4�^
int GetCurrentLevel();

/// ���o�`���d��
int GetTotalLevels();

bool IsFinalLevel();
