#include "MazeGeneratorBar.h"
#include <iostream>
using std::cout;
MazeGeneratorBar::MazeGeneratorBar():
	MazeGeneratorBase("�_�|���@")
{
}

MazeGeneratorBar::~MazeGeneratorBar()
{
}
//�_�|���@�̂�肩��
void MazeGeneratorBar::Generate(int x, int y)
{
	width_ = x;
	height_ = y;
	//���H�̑傫�����K���Ă��邩
	if (x < MIN_LENGTH) {
		cout << "�w�肳�ꂽ�����̒l�����������܂��B�����\�ȍŒ�l�ɒu�����܂��B\n";
		x = MIN_LENGTH;
	}
	if (y < MIN_LENGTH) {
		cout << "�w�肳�ꂽ�c���̒l�����������܂��B�����\�ȍŒ�l�ɒu�����܂��B\n";
		y = MIN_LENGTH;
	}
	if (x % 2 == 0) {
		cout << "�����������ł��B�w��l��1��������ɂ��܂��B\n";
		x++;
	}
	if (y % 2 == 0) {
		cout << "�c���������ł��B�w��l��1��������ɂ��܂��B\n";
		y++;
	}

	//�w��T�C�Y�Ő����A�O����ǂ�
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

