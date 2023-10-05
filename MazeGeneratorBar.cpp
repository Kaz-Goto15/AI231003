#include "MazeGeneratorBar.h"
#include <iostream>
using std::cout;
MazeGeneratorBar::MazeGeneratorBar():
	MazeGeneratorBase("棒倒し法")
{
}

MazeGeneratorBar::~MazeGeneratorBar()
{
}
//棒倒し法のやりかた
void MazeGeneratorBar::Generate(int x, int y)
{
	width_ = x;
	height_ = y;
	//迷路の大きさが適しているか
	if (x < MIN_LENGTH) {
		cout << "指定された横幅の値が小さすぎます。生成可能な最低値に置換します。\n";
		x = MIN_LENGTH;
	}
	if (y < MIN_LENGTH) {
		cout << "指定された縦幅の値が小さすぎます。生成可能な最低値に置換します。\n";
		y = MIN_LENGTH;
	}
	if (x % 2 == 0) {
		cout << "横幅が偶数です。指定値に1を加え奇数にします。\n";
		x++;
	}
	if (y % 2 == 0) {
		cout << "縦幅が偶数です。指定値に1を加え奇数にします。\n";
		y++;
	}

	//指定サイズで生成、外周を壁に
	vector<vector<int>> map(y, vector<int>(x, MAP_FLOOR));
	for (int h = 0; h < y; h++) {
		for (int w = 0; w < x; w++) {
			if (h == 0 || w == 0 || h == y - 1 || w == x - 1) {
				map[h][w] = MAP_WALL;
			}
		}
	}
	Output();
	return true;
}

