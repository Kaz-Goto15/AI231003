#include "MazeGeneratorBar.h"
#include "MazeGeneratorBase.h";
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
//���H�T�C�Y
const int sizeX = 41;
const int sizeY = 21;

int main()
{
    vector<MazeGeneratorBase>* mg;
    mg->push_back(new MazeGeneratorBar());
    int x, y;
    cout << "���H�̏c������́F";
    cin >> y;
    cout << "���H�̉�������́F";
    cin >> x;
    cout << "���H�̐������@��I���i";
    for (int i = 0; i < mg->size(); i++) {
        cout << i << ": " << mg.modelName;
    }
    int type;
    cin >> type;
    //���H����
    
}

//