#include <iostream>
#include "graphe.h"

using namespace std;

int main(){
    Graphe g;
    g.lireFichier("Graphe.txt");
    g.affichage();
    g.existeEst(5);

    return 0;
}
