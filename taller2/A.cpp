// https://vjudge.net/contest/721278#problem/A

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/A.cpp


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <cstdio>
#include <string>
using namespace std;

// definimos el tipo matrix
using Matrix = vector<vector<char>>;
using u16 = uint_fast16_t;


Matrix getLabyrinth(){
    u16 height, width;
    cin >> height >> width;
    cin.ignore();
    
    Matrix labyrinth;
    getchar(); // consumimos el salto de linea
    string row;
    for (u16 i = 0; i < height; i++) {
        getline(cin, row);
        labyrinth.push_back(vector<char>(row.begin(), row.end()));
    }

    return labyrinth;
}

int main() {

    Matrix laberinto = getLabyrinth();

    
    return 0;
}