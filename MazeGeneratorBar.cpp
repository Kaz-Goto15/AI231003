#include "MazeGeneratorBar.h"
#include <iostream>
//#include <windows.h>
using std::cout;

MazeGeneratorBar::MazeGeneratorBar():
	MazeGeneratorBase("棒倒し法")
{
}

MazeGeneratorBar::~MazeGeneratorBar()
{
}
//棒倒し法のやりかた
bool MazeGeneratorBar::Init()
{
	srand((unsigned int)time(nullptr));

	//迷路の大きさが適しているか
	if (width_ < MIN_LENGTH) {
		cout << "指定された横幅の値が小さすぎます。生成可能な最低値に置換します。\n";
		width_ = MIN_LENGTH;
	}
	if (height_ < MIN_LENGTH) {
		cout << "指定された縦幅の値が小さすぎます。生成可能な最低値に置換します。\n";
		height_ = MIN_LENGTH;
	}
	if (IsEven(width_)) {
		cout << "横幅が偶数です。指定値に1を加え奇数にします。\n";
		width_++;
	}
	if (IsEven(height_)) {
		cout << "縦幅が偶数です。指定値に1を加え奇数にします。\n";
		height_++;
	}

	//指定サイズで生成、外周を壁に
	map_ = vector<vector<int>>(height_, vector<int>(width_, MAP_FLOOR));
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			if (h == 0 || w == 0 || h == height_ - 1 || w == width_ - 1) {
				map_[h][w] = MAP_WALL;
			}
		}
	}
	Output();
	return true;
}

bool MazeGeneratorBar::Create()
{
	//
	//迷路全体を構成する2次元配列を、幅高さ5以上の奇数で生成
	//迷路の外周を壁、それ以外を通路とする
	//外周の内側に基準となる壁(棒)を1セルおき(x,yともに偶数の座標)に配置
	//内側の壁(棒)を走査し、ランダムな方向に倒して壁とするが、以下に当てはまる方向には倒してはいけない。
	//  1行目の内側の壁以外では上方向に倒してはいけない。
	//  すでに棒が倒され壁になっている場合、その方向には倒してはいけない。
	for (int y = 1; y < height_ -1; y ++) {
		for (int x = 1; x < width_ -1; x ++) {
			if (IsEven(y) && IsEven(x)) {
				map_[y][x] = MAP_WALL;

				while (true) {
					int dir = rand();
					//方向決め　1行目のみ上も
					if (y == FIRST_WALL_ROW)dir %= DIR_MAX;
					else dir %= (DIR_MAX - 1);

					POINT target = { x,y };
					switch (dir){
					case DIR_LEFT:
						target.x--;
						break;
					case DIR_RIGHT:
						target.x++;
						break;
					case DIR_DOWN:
						target.y++;
						break;
					case DIR_UP:
						target.y--;
						break;
					}
					// 壁でなければ倒し抜ける
					if (map_[target.y][target.x] != MAP_WALL){
						map_[target.y][target.x] = MAP_WALL;
						break;
					}
				}

				//Sleep(UPDATE_DELAY);
				Output();
			}
		}
	}
	return true;
}

