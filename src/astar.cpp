#include <iostream>
#include <fstream>
#include <math.h>
#include <limits>
#include <climits>
#include <vector>
#include <algorithm>

#include "astar.h"

using namespace std;

// Constructeur par défaut de notre Noeud
Node::Node(int L, int C, int distance) {
	this->L = L;
    this->C = C;
    this->distance = distance;
    if(distance == -1) {
        isWall = true;
    }
}

// Lecture de notre grille pour pouvoir faire A*
AStar::AStar(const char * fileName) {
        ifstream file(fileName);

        if(!file.is_open()) {
            cout << "Erreur dans l'ouverture en lecture du fichier : " << fileName << "\n";
            exit(EXIT_FAILURE);
        }

        file >> Ls;
        file >> Cs;

        for(int L = 0; L < Ls; L++) {
            for(int C = 0; C < Cs; C++) {
                int distance;

                file >> distance;

                Node * node = new Node(L, C, distance);

                nodes.push_back(node);
            }
        }
}

// Nodes F_Cost, G_Cost + H_Cost
int Node::get_f() {
	return g + h;
}

// Permet d'accéder aux informations d'un noeud
Node * AStar::getNode(int L, int C) {
	return nodes[indice(L, C)];
}

// Indice global
int AStar::indice(const int i, const int j) {
    return i * Cs + j;
}

// Permet de modifier l'altitude d'un noeud
void AStar::modifyDistance(const int i, const int j, const int distance) {
    nodes[indice(i, j)]->distance = distance;
}

// Trouve le noeud avec le F_Cost le plus faible et donc le choisir afin de le marquer vert
// et calculer de nouveau les voisins mais pour ce nouveau noeud marqué vert
Node * AStar::getLowestFCostNode() {
	Node * node = nullptr;
    int min_f = INT_MAX;

    // on parcourt chaque noeud et on regarde si celui-ci a le coût F le plus faible
    for(Node * n : openNodes) {
		if(n->get_f() < min_f ) {
			min_f = n->get_f();
            node = n;
        }
    }
    return node;
}

// Verifie si openNodes contient le noeud actuel "Noeud"
bool AStar::isInOpenNodes(Node * node) {
    for(Node * n : nodes) {
        if (n == node) {
            return true;
        }
        return false;
    }
}

// Enleve le noeud de notre liste OpenNodes
void AStar::removeNodeFromOpenList(Node * node) {
    int index = -1;
    
    // On parcourt notre tableau openNodes
    for(int i  = 0; i < (int) openNodes.size(); i++) {
		if(openNodes[i] == node) {
            index = i;
            break;
        }
    }

    // On break pour sortir du noeud et on le supprime
	if(index != -1) {
		openNodes.erase(openNodes.begin() + index);
    }
}


// Calcul le chemin le plus court pour partir à Paris
// Si ce n'est pas un bon noeud, on va explorer le voisin de celui-ci
void AStar::calculate(int destL, int destC) {
	Node * startNode = getNode(0, 0); // Lyon, décidé par nous
    Node * targetNode = getNode(destL, destC); // Paris, décidé par l'utilisateur

    cout << "Position de Paris : (" << targetNode->L << ", " << targetNode->C << ") | Noeud en question : " << targetNode->distance << endl;

    // on met notre noeud de départ (Lyon) dans la liste openNodes, 1er noeud qu'on va "explorer"
    openNodes.push_back(startNode);

    // boucle while pour calculer jusqu'à qu'on trouve un noeud 
    while(true) {
        // On recherche le noeud avec le F_cost le plus faible
		Node * currentNode = getLowestFCostNode();

        // Si ce noeud est le noeud qu'on recherche, on trace le chemin de startNode à targetNode, parfait !
		if(currentNode == targetNode) {
            cout << "chemin : "<<endl;
            traceAndStorePaths(startNode, targetNode);
            return;
        }

        // Sinon, on continue de chercher Paris...
        currentNode->isVisited = true;

        // On enlève le currentNode de notre liste car déjà exploré
        removeNodeFromOpenList(currentNode);

        // On explore ses voisins pour trouver le prochain noeud 
        exploreNeighbors(currentNode->L, currentNode->C, targetNode);
    }
}

// Permet d'explorer les voisins autour de notre currentNode 
// afin de déterminer le meilleur prochain noeud possible
void AStar::exploreNeighbors(int L, int C, Node * targetNode) {
    // Un noeud a au total 8 voisins, ici leur coordoonées
    // Parcours en profondeur des voisins, changement en fonction des x et y
    // ex : tout dernier pos à (1,2) variation en y (L) de 0 et variation de x (C) de -1 (le left on va à gauche)
    int dir_L[8] = {1, -1, 1, -1, 1, -1, 0, 0};
    int dir_C[8] = {-1, -1, 1, 1, 0, 0, 1, -1};

    // Le noeud de départ
    Node * currentNode = getNode(L, C);

    // On explore les 8 voisins
	for(int i = 0; i < 8; i++) {
        // La prochaine ligne/Conne, ce sont les voisins
		int next_L = L + dir_L[i];
		int next_C = C + dir_C[i];

        // Si la ligne/Colonne suivante est inférieur à 0 OU si elle est supérieur à la ligne/Conne -1 
        // C'est-à-dire si elle est en dehors de notre grille ===> On passe au i+1 suivant vu qu'il n'aura pas de voisin
		if (next_L < 0 || next_L > Ls - 1) continue;
		if (next_C < 0 || next_C > Cs - 1) continue;

        // Notre prochain noeud grâce à next_L et next_C
        Node * nextNode = getNode(next_L, next_C);

        // Si le prochain noeud a été visité ou si on tombe sur un obstacle ===> On passe au i+1 suivant
		if (nextNode->isVisited || nextNode->isWall) continue;

        // Somme des poids des arêtes entre le noeud de départ
        // et le noeud manipulé. On peut retrouver ce chemin en suivant les pred.
        // ce qui nous ramènera du noeud qu'on manipules au noeud de départ
		int neighborsPathG = currentNode->g + nextNode->distance;
    
        // Si la distance est inférieur au G_cost de notre nouveau noeud OU si le prochain noeud n'est pas dans notre openNodes
        // (S'il est dans openNode on ne veut pas, vu qu'on l'aura déjà "vérifié")
        // Alors on change le g et h de notre nouveau noeud
		if(neighborsPathG < nextNode->g || !isInOpenNodes(nextNode)) {
			nextNode->g = neighborsPathG; // On additionne le G_cost actuel avec notre nouveau G_cost
			nextNode->h = heuristic(nextNode, targetNode);

			nextNode->pere = currentNode;
            nextNode->isExplored = true;

            // Si notre prochain noeud n'est pas dans notre openNodes, on ajoute celui-ci
            // Cela voudra dire qu'on l'aura "déjà vérifié"
            if(!isInOpenNodes(nextNode)) {
				openNodes.push_back(nextNode);
            }
		}
	}
}

// H_Cost : opposé du Nodes G. Distance, par rapport au noeud final
// Utilisé pour connaître le F_Cost le plus faible
int AStar::heuristic(Node * n1, Node * n2) {
	int dst_x = abs(n1->C - n2->C);
	int dst_y = abs(n1->L - n2->L);

	if(dst_x > dst_y) { 
		return (5 * dst_y + 3 * (dst_x - dst_y));
	} else {
		return (5 * dst_x + 3 * (dst_y - dst_x));
	}

    //return sqrt(1 + (dst_x - dst_y) * (dst_x - dst_y)); --> Distance euclidienne
}

// Affichage de notre grille de départ
void AStar::draw() {
    cout << endl << endl;
    int col = 0;

    for(Node * n : nodes) {
        if(n->distance == -1) { // Si c'est un obstacle on met un x
            cout <<  "x ";
        } else { // Sinon on affichage le noeud
			cout << n->distance << " ";
        }

        col++;

        // Si on est en dehors de la grille on affiche pas
        if(col > Cs - 1) {
			col = 0;
            cout << endl;
        }
    }
    cout << endl;
}

// Calcul la route entre startNode (Lyon) et targetNode (Paris)
// Vector pas de push_front donc en sens inverse, si 0 -> 2 -> 3 -> 6 ==> inverse
void AStar::traceAndStorePaths(Node * startNode, Node * targetNode) {
    paths.push_back(targetNode);

    Node * current = targetNode->pere;
    while(current->pere != nullptr) {
        paths.push_back(current);
        current = current->pere;
    }
    
    paths.push_back(startNode);
}

// Booléen qui vérifie si le noeud en parametre est sur notre chemin
bool AStar::isInPath(Node * node) {
    for(Node * n : paths) {
        if(n == node) {
            return true;
        }
    }
    return false;
}

// Dessine le chemin allant de Lyon à Paris
void AStar::drawPath() {
        // Pour chaque noeud si il est dans paths, on l'affiche
        for(Node * n : paths) {
            cout << n->distance << " ";
        }

        cout << endl << endl << endl;

        int col = 0;
        for(Node * n : nodes) {
            if(n->distance == -1) { // Si c'est un obstacle on met un x
                cout <<  "x ";
            }
            else { 
                if(isInPath(n)) { // Le chemin définitif le plus court - Noir mais en Vert pour moi
                    std::printf("\033[0;33;49m%d\033[0m", n->distance);
                    cout << " ";
                }
                else if (n->isExplored) { // Les voisins qu'il a exploré mais pas le chemin définitif - Gris mais en Bleu pour moi
                    std::printf("\033[0;34;49m%d\033[0m", n->distance);
                    cout << " ";
                }
                else { // Le reste
                    cout << n->distance << " ";
                }
            }

            col++;

            // Si on est en dehors de la grille on affiche pas
            if(col > Cs - 1) {
                col = 0;
                cout << endl;
            }
        }
        cout << endl << endl;
}