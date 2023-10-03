#include "MazeGeneratorBase.h"
#include <iostream>
#include <sstream>
MazeGeneratorBase::MazeGeneratorBase()
{
}

MazeGeneratorBase::~MazeGeneratorBase()
{
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
