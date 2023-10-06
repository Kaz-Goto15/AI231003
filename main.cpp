#include "MazeGeneratorBar.h"
#include "MazeGeneratorBase.h";
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
//���H�T�C�Y
static const int sizeX = 41;
static const int sizeY = 21;

int main()
{
	vector<MazeGeneratorBase*> mazeModelList;
	mazeModelList.push_back(new MazeGeneratorBar());
	//mazeModelList.push_back(new MazeGeneratorExtend());
	//mazeModelList.push_back(new MazeGeneratorDig())
	int x, y;
	cout << "���H�̏c������́F";
	cin >> y;
	cout << "���H�̉�������́F";
	cin >> x;
	cout << "���H�̐������@��I���i";
	for (int i = 0; i < mazeModelList.size(); i++) {
		cout << i << ": " << mazeModelList[i]->GetModelName();
	}
	cout << ")\n";
	int type;
	cin >> type;
	//���H����
	mazeModelList[type]->Generate(x,y);
	
	//���f�����X�g�̊J��
	vector<MazeGeneratorBase*> ::iterator it = mazeModelList.begin();
	while (it != mazeModelList.end()) {
		delete (*it);
		++it;
	}
}