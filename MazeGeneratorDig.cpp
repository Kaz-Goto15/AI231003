#include "MazeGeneratorDig.h"
#include <iostream>
#include <windows.h>
using std::cout;

MazeGeneratorDig::MazeGeneratorDig() :
	MazeGeneratorBase("���@��@")
{
}

MazeGeneratorDig::~MazeGeneratorDig()
{
}
//�ǐL�΂��@�̂�肩��
bool MazeGeneratorDig::Init()
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

	//�w��T�C�Y�Ő����A�O�Ǖ�������x���ɁA���̑���S�ĕǂɂ��� ���O�Ǖ����͍Ō�ɕǂɂ���
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
	//�����_���Ȋ���W���J�n���W�Ƃ���
	//�@��i�߂����(1�}�X�悪���A)
	//�����W����P�I�сA���������
	//�I�񂾍��W�����ł���΁A���݊g�����̕ǔz����N���A���A�g�����s��

	//���H�S�̂��\������2�����z����A������5�ȏ�̊�Ő������܂��B
	//���H�̊O����ʘH�Ƃ��A����ȊO��ǂƂ��܂��B
	//	x, y�Ƃ��Ɋ�ƂȂ���W(�C��)�����@��J�n���W�Ƃ��܂��B
	//	���@����J�n���܂��B
	//	�w����W��ʘH�Ƃ��܂��B
	//	���Ɍ@��i�߂����(1�Z���悪�ʘH����2�Z���悪�ǂ̕���)�������_���Ō��肵�A2�Z����܂ŒʘH�Ƃ��܂��B�@��i�߂��Ȃ��Ȃ�܂ŌJ��Ԃ��܂��B
	//	�@��i�߂����ʎl���̂ǂ��ɂ��i�߂Ȃ��Ȃ����ꍇ�A���łɒʘH�ƂȂ������W(x, y�Ƃ��Ɋ)�������_���Ɏ擾���A4.�̌��@�菈�����ċA�I�ɌĂяo���܂��B
	//	�O����ǂɖ߂��܂��B

	//�����̌@�n�_�̐ݒ�i��j
	//�w�蕝�̔���(�[���؎�)�����̗������Q�{���A1�𑫂�
	//ex:��15�̏ꍇ:�z��0-14����1,3,..,11,13 ��2n+1(0~6)�����߂�
	//   ��15�͊O������Ⴄ���߁Arand() % (15/2) ��0~6�̗������o��
	POINT startPoint;
	startPoint.x = rand() % (width_ / 2) * 2 + 1;
	startPoint.y = rand() % (height_ / 2) * 2 + 1;

	Dig(startPoint);

	//�O�ǂ�����
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
		//�@���������� �̌@�\����0��break
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

		//�̌@�\�����̂��������_�������ɐL�΂�
		//���ʒu�����ɂ��A�J�n���W���X�g�ɒǉ�
		SetFloor(pts);
		//���������߁A�Q�}�X��܂ŏ��ɂ���@�Q�}�X��̋������W�͊J�n���W���X�g�ɒǉ�
		DIRECTION dir = dirList[rand() % dirList.size()];
		POINT dirPts;
		StoreDirectionValue(&dirPts, dir);
		POINT nextPts = pts + dirPts + dirPts;
		SetFloor(nextPts);
		SetFloor(nextPts - dirPts);
		pts = nextPts;
	}

	Output();

	//�@��i�߂��Ȃ������ꍇ�A�J�n���W���X�g���̃����_�����W����@��
	//�J�n���W���X�g��0�ɂȂ�����I��
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
