#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorBar :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //���H�̍Œ�}�X�i�c�����j
public:
    MazeGeneratorBar();
    ~MazeGeneratorBar();
    bool Init() override;
    bool Update() override;
};

