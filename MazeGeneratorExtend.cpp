#include "MazeGeneratorExtend.h"
#include <iostream>
#include <windows.h>
using std::cout;

MazeGeneratorExtend::MazeGeneratorExtend() :
	MazeGeneratorBase("壁伸ばし法")
{
}

MazeGeneratorExtend::~MazeGeneratorExtend()
{
}
//壁伸ばし法のやりかた
bool MazeGeneratorExtend::Init()
{
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

bool MazeGeneratorExtend::Update()
{
	//迷路全体を構成する2次元配列を、幅高さ5以上の奇数で生成
	//迷路の外周を壁、それ以外を通路とする
	//x, yともに偶数となる座標を壁伸ばし開始座標(候補)としてリストアップする
	//壁伸ばし開始座標からランダムで座標を取り出し、通路の場合のみ壁伸ばし処理を行う
	// ※すべての候補座標が壁になるまで繰り返す
	//壁伸ばし処理：
	//	指定座標を壁とする
	//	次に掘り進める方向(隣のセルが通路の方向かつ2セル先が現在拡張中の壁ではない方向)をランダムで決定
	//	拡張する方向2セル先が壁の場合(既存の壁に接続された場合)、壁の拡張を終了
	//	通路の場合、そのセルから続けて拡張します。(5. の処理を再帰的に呼び出す。)
	//	四方がすべて現在拡張中の壁の場合、拡張できる座標が見つかるまで、現在拡張中の壁をバックして、壁の拡張を再開する
	//すべての候補座標が壁(拡張済)になれば完了
	srand((unsigned int)time(nullptr));
	for (int y = 1; y < height_ - 1; y++) {
		for (int x = 1; x < width_ - 1; x++) {
			if (IsEven(y) && IsEven(x)) {
				map_[y][x] = MAP_WALL;

				while (true) {
					int dir = rand();
					//方向決め　1行目のみ上も
					if (y == FIRST_WALL_ROW)dir %= DIR_MAX;
					else dir %= (DIR_MAX - 1);

					POINT target = { x,y };
					switch (dir) {
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
					cout << "Tgt: (" << target.x << "," << target.y << ")\n";
					// 壁でなければ倒し抜ける
					if (map_[target.y][target.x] != MAP_WALL) {
						map_[target.y][target.x] = MAP_WALL;
						break;
					}
				}

				cout << "Now: (" << x << "," << y << ")\n";
				Sleep(UPDATE_DELAY);
				Output();
			}
		}
	}
	isFinished = true;

	return true;
}

