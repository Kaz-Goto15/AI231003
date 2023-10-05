#include "MazeGeneratorBase.h"
#include <iostream>
#include <sstream>
MazeGeneratorBase::MazeGeneratorBase(std::string modelName):
	modelName_(modelName)
{
}

MazeGeneratorBase::~MazeGeneratorBase()
{
}

void MazeGeneratorBase::Generate(int x, int y)
{
	width_ = x;
	height_ = y;
	Init();
	while(true) {
		Update();
		Sleep(500);
	}
}

void MazeGeneratorBase::Output()
{
	std::stringstream ss;
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			ss << map_[h][w];
		}
		std::cout << ss.str() << std::endl;
		ss.str("");
	}
}