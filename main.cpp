#include "MazeGeneratorBar.h"
#include "MazeGeneratorBase.h";
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
//ñ¿òHÉTÉCÉY
const int sizeX = 41;
const int sizeY = 21;

int main()
{
    vector<MazeGeneratorBase>* mg;
    mg->push_back(new MazeGeneratorBar());
    int x, y;
    cout << "ñ¿òHÇÃècïùÇì¸óÕÅF";
    cin >> y;
    cout << "ñ¿òHÇÃâ°ïùÇì¸óÕÅF";
    cin >> x;
    cout << "ñ¿òHÇÃê∂ê¨ï˚ñ@ÇëIëÅi";
    for (int i = 0; i < mg->size(); i++) {
        cout << i << ": " << mg.modelName;
    }
    int type;
    cin >> type;
    //ñ¿òHê∂ê¨
    
}

//