#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorBar :
    public MazeGeneratorBase
{
private:
public:
    MazeGeneratorBar();
    ~MazeGeneratorBar();
    void Generate() override;
};

