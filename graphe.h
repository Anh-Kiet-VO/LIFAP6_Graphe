#ifndef _GRAPHE
#define _GRAPHE

#include <vector>
#include <array>
#include <string>

using namespace std;

struct Noeud{
    int i, j, altitude;

    //0 = blanc, 1 = gris, 2 = noir
    int couleur;

    //false = pas une librairie
    bool librairie;
};

struct Dijkstra{
    Noeud pred;

    float distance; //sqrt(1 + sqr(h(i,j) − h(i − 1,j))) -> distance entre h(i, j) et voisin Nord
};

class Graphe{
    public:
        vector<Noeud> grille;           //tableau des noeuds (sommet)      
        vector<Dijkstra> tabRoute;      //tableau des distance/pred
        vector<int> tabLibrairie;       //tab des indices 1D des librairies
        vector<float> coutLibrairie;    //tab des cout pour aller aux librairies
        int L, C;

        Graphe();
        Graphe(const int lignes, const int colonnes);
        Graphe(const Graphe &a);

        /**
         * @brief Va lire le fichier, et remplir la grille avec les valeurs
         */
        void lecture(const std::string &fichier);

        void lectureLib(const std::string &fichier);

        /**
         * @brief Renvoie l'indice du tableau 1D correspondant
         * aux coordonnées (i j) du noeud de la grille en 2D
         */
        int indice(const int i, const int j);

        /**
         * @brief Renvoie le numéro de la ligne et 
         * de la colonne ainsi que l'altitude de l'indice 
         * en paramètre
         */
        int ligne(const int indice);
        int colonne(const int indice);
        int altitude(const int indice);
        int couleur(const int indice);

        /**
         * @brief Retourne l'indice des voisins N, S, E et O 
         * de la valeur dont l'indice est passé en paramètre
         * Retourne -1 si le voisin n'existe pas
         */
        int nord(const int ind);
        int sud(const int ind);
        int ouest(const int ind);
        int est(const int ind);

        /**
         * @brief Return true si les voisins N, S, O et E
         * de la valeur de l'indice passé en paramètre existent,
         * false sinon
         */
        bool existeNord(const int ind);
        bool existeSud(const int ind);
        bool existeOuest(const int ind);
        bool existeEst(const int ind);

        /**
         * @brief Remplit un array de taille 4 de l'indice des 4 voisins
         * de la valeur dont l'indice est passé en paramètre.
         * Si la valeur en question est -1 (ce qui signifie que
         * la donnée n'existe pas), remplit le tableau de -1, car une donnée
         * n'existant pas ne peut avoir de voisins
         */
        array<int, 4> voisins(const int ind);

        /**
         * @brief Affiche sous format 2D le tableau en 1D
         * les '-' correspondent aux emplacements vides.
         */
        void affichage();

        // affiche le graphe (mais uniquement les libs (leur indices))
        void afficheLibrairie();

        /**
         * @brief Prend les coordonnées i et j d'un noeud de la grille
         * et remplace l'altitude correspondant à ce noeud[i, j] par alt
         */
        void modifAlti(const int i,const int j, const int alti);

        /**
         * @brief Ajoute un noeud n à notre grille
         */
        void ajoutNoeud(Noeud n);

        /**
         * @brief Supprime le noeud dont les coordonnées sont passées
         * en paramètre
         */
        void supprimeNoeud(const int i, const int j);

        /**
         * @brief renvoie la distance euclidienne entre ind et indBis
         */
        float distanceEuclidienne(const int ind, const int indBis);

        /**
         * @brief Algorithme de Dijkstra
         * Calcule toutes les routes pour aller de ind à tous les sommets de Dijkstra en empruntant la moins chère
         */
        void calculeRoute(const int ind);

        /**
         * @brief Renvoie la route la moins chère pour aller du point indA au point indB
         */
        float cheminLePlusCourt(const int indA, const int intB);

        /**
         * @brief Va écrire une nouvelle grille remplie des indices des plus courts chemins des librairies par sommet
         */
        void siteLibrairie();
        
};

#endif
