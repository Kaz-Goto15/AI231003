#include "MazeGeneratorBar.h"
#include <iostream>

#include <windows.h>
using std::cout;

MazeGeneratorBar::MazeGeneratorBar():
	MazeGeneratorBase("�_�|���@")
{
}

MazeGeneratorBar::~MazeGeneratorBar()
{
}
//�_�|���@�̂�肩��
bool MazeGeneratorBar::Init()
{
	//���H�̑傫�����K���Ă��邩
	if (width_ < MIN_LENGTH) {
		cout << "�w�肳�ꂽ�����̒l�����������܂��B�����\�ȍŒ�l�ɒu�����܂��B\n";
		width_ = MIN_LENGTH;
	}
	if (height_ < MIN_LENGTH) {
		cout << "�w�肳�ꂽ�c���̒l�����������܂��B�����\�ȍŒ�l�ɒu�����܂��B\n";
		height_ = MIN_LENGTH;
	}
	if (IsEven(width_)) {
		cout << "�����������ł��B�w��l��1��������ɂ��܂��B\n";
		width_++;
	}
	if (IsEven(height_)) {
		cout << "�c���������ł��B�w��l��1��������ɂ��܂��B\n";
		height_++;
	}

	//�w��T�C�Y�Ő����A�O����ǂ�
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
	//
	//���H�S�̂��\������2�����z����A������5�ȏ�̊�Ő���
	//���H�̊O����ǁA����ȊO��ʘH�Ƃ���
	//�O���̓����Ɋ�ƂȂ��(�_)��1�Z������(x,y�Ƃ��ɋ����̍��W)�ɔz�u
	//�����̕�(�_)�𑖍����A�����_���ȕ����ɓ|���ĕǂƂ��邪�A�ȉ��ɓ��Ă͂܂�����ɂ͓|���Ă͂����Ȃ��B
	//  1�s�ڂ̓����̕ǈȊO�ł͏�����ɓ|���Ă͂����Ȃ��B
	//  ���łɖ_���|����ǂɂȂ��Ă���ꍇ�A���̕����ɂ͓|���Ă͂����Ȃ��B
	//�����_���l(0123 or 012)������
	srand((unsigned int)time(nullptr));
	for (int y = 1; y < height_ -1; y ++) {
		for (int x = 1; x < width_ -1; x ++) {
			if (IsEven(y) && IsEven(x)) {
				cout << "Now: (" << x << "," << y << ")\n";
				Sleep(500);

				map_[y][x] = MAP_WALL;

				while (true) {
					int dir = rand();
					//�������߁@1�s�ڂ̂ݏ��
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
					cout << "Tgt: (" << target.x << "," << target.y << ")\n";
					// �ǂłȂ���Γ|��������
					if (map_[target.y][target.x] != MAP_WALL){
						map_[target.y][target.x] = MAP_WALL;
						break;
					}
				}
			}
			Output();
		}
	}
	isFinished = true;
	//2����y,x�ɖ_���Ĕ���
	/*
	//�_�𗧂ē|��
			var rnd = new Random();
	for (int x = 2; x < width - 1; x += 2)
			{
				for (int y = 2; y < height - 1; y += 2)
				{
					maze[x, y] = Wall; // �_�𗧂Ă�

					// �|����܂ŌJ��Ԃ�
					while (true){
						// 1�s�ڂ̂ݏ�ɓ|����
						int direction;
						if (y == 2)
							direction = rnd.Next(4);
						else
							direction = rnd.Next(3);

						// �_��|�����������߂�
						int wallX = x;
						int wallY = y;
						switch (direction)
						{
							case 0: // �E
								wallX++;
								break;
							case 1: // ��
								wallY++;
								break;
							case 2: // ��
								wallX--;
								break;
							case 3: // ��
								wallY--;
								break;
						}
						// �ǂ���Ȃ��ꍇ�̂ݓ|���ďI��
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

