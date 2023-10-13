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
	virtual bool Update() = 0;
	void Generate(int x, int y);
	void Output();
	std::string GetModelName() { return modelName_; }
protected:
	enum MAZE_ATTRIBUTE {
		MAP_WALL = 0,
		MAP_FLOOR = 1
	};
	std::string outStr = { "Å°", "Å@" };
	static const std::string MAZE_OUT_;
	std::string modelName_;
	int width_, height_;
	bool isFinished;
	vector<vector<int>> map_;
};

