#pragma once
#include "MazeGeneratorBase.h"
#include <Windows.h>
class MazeGeneratorBar :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //迷路の最低マス（縦横幅）
    //static const POINT REFERENCE_POINT = { 2, 2 };
    struct REFER {
        int x;
        int y;
    }
    
    static const REFER REFERENCE_POINT = { 2,2 };
    //REFERENCE_POINT.x = 1;
    enum DIRECTION
    {
        DIR_LEFT = 0,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_UP,
        DIR_MAX
    };
public:
    MazeGeneratorBar();
    ~MazeGeneratorBar();
    bool Init() override;
    bool Update() override;
};

