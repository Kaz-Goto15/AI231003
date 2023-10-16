#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorExtend :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //迷路の最低マス（縦横幅）
    static const int FIRST_WALL_ROW = 2;
    struct POINT {
        int x;
        int y;
    };
    enum DIRECTION
    {
        DIR_LEFT = 0,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_UP,
        DIR_MAX
    };
    bool IsEven(int num) { return !(num % 2); }

    vector<POINT> startPointList;
    vector<POINT> currentWallPoint;
    void ExtendWall(POINT pts);
    bool IsDirCanExtend(POINT pts, POINT ValueOnDir);
    bool IsCurrentWall(int currentPtsAttribute);
    POINT GetValueOnDirection(DIRECTION dir);
public:
    MazeGeneratorExtend();
    ~MazeGeneratorExtend();
    bool Init() override;
    bool Update() override;
};

