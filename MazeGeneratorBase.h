#pragma once
#include <vector>
using std::vector;

class MazeGeneratorBase
{
public:
	MazeGeneratorBase();
	virtual ~MazeGeneratorBase();
	virtual void Generate() = 0;
	void Output();
protected:
	enum MAZE_ATTRIBUTE {
		MAP_WALL = 0,
		MAP_FLOOR = 1,
	};

	int width_, height_;
	vector<vector<int>> map_;
};

