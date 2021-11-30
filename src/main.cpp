#include <iostream>
#include "graphe.h"

using namespace std;

int main(){

    //Graphe g;

    //Lecture de notre fichier graphe et affichage de celle-ci
    //g.lireFichier("Graphe.txt");
    Graphe g("Graphe.txt");
    g.affichage();

    // On check si les voisins marchent
    g.voisins(25);

    return 0;
}
