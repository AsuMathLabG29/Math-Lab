#include <iostream>
#include "CMatrix.h"
#include <fstream>
using namespace std;

int main(int argv, char* argc[])
{
    ifstream source;
    string line;

    source.open(argc[1]);
    if(!source.bad() && source.is_open() && argv >= 2){
        while(getline(source,line)){
            istringstream iss(line);
            cout << line << '\n';
        }
        source.close();
    }
    return 0;
}
