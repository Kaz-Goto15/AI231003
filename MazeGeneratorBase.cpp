﻿#include "MazeGeneratorBase.h"
#include <iostream>
#include <sstream>
#include <windows.h>

MazeGeneratorBase::MazeGeneratorBase(std::string modelName):
	modelName_(modelName),
	width_(-1),height_(-1)
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
	Create();
}

void MazeGeneratorBase::Output()
{
	//std::system("cls");
	std::stringstream ss;
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			ss << outStr[map_[h][w]];
		}
		std::cout << ss.str() << std::endl;
		ss.str("");
	}
	std::cout << std::endl;
}