#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorBar :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //迷路の最低マス（縦横幅）
    static const int FIRST_WALL_ROW = 2;
    struct POINT {
        int x;
        int y;
    };
    //static REFER REFERENCE_POINT = { 2, 2 };
    //REFERENCE_POINT.x = 1;
    enum DIRECTION
    {
        DIR_LEFT = 0,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_UP,
        DIR_MAX
    };
    bool IsEven(int num) { return !(num % 2); }
public:
    MazeGeneratorBar();
    ~MazeGeneratorBar();
    bool Init() override;
    bool Update() override;
};

