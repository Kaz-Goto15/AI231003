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
bool MazeGeneratorBar::Init()
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
	if (width_ % 2 == 0) {
		cout << "横幅が偶数です。指定値に1を加え奇数にします。\n";
		width_++;
	}
	if (height_ % 2 == 0) {
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

bool MazeGeneratorBar::Update()
{
    //ランダム値(0123 or 012)を決め

    //2ずつy,xに棒立て判定
	/*
	//棒を立て倒す
            var rnd = new Random();
    for (int x = 2; x < width - 1; x += 2)
            {
                for (int y = 2; y < height - 1; y += 2)
                {
                    maze[x, y] = Wall; // 棒を立てる

                    // 倒せるまで繰り返す
                    while (true){
                        // 1行目のみ上に倒せる
                        int direction;
                        if (y == 2)
                            direction = rnd.Next(4);
                        else
                            direction = rnd.Next(3);

                        // 棒を倒す方向を決める
                        int wallX = x;
                        int wallY = y;
                        switch (direction)
                        {
                            case 0: // 右
                                wallX++;
                                break;
                            case 1: // 下
                                wallY++;
                                break;
                            case 2: // 左
                                wallX--;
                                break;
                            case 3: // 上
                                wallY--;
                                break;
                        }
                        // 壁じゃない場合のみ倒して終了
                        if (maze[wallX, wallY] != Wall)
                        {
                            maze[wallX, wallY] = Wall;
                            break;
                        }
                    }
                }
            }
	
	
	
	*/
	return true;
}

