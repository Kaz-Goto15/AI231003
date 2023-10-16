#include "MazeGeneratorExtend.h"
#include <iostream>
#include <windows.h>
using std::cout;

MazeGeneratorExtend::MazeGeneratorExtend() :
	MazeGeneratorBase("�ǐL�΂��@")
{
}

MazeGeneratorExtend::~MazeGeneratorExtend()
{
}
//�ǐL�΂��@�̂�肩��
bool MazeGeneratorExtend::Init()
{
	srand((unsigned int)time(nullptr));

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

	//�������W���J�n���W���X�g�ɒǉ�
	for (int y = 1; y < height_ - 1; y++) {
		for (int x = 1; x < width_ - 1; x++) {
			if (IsEven(y) && IsEven(x)) {
				startPointList.push_back({ x,y });
			}
		}
	}

	Output();
	return true;
}

bool MazeGeneratorExtend::Update()
{
	//���H�S�̂��\������2�����z����A������5�ȏ�̊�Ő���
	//���H�̊O����ǁA����ȊO��ʘH�Ƃ���
	//x, y�Ƃ��ɋ����ƂȂ���W��ǐL�΂��J�n���W(���)�Ƃ��ă��X�g�A�b�v
	// 
	//�ǐL�΂��J�n���W���烉���_���ō��W�����o���A�ʘH�̏ꍇ�̂ݕǐL�΂��������s��
	// �����ׂĂ̌����W���ǂɂȂ�܂ŌJ��Ԃ�
	//�ǐL�΂������F
	//	�w����W��ǂƂ���
	//	���Ɍ@��i�߂����(�ׂ̃Z�����ʘH�̕�������2�Z���悪���݊g�����̕ǂł͂Ȃ�����)�������_���Ō���
	//	�g���������2�Z���悪�ǂ̏ꍇ(�����̕ǂɐڑ����ꂽ�ꍇ)�A�ǂ̊g�����I��
	//	�ʘH�̏ꍇ�A���̃Z�����瑱���Ċg��(5. �̏������ċA�I�ɌĂяo���B)
	//	�l�������ׂČ��݊g�����̕ǂ̏ꍇ�A�g���ł�����W��������܂ŁA���݊g�����̕ǂ��o�b�N���āA�ǂ̊g�����ĊJ����
	//���ׂĂ̌����W����(�g����)�ɂȂ�Ί���
	while (startPointList.size() > 0){
		int pts = rand() % startPointList.size();
		POINT point = startPointList[pts];
		startPointList.erase(startPointList.begin() + pts);
		
		if (map_[point.y][point.x] == MAP_FLOOR) {
			currentWallPoint.clear();
			ExtendWall(point);
		}
	}
	for (int y = 1; y < height_ - 1; y++) {
		for (int x = 1; x < width_ - 1; x++) {
			if (IsEven(y) && IsEven(x)) {
				map_[y][x] = MAP_WALL;

				while (true) {
					int dir = rand();
					//�������߁@1�s�ڂ̂ݏ��
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
					// �ǂłȂ���Γ|��������
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

//���W����Ǌg��
void MazeGeneratorExtend::ExtendWall(POINT pts)
{
	//static const int[4];
	//�L�΂����������
	vector<DIRECTION> dirList;
	for (DIRECTION d = DIR_LEFT; d < DIR_MAX; d = static_cast<DIRECTION>(d + 1)){
		POINT dirPts;
		StoreDirectionValue(&dirPts, d);
		if (IsDirCanExtend(pts, dirPts)) {
			dirList.push_back(d);
		}
	}

	//�����_���ɐL�΂�
	if (dirList.size() > 0) {
		//���ʒu��ǂ�
		map_[pts.y][pts.x] = MAP_WALL;
		DIRECTION dir = dirList[rand() % dirList.size()];
		//2�}�X�悪���̏ꍇ�̂ݑ�����
		bool isFloor;
		POINT dirPts;
		StoreDirectionValue(&dirPts, dir);
		isFloor = (map_[pts.y + dirPts.y * 2][pts.x + dirPts.x * 2] == MAP_FLOOR);
		map_[--pts.y + dirPts.y*2][--pts.x + dirPts.x*2] = MAP_WALL;
		map_[--pts.y + dirPts.y * 2][--pts.x + dirPts.x * 2] = MAP_WALL;
		if (isFloor)ExtendWall(pts);
	}
	else {
		// ���ׂČ��݊g�����̕ǂɂԂ���ꍇ�A�o�b�N���čĊJ
		//var beforeCell = CurrentWallCells.Pop();
		//ExtendWall(beforeCell.X, beforeCell.Y);
	}
}

bool MazeGeneratorExtend::IsDirCanExtend(POINT pts, POINT ValueOnDir)
{
	return (map_[pts.y + ValueOnDir.y][pts.x + ValueOnDir.x] == MAP_FLOOR &&
		IsCurrentWall(map_[pts.y + ValueOnDir.y * 2][pts.x + ValueOnDir.x * 2]));
}

bool MazeGeneratorExtend::IsCurrentWall(int currentPtsAttribute)
{
	return false;
}

void MazeGeneratorExtend::StoreDirectionValue(POINT* pts, DIRECTION dir)
{
	switch (dir)
	{
	case MazeGeneratorExtend::DIR_LEFT:
		pts->x = -1;
		pts->y = 0;
	case MazeGeneratorExtend::DIR_RIGHT:
		pts->x = 1;
		pts->y = 0;
	case MazeGeneratorExtend::DIR_DOWN:
		pts->x = 0;
		pts->y = 1;
	case MazeGeneratorExtend::DIR_UP:
		pts->x = 0;
		pts->y = -1;
	default:
		pts->x = 0;
		pts->y = 0;
	}
}
