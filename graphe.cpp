#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include "graphe.h"

using namespace std;

Graphe::Graphe(){

}

Graphe::Graphe(const int lignes, const int colonnes) {
    L = lignes;
    C = colonnes;

    grille.resize(L * C);
    tabRoute.resize(L * C);

    for(int w = 0; w < lignes * colonnes; w++) {
        grille[w].altitude = -1;
    }
}

Graphe::Graphe(const Graphe &g) {
    L = g.L;
    C = g.C;

    grille.resize(g.L * g.C);
    tabRoute.resize(g.L * g.C);

    for(int k = 0; k < L * C; k++) {
        grille[k].i = g.grille[k].i;
        grille[k].j = g.grille[k].j;
        grille[k].altitude = g.grille[k].altitude;
        grille[k].couleur = g.grille[k].couleur;
        grille[k].librairie = g.grille[k].librairie;
    }
}

int Graphe::indice(const int i, const int j) {
    return i * C + j;
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
    } else {
		return -1;
	}
}

int Graphe::sud(const int ind) {
    int i = ligne(ind) + 1;
    int j = colonne(ind);

    if (i < L) {
        return indice(i,j);
    } else {
		return -1;
	}
}

int Graphe::ouest(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) - 1;

    if (i >= 0) {
        return indice(i,j);
    } else {
		return -1;
	}
}

int Graphe::est(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) + 1;

    if (i < C) {
        return indice(i,j);
    } else {
		return -1;
	}
}

array<int, 4> Graphe::voisins(const int ind){
    array<int, 4> tabVoisins;

    if(altitude(ind) != -1) {
		// Si le nord existe, alors 
        if(existeNord(ind)) {
			tabVoisins[0] = nord(ind);
		} else {
			tabVoisins[0] = -1;
		}

		// Si le sud existe, alors 
        if(existeSud(ind)) {
			tabVoisins[1] = sud(ind);
		} else {
			tabVoisins[1] = -1;
		}

		// Si le ouest existe, alors 
        if(existeOuest(ind)) {
			tabVoisins[2] = ouest(ind);
		} else {
			tabVoisins[2] = -1;
		}

		// Si le est existe, alors 
        if(existeEst(ind)) {
			tabVoisins[3] = est(ind);
		} else {
			tabVoisins[3] = -1;
		}
    } else {
        for(int i = 0 ; i < 4 ; i++) {
			tabVoisins[i] = -1;
		}  
    }
    return tabVoisins;
}

void Graphe::modifAlti(const int i,const int j, const int alti){
    if (grille[indice(i,j)].altitude == -1) {
        cout<<"Sommet inexistant"<<endl;
    } else {
        grille[indice(i,j)].altitude = alti;
    }
}

void Graphe::affichage() {
    for(int i = 0 ; i < L ; i++) {
        for(int j = 0 ; j < C ; j++) {
            int alti = grille[indice(i,j)].altitude;

            if(alti == -1) {
                cout<<"-";
            }
            else {
                cout << alti;
            }
            cout<<"  ";
        }
        
        cout<<endl;
    }
}

