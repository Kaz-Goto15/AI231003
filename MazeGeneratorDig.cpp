#include "MazeGeneratorDig.h"
#include <iostream>
#include <windows.h>
using std::cout;

MazeGeneratorDig::MazeGeneratorDig() :
	MazeGeneratorBase("穴掘り法")
{
}

MazeGeneratorDig::~MazeGeneratorDig()
{
}
//壁伸ばし法のやりかた
bool MazeGeneratorDig::Init()
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

	//指定サイズで生成、外壁部分を一度床に、その他を全て壁にする ※外壁部分は最後に壁にする
	map_ = vector<vector<int>>(height_, vector<int>(width_, MAP_WALL));
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			if (h == 0 || w == 0 || h == height_ - 1 || w == width_ - 1) {
				map_[h][w] = MAP_FLOOR;
			}
		}
	}

	Output();
	return true;
}

bool MazeGeneratorDig::Create()
{
	//ランダムな奇数座標を開始座標とする
	//掘り進める方向(1マス先が床、)
	//候補座標から１つ選び、それを消去
	//選んだ座標が床であれば、現在拡張中の壁配列をクリアし、拡張を行う

	//迷路全体を構成する2次元配列を、幅高さ5以上の奇数で生成します。
	//迷路の外周を通路とし、それ以外を壁とします。
	//	x, yともに奇数となる座標(任意)を穴掘り開始座標とします。
	//	穴掘りを開始します。
	//	指定座標を通路とします。
	//	次に掘り進める方向(1セル先が通路かつ2セル先が壁の方向)をランダムで決定し、2セル先まで通路とします。掘り進められなくなるまで繰り返します。
	//	掘り進めた結果四方のどこにも進めなくなった場合、すでに通路となった座標(x, yともに奇数)をランダムに取得し、4.の穴掘り処理を再帰的に呼び出します。
	//	外周を壁に戻します。

	//初期採掘地点の設定（奇数）
	//指定幅の半分(端数切捨)未満の乱数を２倍し、1を足す
	//ex:幅15の場合:配列0-14から奇数1,3,..,11,13 →2n+1(0~6)を求める
	//   幅15は外部から貰うため、rand() % (15/2) で0~6の乱数が出る
	POINT startPoint;
	startPoint.x = rand() % (width_ / 2) * 2 + 1;
	startPoint.y = rand() % (height_ / 2) * 2 + 1;

	Dig(startPoint);

	//外壁を建造
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

void MazeGeneratorDig::Dig(POINT pts)
{
	while (true) {
		//掘れる方向決め 採掘可能方向0でbreak
		vector<DIRECTION> dirList;
		for (DIRECTION d = static_cast<DIRECTION>(0); d < DIR_MAX; d = static_cast<DIRECTION>(d + 1)) {
			POINT dirPts, tgtPtr;
			StoreDirectionValue(&dirPts, d);
			tgtPtr = pts + dirPts;
			if (IsWall(tgtPtr) && IsWall(tgtPtr + dirPts)) {
				dirList.push_back(d);
			}
		}
		if (dirList.size() == 0)break;

		//採掘可能方向のうちランダム方向に伸ばす
		//自位置を床にし、開始座標リストに追加
		SetFloor(pts);
		//方向を決め、２マス先まで床にする　２マス先の偶数座標は開始座標リストに追加
		DIRECTION dir = dirList[rand() % dirList.size()];
		POINT dirPts;
		StoreDirectionValue(&dirPts, dir);
		POINT nextPts = pts + dirPts + dirPts;
		SetFloor(nextPts);
		SetFloor(nextPts - dirPts);
		pts = nextPts;
	}

	Output();

	//掘り進められなかった場合、開始座標リスト内のランダム座標から掘る
	//開始座標リストが0になったら終了
	POINT reDigPts;
	if (StoreStartPoint(&reDigPts)) {
		Dig(reDigPts);
	}
}

void MazeGeneratorDig::StoreDirectionValue(POINT* pts, DIRECTION dir)
{
	switch (dir)
	{
	case MazeGeneratorDig::DIR_LEFT:
		pts->x = -1;
		pts->y = 0;
		break;
	case MazeGeneratorDig::DIR_RIGHT:
		pts->x = 1;
		pts->y = 0;
		break;
	case MazeGeneratorDig::DIR_DOWN:
		pts->x = 0;
		pts->y = 1;
		break;
	case MazeGeneratorDig::DIR_UP:
		pts->x = 0;
		pts->y = -1;
		break;
	default:
		pts->x = 0;
		pts->y = 0;
		break;
	}
}

void MazeGeneratorDig::SetFloor(POINT pts)
{
	map_[pts.y][pts.x] = MAP_FLOOR;
	if (IsOdd(pts)) {
		startPointList.push_back(pts);
	}
}

bool MazeGeneratorDig::StoreStartPoint(POINT* nextSPts)
{
	if (startPointList.size() > 0) {
		int index = rand() % startPointList.size();
		*nextSPts = startPointList[index];
		startPointList.erase(startPointList.begin() + index);
		return true;
	}
	return false;
}

bool MazeGeneratorDig::IsWall(POINT pts)
{
	return (map_[pts.y][pts.x] == MAP_WALL);
}
