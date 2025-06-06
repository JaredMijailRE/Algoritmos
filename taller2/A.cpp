// https://vjudge.net/contest/721278#problem/A

// Sorce: https://github.com/JaredMijailRE/Algoritmos/blob/main/taller2/A.cpp


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <tuple>
using namespace std;

// definimos el tipo matrix
using Matrix = vector<vector<char>>;
using u16 = uint_fast16_t;
using point = tuple<u16, u16>;


Matrix getLabyrinth(point *inicio, point *meta){
    u16 height, width;
    point& inicioPunto = *inicio;
    point& metaPunto = *meta;
    cin >> height >> width;
    cin.ignore();
    
    Matrix labyrinth;
    getchar(); // consumimos el salto de linea
    string row;
    for (u16 i = 0; i < height; i++) {
        getline(cin, row);
        labyrinth.push_back(vector<char>(row.begin(), row.end()));
        u16 posInicio = row.find("A");
        u16 posMeta = row.find("B");

        if(posInicio != -1){
            inicioPunto = {i, posInicio};
        }

        if(posMeta != -1){
            metaPunto = {i, posMeta};
        }
    }

    return labyrinth;
}

void solveLabyrinth(point inicio, point meta, Matrix labyrith){

    

}

int main() {
    point inicio, meta;

    Matrix laberinto = getLabyrinth(&inicio, &meta);


    
    return 0;
}