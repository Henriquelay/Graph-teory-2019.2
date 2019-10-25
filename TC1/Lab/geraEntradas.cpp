#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

#define MINVERT 3
#define MAXVERT 200

int main(int argc, char* argv[]) {
    unsigned int nArestas, nGrafos = stoi(argv[1]), nVertices;
    ofstream outfile;

    unsigned int A, B;
    unsigned int C, R, E;

    outfile.open("input_gen.txt", ios::out);

    srand(time(0));
    for(unsigned int i = 0; i < nGrafos; i++) {
        nVertices = (unsigned int) (rand() % MAXVERT) + MINVERT;
        nArestas = (unsigned int) rand() % (((nVertices)-1) / 2);
        outfile << nVertices << ' ' << nArestas << endl;
        for(int unsigned m = 0; m < nArestas; m++) {
            A = (unsigned int) (rand() % (nVertices-1)) + 1;
            do {
                B = (unsigned int) (rand() % (nVertices-1)) + 1;
            } while (A == B);
            outfile << A << ' ' << B << endl;
        }
        C = (unsigned int) (rand() % (nVertices-1)) + 1;
        do {
            R = (unsigned int) (rand() % (nVertices-1)) + 1;
        } while(C == R);
        do {
            E = (unsigned int) (rand() % (nVertices-1)) + 1;
        } while(E == R || E == C);

        outfile << C << ' ' << R << ' ' << E;
        
        if(!i == nGrafos) outfile << '\n'; 
    }
    outfile.close();
}