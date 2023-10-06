#include "MazeGeneratorBase.h"
#include <iostream>
#include <sstream>
#include <windows.h>

MazeGeneratorBase::MazeGeneratorBase(std::string modelName):
	modelName_(modelName),
	width_(-1),height_(-1),
	isFinished(false)
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
	while(!isFinished) {
		Sleep(UPDATE_DELAY);
		isFinished = Update();
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