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

void MazeGeneratorExtend::ExtendWall(POINT pts)
{
	//static const int[4];
	vector<DIRECTION> dir;
	for (DIRECTION dir = DIR_LEFT; dir < DIR_MAX; dir = static_cast(DIRECTION++)) {
		if(IsDirCanExtend(pts, GetValueOnDirection(DIRECT))
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

POINT MazeGeneratorExtend::GetValueOnDirection(DIRECTION dir)
{
	switch (dir)
	{
	case MazeGeneratorExtend::DIR_LEFT:
		return {-1,0}
	case MazeGeneratorExtend::DIR_RIGHT:
		return { 1,0 };
	case MazeGeneratorExtend::DIR_DOWN:
		return { 0,1 };
	case MazeGeneratorExtend::DIR_UP:
		return { 0,-1 };
	default:
		return { 0,0 };
	}
}
