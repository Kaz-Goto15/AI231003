#include "MazeGeneratorBar.h"
#include <iostream>
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
	if (width_ % 2 == 0) {
		cout << "‰¡•‚ª‹ô”‚Å‚·BŽw’è’l‚É1‚ð‰Á‚¦Šï”‚É‚µ‚Ü‚·B\n";
		width_++;
	}
	if (height_ % 2 == 0) {
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
    //ƒ‰ƒ“ƒ_ƒ€’l(0123 or 012)‚ðŒˆ‚ß

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

