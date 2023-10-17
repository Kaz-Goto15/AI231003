#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorExtend :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //���H�̍Œ�}�X�i�c�����j
    static const int FIRST_WALL_ROW = 2;
    struct POINT {
        int x;
        int y;

        bool operator == (const POINT pts) const {
            return (x == pts.x && y == pts.y);
        }
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
    bool IsCurrentWall(POINT pts);
    void StoreDirectionValue(POINT* pts, DIRECTION dir);
    void SetWall(POINT pts);
public:
    MazeGeneratorExtend();
    ~MazeGeneratorExtend();
    bool Init() override;
    bool Update() override;
};
