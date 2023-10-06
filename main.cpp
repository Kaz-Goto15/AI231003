#include "MazeGeneratorBar.h"
#include "MazeGeneratorBase.h";
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
//迷路サイズ
static const int sizeX = 41;
static const int sizeY = 21;

int main()
{
	vector<MazeGeneratorBase*> mazeModelList;
	mazeModelList.push_back(new MazeGeneratorBar());
	//mazeModelList.push_back(new MazeGeneratorExtend());
	//mazeModelList.push_back(new MazeGeneratorDig())
	int x, y;
	cout << "迷路の縦幅を入力：";
	cin >> y;
	cout << "迷路の横幅を入力：";
	cin >> x;
	cout << "迷路の生成方法を選択（";
	for (int i = 0; i < mazeModelList.size(); i++) {
		cout << i << ": " << mazeModelList[i]->GetModelName();
	}
	cout << ")\n";
	int type;
	cin >> type;
	//迷路生成
	mazeModelList[type]->Generate(x,y);
	
	//モデルリストの開放
	vector<MazeGeneratorBase*> ::iterator it = mazeModelList.begin();
	while (it != mazeModelList.end()) {
		delete (*it);
		++it;
	}
}