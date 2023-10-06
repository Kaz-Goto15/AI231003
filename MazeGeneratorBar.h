#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorBar :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //迷路の最低マス（縦横幅）
public:
    MazeGeneratorBar();
    ~MazeGeneratorBar();
    bool Init() override;
    bool Update() override;
};

