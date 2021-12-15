#ifndef _ASTAR
#define _ASTAR

using namespace std;
#include <iostream>
#include <vector>

class Node {
    friend class AStar;

    public:
    // Constructeur par défaut de notre Noeud
    Node(int L, int C, int distance);
    
    int L;
    int C;
    int distance;

    // pour tracer notre chemin (traceAndStorePaths) - pas besoin de priorityQueue etc
    Node * pere = nullptr; 

    bool isWall = false;
    bool isExplored = false;
    bool isVisited = false;

    // G_Cost : distance par rapport au point de départ
    int g = 0;

    // H_Cost : distance par rapport au point d'arrivé
    int h = 0;

    // Nodes F_Cost, G_Cost + H_Cost
    int get_f();
};

class AStar {
    vector<Node*> nodes; // Tableau de Noeud cest-à-dire de notre grille

    int Ls = 0; // Dimension x de notre grille 
    int Cs = 0; // Dimension y de notre grille

    vector<Node*> openNodes; // Tableau de nos noeuds "déjà exploré" où le F_cost a été calculé
    vector<Node*> paths; // Tableau de noeuds c'est-à-dire de notre chemin final

    public:
    // Lecture de notre grille pour pouvoir faire A*
    AStar(const char * fileName);

    // Permet d'accéder aux informations d'un noeud
    Node * getNode(int L, int C);

    // Indice global
    int indice(const int i, const int j);

    // Permet de modifier l'altitude d'un noeud
    void modifyDistance(const int i, const int j, const int distance);

    // Trouve le noeud avec le F_Cost le plus faible et donc le choisir afin de le marquer vert
    // et calculer de nouveau les voisins mais pour ce nouveau noeud marqué vert
    Node * getLowestFCostNode();
    
    // Verifie si openNodes contient le noeud actuel "Noeud"
    bool isInOpenNodes(Node * node);

    // Enleve le noeud de notre liste OpenNodes
    void removeNodeFromOpenList(Node * node);

    // Calcul le chemin le plus court pour partir à Paris
    // Si ce n'est pas un bon noeud, on va explorer le voisin de celui-ci
    void calculate(int destL, int destC);
    
    // Permet d'explorer les voisins autour de notre currentNode 
    // afin de déterminer le meilleur prochain noeud possible
	void exploreNeighbors(int L, int C, Node * targetNode);
    
    // H_Cost : opposé du Nodes G. Distance, par rapport au noeud final
    // Utilisé pour connaître le F_Cost le plus faible
    int heuristic(Node * n1, Node * n2);

    // Affichage de notre grille de départ
    void draw();

    // Calcul la route entre startNode (Lyon) et targetNode (Paris)
    // Vector pas de push_front donc en sens inverse, si 0 -> 2 -> 3 -> 6 ==> inverse
    void traceAndStorePaths(Node * startNode,Node * targetNode);

    // Booléen qui vérifie si le noeud en parametre est sur notre chemin
    bool isInPath(Node * node);

    // Dessine le chemin allant de Lyon à Paris
    void drawPath();
};

#endif