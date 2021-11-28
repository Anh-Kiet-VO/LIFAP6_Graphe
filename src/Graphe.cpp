#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include "graphe.h"

using namespace std;

Graphe::Graphe() {

}

Graphe::Graphe(const int lignes, const int colonnes) {
    L = lignes;
    C = colonnes;

    grille.resize(L * C);
    tabRoute.resize(L * C);

    for(int cece = 0; cece < lignes * colonnes; cece++) {
        grille[cece].altitude = -1;
    }
}

Graphe::Graphe(const Graphe &g) {
    L = g.L;
    C = g.C;

    grille.resize(g.L * g.C);
    tabRoute.resize(g.L * g.C);

    for(int keke = 0; keke < L * C ; keke++) {
        grille[keke].i = g.grille[keke].i;
        grille[keke].j = g.grille[keke].j;
        grille[keke].altitude = g.grille[keke].altitude;
        grille[keke].couleur = g.grille[keke].couleur;
        grille[keke].librairie = g.grille[keke].librairie;
    }
}

//Formule pour passer de la grille 2D au tableau 1D
int Graphe::indice(const int i, const int j) {
    return i * C + j;
}

int Graphe::ligne(const int indice) {
    return indice / C;
}

int Graphe::colonne(const int indice) {
    return indice % C;
}

int Graphe::altitude(const int indice) {
    return grille[indice].altitude;
}

int Graphe::couleur(const int indice) {
    return grille[indice].couleur;
}

int Graphe::nord(const int ind) {
    int i = ligne(ind) - 1;
    int j = colonne(ind);

    if (i >= 0) {
        return indice(i,j);
    }
    else {
        return -1;
    }
}

int Graphe::sud(const int ind) {
    int i = ligne(ind) + 1;
    int j = colonne(ind);

    if (i < L) {
        return indice(i,j);
    }
    else {
        return -1;
    }
    
}

int Graphe::ouest(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) - 1;

    if (i >= 0) {
        return indice(i,j);
    }
    else {
        return -1;
    }
}

int Graphe::est(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) + 1;

    if (i < C) {
        return indice(i,j);
    }
    else {
        return -1;
    }
}

bool Graphe::existeNord(const int ind) {
    int i = ligne(ind) - 1;
    int j = colonne(ind);

    if(altitude(indice(i, j)) == -1)
        return false;

    if(i >= 0) return true;
    else return false;
}

bool Graphe::existeSud(const int ind) {
    int i = ligne(ind) + 1;
    int j = colonne(ind);
    if(altitude(indice(i, j)) == -1)
        return false;

    if(i < L) return true;
    else return false;
}

bool Graphe::existeOuest(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) - 1;
    if(altitude(indice(i, j)) == -1)
        return false;

    if(j >= 0) return true;
    else return false;
}

bool Graphe::existeEst(const int ind){
    int i = ligne(ind);
    int j = colonne(ind) + 1;
    if(altitude(indice(i, j)) == -1)
        return false;

    if(j < C) return true;
    else return false;
}

std::array<int, 4> Graphe::voisins(const int ind) {
    std::array<int, 4> tabVoisins;

    if(altitude(ind) != -1) {

        if(existeNord(ind)) {
            tabVoisins[0] = nord(ind);
        }
        else {
            tabVoisins[0] = -1;
        }

        if(existeSud(ind)) {
            tabVoisins[1] = sud(ind);
        }
        else {
            tabVoisins[1] = -1;
        }

        if(existeOuest(ind)) {
            tabVoisins[2] = ouest(ind);
        } 
        else {
            tabVoisins[2] = -1;
        } 
        if(existeEst(ind)) {
            tabVoisins[3] = est(ind);
        }
        else {
            tabVoisins[3] = -1;
        }
    }
    else {
        for(int i = 0; i < 4; i++) {
            tabVoisins[i] = -1;
        }
    }
    return tabVoisins;
}

void Graphe::affichage() {

    for(int i = 0 ; i < L ; i++) {
        for(int j = 0 ; j < C ; j++) {
            int alt = grille[indice(i,j)].altitude;
            if(alt == -1){
                cout<<"-";
            }
            else{
                cout << alti;
            }
            cout<<"  ";
        }
        cout<<endl;
    }
}

void Graphe::modifAlti(const int i,const int j, const int alti) {
    if (grille[indice(i,j)].altitude == -1) {
        cout<<"Sommet inexistant"<<endl;
    }
    else {
        grille[indice(i,j)].altitude = alti;
    }
}