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

	//指定サイズで生成、外周を壁にする
	//床の偶数座標を開始座標リストに追加
	map_ = vector<vector<int>>(height_, vector<int>(width_, MAP_FLOOR));
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			if (h == 0 || w == 0 || h == height_ - 1 || w == width_ - 1) {
				map_[h][w] = MAP_WALL;
			}else
			if (IsEven(h) && IsEven(w)) {
				startPointList.push_back({ w,h });
			}

		}
	}

	Output();
	return true;
}

bool MazeGeneratorExtend::Update()
{
	//候補座標から１つ選び、それを消去
	//選んだ座標が床であれば、現在拡張中の壁配列をクリアし、拡張を行う
	while (startPointList.size() > 0){
		int index = rand() % startPointList.size();
		POINT pts = startPointList[index];
		startPointList.erase(startPointList.begin() + index);
		
		if (map_[pts.y][pts.x] == MAP_FLOOR) {
			currentWallPoint.clear();
			ExtendWall(pts);
		}
		Output();
	}
	isFinished = true;

	return true;
}

//座標から壁拡張
void MazeGeneratorExtend::ExtendWall(POINT pts)
{
	//自身の座標を壁にする
	// １マス先が床であり、もう１マス先が現在拡張中の壁配列に存在しない座標である方向を収集し、ランダムで決める
	// 拡張後、その方向の2マス先が元から壁であれば拡張を終了
	// 　　　　　　　　　　　　　元から通路であれば、その地点で拡張を行う
	// 方向決めが０だった場合、最後の要素を削除した後、最後の要素で拡張を行う
	
	//伸ばせる方向決め
	vector<DIRECTION> dirList;
	for (DIRECTION d = DIR_LEFT; d < DIR_MAX; d = static_cast<DIRECTION>(d + 1)){
		POINT dirPts;
		StoreDirectionValue(&dirPts, d);
		if (IsDirCanExtend(pts, dirPts)) {
			dirList.push_back(d);
		}
	}

	//収集した方向のうちランダムに伸ばす
	if (dirList.size() > 0) {
		//自位置を壁に
		SetWall(pts);
		DIRECTION dir = dirList[rand() % dirList.size()];
		//2マス先が床の場合のみ続ける
		POINT dirPts;
		StoreDirectionValue(&dirPts, dir);
		POINT nextPts = pts + dirPts + dirPts;
		bool isFloor = (map_[nextPts.y][nextPts.x] == MAP_FLOOR);
		SetWall(nextPts);
		SetWall(nextPts - dirPts);
		if (isFloor)ExtendWall(nextPts);
	}else {
		// すべて現在拡張中の壁にぶつかる場合、バックして再開
		currentWallPoint.pop_back();
		POINT beforePoint = currentWallPoint.back();
		ExtendWall(beforePoint);
	}
}

bool MazeGeneratorExtend::IsDirCanExtend(POINT pts, POINT ValueOnDir)
{
	POINT tmp = pts + ValueOnDir;
	return (map_[tmp.y][tmp.x] == MAP_FLOOR &&
		!IsCurrentWall(tmp + ValueOnDir));
}

bool MazeGeneratorExtend::IsCurrentWall(POINT pts)
{
	return std::find(currentWallPoint.begin(), currentWallPoint.end(), pts) != currentWallPoint.end();
}

void MazeGeneratorExtend::StoreDirectionValue(POINT* pts, DIRECTION dir)
{
	switch (dir)
	{
	case MazeGeneratorExtend::DIR_LEFT:
		pts->x = -1;
		pts->y = 0;
		break;
	case MazeGeneratorExtend::DIR_RIGHT:
		pts->x = 1;
		pts->y = 0;
		break;
	case MazeGeneratorExtend::DIR_DOWN:
		pts->x = 0;
		pts->y = 1;
		break;
	case MazeGeneratorExtend::DIR_UP:
		pts->x = 0;
		pts->y = -1;
		break;
	default:
		pts->x = 0;
		pts->y = 0;
		break;
	}
}

void MazeGeneratorExtend::SetWall(POINT pts)
{
	map_[pts.y][pts.x] = MAP_WALL;
	if (IsEven(pts)) {
		currentWallPoint.push_back(pts);
	}
}
