#include "MazeGeneratorBar.h"
#include <iostream>

#include <windows.h>
using std::cout;

MazeGeneratorBar::MazeGeneratorBar():
	MazeGeneratorBase("–_“|‚µ–@")
{
}

MazeGeneratorBar::~MazeGeneratorBar()
{
}
//–_“|‚µ–@‚Ì‚â‚è‚©‚½
bool MazeGeneratorBar::Init()
{
	//–À˜H‚Ì‘å‚«‚³‚ª“K‚µ‚Ä‚¢‚é‚©
	if (width_ < MIN_LENGTH) {
		cout << "Žw’è‚³‚ê‚½‰¡•‚Ì’l‚ª¬‚³‚·‚¬‚Ü‚·B¶¬‰Â”\‚ÈÅ’á’l‚É’uŠ·‚µ‚Ü‚·B\n";
		width_ = MIN_LENGTH;
	}
	if (height_ < MIN_LENGTH) {
		cout << "Žw’è‚³‚ê‚½c•‚Ì’l‚ª¬‚³‚·‚¬‚Ü‚·B¶¬‰Â”\‚ÈÅ’á’l‚É’uŠ·‚µ‚Ü‚·B\n";
		height_ = MIN_LENGTH;
	}
	if (IsEven(width_)) {
		cout << "‰¡•‚ª‹ô”‚Å‚·BŽw’è’l‚É1‚ð‰Á‚¦Šï”‚É‚µ‚Ü‚·B\n";
		width_++;
	}
	if (IsEven(height_)) {
		cout << "c•‚ª‹ô”‚Å‚·BŽw’è’l‚É1‚ð‰Á‚¦Šï”‚É‚µ‚Ü‚·B\n";
		height_++;
	}

	//Žw’èƒTƒCƒY‚Å¶¬AŠOŽü‚ð•Ç‚É
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
	//–À˜H‘S‘Ì‚ð\¬‚·‚é2ŽŸŒ³”z—ñ‚ðA•‚‚³5ˆÈã‚ÌŠï”‚Å¶¬
	//–À˜H‚ÌŠOŽü‚ð•ÇA‚»‚êˆÈŠO‚ð’Ê˜H‚Æ‚·‚é
	//ŠOŽü‚Ì“à‘¤‚ÉŠî€‚Æ‚È‚é•Ç(–_)‚ð1ƒZƒ‹‚¨‚«(x,y‚Æ‚à‚É‹ô”‚ÌÀ•W)‚É”z’u
	//“à‘¤‚Ì•Ç(–_)‚ð‘–¸‚µAƒ‰ƒ“ƒ_ƒ€‚È•ûŒü‚É“|‚µ‚Ä•Ç‚Æ‚·‚é‚ªAˆÈ‰º‚É“–‚Ä‚Í‚Ü‚é•ûŒü‚É‚Í“|‚µ‚Ä‚Í‚¢‚¯‚È‚¢B
	//  1s–Ú‚Ì“à‘¤‚Ì•ÇˆÈŠO‚Å‚Íã•ûŒü‚É“|‚µ‚Ä‚Í‚¢‚¯‚È‚¢B
	//  ‚·‚Å‚É–_‚ª“|‚³‚ê•Ç‚É‚È‚Á‚Ä‚¢‚éê‡A‚»‚Ì•ûŒü‚É‚Í“|‚µ‚Ä‚Í‚¢‚¯‚È‚¢B
	//ƒ‰ƒ“ƒ_ƒ€’l(0123 or 012)‚ðŒˆ‚ß
	srand((unsigned int)time(nullptr));
	for (int y = 1; y < height_ -1; y ++) {
		for (int x = 1; x < width_ -1; x ++) {
			if (IsEven(y) && IsEven(x)) {
				cout << "Now: (" << x << "," << y << ")\n";
				Sleep(500);

				map_[y][x] = MAP_WALL;

				while (true) {
					int dir = rand();
					//•ûŒüŒˆ‚ß@1s–Ú‚Ì‚Ýã‚à
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
					// •Ç‚Å‚È‚¯‚ê‚Î“|‚µ”²‚¯‚é
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
	//2‚¸‚Ây,x‚É–_—§‚Ä”»’è
	/*
	//–_‚ð—§‚Ä“|‚·
			var rnd = new Random();
	for (int x = 2; x < width - 1; x += 2)
			{
				for (int y = 2; y < height - 1; y += 2)
				{
					maze[x, y] = Wall; // –_‚ð—§‚Ä‚é

					// “|‚¹‚é‚Ü‚ÅŒJ‚è•Ô‚·
					while (true){
						// 1s–Ú‚Ì‚Ýã‚É“|‚¹‚é
						int direction;
						if (y == 2)
							direction = rnd.Next(4);
						else
							direction = rnd.Next(3);

						// –_‚ð“|‚·•ûŒü‚ðŒˆ‚ß‚é
						int wallX = x;
						int wallY = y;
						switch (direction)
						{
							case 0: // ‰E
								wallX++;
								break;
							case 1: // ‰º
								wallY++;
								break;
							case 2: // ¶
								wallX--;
								break;
							case 3: // ã
								wallY--;
								break;
						}
						// •Ç‚¶‚á‚È‚¢ê‡‚Ì‚Ý“|‚µ‚ÄI—¹
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

