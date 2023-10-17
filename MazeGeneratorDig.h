#pragma once
#include "MazeGeneratorBase.h"
class MazeGeneratorDig :
    public MazeGeneratorBase
{
private:
    static const int MIN_LENGTH = 5;    //ñ¿òHÇÃç≈í·É}ÉXÅiècâ°ïùÅj
    static const int FIRST_WALL_ROW = 2;
    struct POINT {
        int x;
        int y;

        bool operator == (const POINT pts) const {
            return (x == pts.x && y == pts.y);
        }
        POINT operator + (const POINT& pts) {
            POINT ret;
            ret.x = x + pts.x;
            ret.y = y + pts.y;
            return ret;
        }
        POINT operator - (const POINT& pts) {
            POINT ret;
            ret.x = x - pts.x;
            ret.y = y - pts.y;
            return ret;
        }
        POINT operator += (const POINT& pts) {
            return (*this + pts);
        }
        POINT operator -= (const POINT& pts) {
            return (*this - pts);
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
    bool IsEven(POINT pts) { return (IsEven(pts.x) && IsEven(pts.y)); }

    vector<POINT> startPointList;
    vector<POINT> currentWallPoint;
    void Dig(POINT pts);
    void StoreDirectionValue(POINT* pts, DIRECTION dir);
    void SetFloor(POINT pts);
    void StoreStartPoint(POINT* nextSPts);
public:
    MazeGeneratorDig();
    ~MazeGeneratorDig();
    bool Init() override;
    bool Create() override;
};

