#include <iostream>
#include "astar.h"

using namespace std;

int main(){
    AStar a("astar.txt");

    a.draw();
    

    // On demande à l'utilisateur s'il veut modifier l'altitude 
    char askDistanceChange;
    cout<<"Voulez-vous modifier l'altitude d'un noeud ? Y/N : ";
    cin>>askDistanceChange;
    if(askDistanceChange == 'Y') {
        cout<<endl;

        int valDistanceChange;
        cout<<"Valeur de votre altitude ? : ";
        cin>>valDistanceChange;

        cout<<endl;

        int posXDistanceChange;
        cout<<"Position x du noeud : ";
        cin>>posXDistanceChange;

        cout<<endl;

        int posYDistanceChange;
        cout<<"Position y du noeud : ";
        cin>>posYDistanceChange;

        a.modifyDistance(posXDistanceChange, posYDistanceChange, valDistanceChange);
        a.draw();

        cout<<endl;
    }
    

    // On demande à l'utilisateur s'il veut afficher l'altitude 
    char askDistance;
    cout<<"Voulez-vous afficher l'altitude d'un noeud ? Y/N : ";
    cin>>askDistance;
    if(askDistance == 'Y') {
        cout<<endl;

        int posXDistance;
        cout<<"Position x du noeud : ";
        cin>>posXDistance;

        int posYDistance;
        cout<<"Position y du noeud : ";
        cin>>posYDistance;

        cout<<a.getNode(posXDistance, posYDistance)->distance;

        cout<<endl;
    }

    // On demande à l'utilisateur les coordonées de Paris afin de calculer le chemin le plus court
    int posXParis, posYParis;

    cout<<"Position x de Paris ? : ";
    cin>>posXParis;
    cout<<endl; 

    cout<<"Position y de Paris ? : ";
    cin>>posYParis;
    cout<<endl; 

    a.calculate(posXParis, posYParis);

    a.drawPath();

    return 0;
}
