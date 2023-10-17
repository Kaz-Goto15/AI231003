#pragma once
#include <vector>
#include <string>
using std::vector;

namespace {
	static const int UPDATE_DELAY = 500;
}
class MazeGeneratorBase
{
public:
	MazeGeneratorBase(std::string modelName);
	virtual ~MazeGeneratorBase();
	virtual bool Init() = 0;
	virtual bool Create() = 0;
	void Generate(int x, int y);
	void Output();
	std::string GetModelName() { return modelName_; }
protected:
	enum MAZE_ATTRIBUTE {
		MAP_WALL = 0,
		MAP_FLOOR = 1,
		MAP_MAX
	};
	std::string outStr[MAP_MAX] = {"Å°", "Å@"};
	std::string modelName_;
	int width_, height_;
	vector<vector<int>> map_;
};

