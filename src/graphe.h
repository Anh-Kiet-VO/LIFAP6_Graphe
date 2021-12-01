#ifndef _GRAPHE
#define _GRAPHE

#include <vector>
#include <array>
#include <string>

using namespace std;

class Noeud {
    friend class Graphe;
    friend class Noeud;
    public:
    int i, j, altitude;

    //0 = blanc, 1 = gris, 2 = noir
    int couleur;

};

class Dijkstra{
    friend class Noeud;
    public:
    Noeud pred;

    float distance; //sqrt(1 + sqr(h(i,j) − h(i − 1,j))) -> distance entre h(i, j) et voisin Nord
};

class Graphe {
    
    public:
        vector<Noeud> grille;           //tableau des noeuds (sommet)    
        vector<Dijkstra> tabRoute;    
        int L, C;

        Graphe();
        Graphe(const char * fichier);
        Graphe(const int lignes, const int colonnes);
        Graphe(const Graphe &a);

        bool grilleOK(const int indice);

        void lireFichier(const string &nom_fichier);

        int indice(const int i, const int j);

        int ligne(const int indice);
        int colonne(const int indice);
        int altitude(const int indice);
        int couleur(const int indice);

        int getNord(const int ind);
        int getSud(const int ind);
        int getOuest(const int ind);
        int getEst(const int ind);

        bool nord(const int ind);
        bool sud(const int ind);
        bool ouest(const int ind);
        bool est(const int ind);

        array<int, 4> voisins(const int ind);

        void affichage();

        void modifAlti(const int i,const int j, const int alti);

        void ajoutNoeud(Noeud n);

        void supprimeNoeud(const int i, const int j);

        float distanceEuclidienne(const int indA, const int indB);

        void calculeRoute(const int ind);
};

#endif
