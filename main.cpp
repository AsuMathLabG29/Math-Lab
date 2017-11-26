// main.cpp

#include <iostream>
#include "sstream"
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "CMatrix.h"

using namespace std;


vector<CMatrix> matrixVec;
vector<char> matrixOp;

string int_to_string(int x){

    std::ostringstream stream;
    stream << x;
    return stream.str();
}

string checkMatrix(char name){

    for (int i = 0; i < matrixVec.size(); i++) {
        if (matrixVec[i].getName() == name)
            return int_to_string(i);
    }

    return "";
}


int main(int argc, char *argv[])
{
//    string matStr = "A = [1.4 2.2 3.2; 4.4 5.4 6.4; 3.3 4.2 2.2]";
//    CMatrix A(matStr);

//    C = A + B
//    D = A - B

//    argv[1] = "/home/abyss/Workspace/CLionProjects/Math Lab/example.m";
    ifstream testFile(argv[1]);

    string str;
    char op = 'o';
    double num = 0.0;
    while (getline(testFile, str)){
        for (int i = 0; i < str.length(); i++){
            switch (str[i]){

                case '+':
                    op = '+';
                    break;
                case '-':
                    op = '-';
                    break;
                case '*':
                    if (str[i - 1] == '.'){

                        op = 'm';
                    }
                    else{
                        op = '*';
                    }
                    break;
                case '/':
                    if (str[i - 1] == '.'){
                        op = 'd';
                    }
                    else{
                        op = '/';
                    }
                    break;
                case '\'':
                    op = '\'';
                    break;
                case '.':
                    num= stod(str.substr(str.find('=')+1,(str.length() - str.find('/'))-1));

                    break;

                case ' ':
                    break;
                case '\r':
                    break;
                case '=':
                    op = '=';
                    break;
                case '[':
                    matrixVec.push_back(CMatrix(str.substr(str.find('['),str.length())));
                    op = 'o';
                    break;
                default:
//                    string matIndex = checkMatrix(str[i]);

                    matrixOp.push_back(str[i]);
//                    if (matIndex.empty()){
////                        matrixOp.push_back(matrixVec[atoi(matIndex.c_str())]);
//                        matrixVec.push_back(CMatrix(str[i]));
//                    }
//                    else {
////                        matrixOp.push_back(CMatrix(str[i]));
//                    }

                    break;
            }

            if (str[i] == '['){
                break;
            }

        }

        if (op != 'o'){

            CMatrix A = matrixVec[0];
            CMatrix B = matrixVec[1];
            CMatrix C = CMatrix(matrixOp[0]);

            char name = 'a';

            switch (op){

                case '+':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = A + B;
                    C.setName(name);
                    cout << C;
                    break;
                case '-':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = A - B;
                    C.setName(name);
                    cout << C;
                    break;
                case '*':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = A * B;
                    C.setName(name);
                    cout << C;
                    break;
                case '/':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = A / B;
                    C.setName(name);
                    cout << C;
                    break;
                case '\'':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = A.getTranspose();
                    C.setName(name);
                    cout << C;
                    break;
                case 'm':

                    break;
                case 'd':
                    name = C.getName();
                    cout << name << " = " << endl;
                    C = num / A;
                    C.setName(name);
                    cout << C;
                    break;
            }

            string matIndex = checkMatrix(C.getName());

            if (matIndex.empty()){
                matrixVec.push_back(C);
            }
            else {
                matrixVec[atoi(matIndex.c_str())] = C;
            }


        }


        op = 'o';
        matrixOp.clear();

    }
    return 0;
}
