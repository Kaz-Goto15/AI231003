#pragma once
#include <vector>
#include <string>
using std::vector;

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

	int width_, height_;
	vector<vector<int>> map_;
	std::string modelName_;
};

