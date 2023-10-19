#include "MazeGeneratorBase.h"
#include <iostream>
#include <sstream>
#include <windows.h>

using std::cout;
using std::cin;
using std::string;

MazeGeneratorBase::MazeGeneratorBase(std::string modelName):
	modelName_(modelName),
	width_(-1),height_(-1)
{
}

MazeGeneratorBase::~MazeGeneratorBase()
{
}

void MazeGeneratorBase::Generate(int x, int y)
{
	width_ = x;
	height_ = y;
	Init();
	Create();
	CheckSave();
}

void MazeGeneratorBase::Output()
{
	//std::system("cls");
	std::stringstream ss;
	for (int h = 0; h < height_; h++) {
		for (int w = 0; w < width_; w++) {
			ss << outStr[map_[h][w]];
		}
		std::cout << ss.str() << std::endl;
		ss.str("");
	}
	std::cout << std::endl;
}

void MazeGeneratorBase::CheckSave()
{

	std::cout << "今回の結果をCSV形式で保存しますか？(Y/n)\n";
	char cmdSave;
	while (true) {
		cin >> cmdSave;
		if (cmdSave == 'Y' || cmdSave == 'n')break;
	}
	if (cmdSave == 'Y') {
		SaveFile();
	}
}

bool MazeGeneratorBase::SaveFile()
{
	const char* defaultExt = "csv";
	char fileName[MAX_PATH];
	sprintf_s(fileName, MAX_PATH, "無題.%s", defaultExt);

	//dialog setting
	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.lpstrFilter = "マップデータ(*.csv)\0*.csv\0すべてのファイル(*.*)\0*.*\0\0";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = defaultExt;

	//「ファイルを保存」ダイアログ
	BOOL selFile = GetSaveFileNameA(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return false;

	//ファイルを開く
	HANDLE hFile;
	hFile = CreateFileA(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBoxA(NULL, (("CANNOT OPEN FILE: " + (string)fileName)).c_str(), "Error", MB_OK);
		return false;
	}

	//データ書込
	std::string writeData;
	for (int h = 0; h < height_; h++) {
		std::stringstream ss;
		for (int w = 0; w < width_; w++) {
			ss << map_[h][w];
			if (w != width_ - 1)ss << ",";
		}
		ss << "\r\n";
		writeData += ss.str();
	}
	writeData += "\0";

	DWORD dwBytes = 0;
	BOOL res = WriteFile(hFile, writeData.c_str(), (DWORD)strlen(writeData.c_str()), &dwBytes, NULL);

	if (res == FALSE) {
		MessageBoxA(NULL, (("FAILED TO WRITE: " + (string)fileName)).c_str(), "Error", MB_OK);
		return false;
	}

	//ファイルを閉じる
	CloseHandle(hFile);

}
