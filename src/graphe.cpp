#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>

#include "graphe.h"

using namespace std;

Graphe::Graphe() {
    L = 0;
    C = 0;

    grille.resize(L * C);

    for(int cece = 0; cece < L * C; cece++) {
        grille[cece].altitude = -1;
    }
}

Graphe::Graphe(const char * fichier)
{
	lireFichier(fichier);
}

Graphe::Graphe(const int lignes, const int colonnes) {
    L = lignes;
    C = colonnes;

    grille.resize(L * C);

    for(int cece = 0; cece < lignes * colonnes; cece++) {
        grille[cece].altitude = -1;
    }
}

Graphe::Graphe(const Graphe &g) {
    L = g.L;
    C = g.C;

    grille.resize(g.L * g.C);

    for(int keke = 0; keke < L * C ; keke++) {
        grille[keke].i = g.grille[keke].i;
        grille[keke].j = g.grille[keke].j;
        grille[keke].altitude = g.grille[keke].altitude;
        grille[keke].couleur = g.grille[keke].couleur;
        grille[keke].librairie = g.grille[keke].librairie;
    }
}

void Graphe::lireFichier(const string &nom_fichier) {
    ifstream fichierLecture(nom_fichier);

    //Si le fichier ne s'ouvre pas
    if(!fichierLecture.is_open()) {
        cout << "Erreur dans l'ouverture en lecture du fichier : "<< nom_fichier;
        exit(EXIT_FAILURE);
    }

    int sommet;
    Noeud n;

    fichierLecture >> L;
    fichierLecture >> C;
    
    //Redimmensionne la grille avec la taille trouvée dans le fichier
    grille.resize(L * C);

    //Lit le fichier et remplit la grille avec les valeurs
    //et les coordonnées adéquates
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            fichierLecture >> sommet;

            n.altitude = sommet;

            n.i = i;
            n.j = j;

            n.librairie = 0;

            if(n.altitude != -1) {
                n.couleur = 0;
            }

            grille[indice(i, j)] = n;
        }
    }
    fichierLecture.close();
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

bool Graphe::grilleOK(const int indice) {
    if(indice < L * C) {
        return 1;
    } else return 0;
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

    if(altitude(indice(i, j)) == -1) {
        return false;
    }
        
    if(j >= 0) {
        return true;
    }
    else {
        return false;
    } 
}

bool Graphe::existeEst(const int ind) {
    int i = ligne(ind);
    int j = colonne(ind) + 1;
    
    if(altitude(indice(i, j)) == -1) {
        return false;
    }

    if(j < C) {
        return true;
    }
    else {
        return false;
    }
}

std::array<int, 4> Graphe::voisins(const int ind) {
    std::array<int, 4> tabVoisins;

    if(altitude(ind) != -1 && grilleOK(ind) == 1) {
        // Si il y a un voisin au nord, on stock celui-ci
        if(existeNord(ind)) {
            tabVoisins[0] = nord(ind);
            cout<<"Nord OK";
        }
        else {
            tabVoisins[0] = -1;
        }

        // Si il y a un voisin au sud, on stock celui-ci
        if(existeSud(ind)) {
            tabVoisins[1] = sud(ind);
            cout<<"Sud OK";
        }
        else {
            tabVoisins[1] = -1;
        }

        // Si il y a un voisin à l'ouest, on stock celui-ci
        if(existeOuest(ind)) {
            tabVoisins[2] = ouest(ind);
            cout<<"Ouest OK";
        } 
        else {
            tabVoisins[2] = -1;
        } 

        // Si il y a un voisin à l'est, on stock celui-ci
        if(existeEst(ind)) {
            tabVoisins[3] = est(ind);
            cout<<"Est OK";
        }
        else {
            tabVoisins[3] = -1;
        }
    } // Sinon, il n'y a pas de voisin donc -1
    else {
        for(int i = 0; i < 4; i++) {
            tabVoisins[i] = -1;
        }
    }
    return tabVoisins;
}

void Graphe::affichage() {
    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            int alti = grille[indice(i,j)].altitude;

            if(alti == -1) {
                cout<<"x";
            }
            else {
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