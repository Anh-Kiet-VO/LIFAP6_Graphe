#include <iostream>
#include "graphe.h"

using namespace std;

int main(){

    // Initialisation et affichage d'un graphe vide 
    //Graphe g(5,5);
    //g.affichage();

    //  Lecture de notre fichier graphe et affichage de celle-ci
    //g.lireFichier("Graphe.txt");
    Graphe g2("Graphe.txt");
    g2.affichage();
    g2.modifAlti(0,0,5);

    cout<<endl;

    // Affichage de notre fichier graphe avec    
    g2.affichage();

    // On check si les voisins marchent
    int valVoisin;
    char boolTrouverVoisin;

    cout<<"Voulez vous trouver les voisins d'un indice ? Y/N ";
    cin>>boolTrouverVoisin;
    
    if(boolTrouverVoisin == 'Y') {
        cout<<endl;
        cout<<"Quel voisin voulez-vous chercher ? (Donnez l'indice) ";
        cin>>valVoisin;
        g2.voisins(valVoisin);
        cout<<endl;
        g2.affichage();
        cout<<endl;
    }   

    char boolNoeud;
    Noeud n;

    cout<<"Voulez vous ajouter un nouveau noeud ? Y/N ";
    cin>>boolNoeud;

    if(boolNoeud == 'Y') {
        cout<<endl;

        cout<<"Altitude de votre noeud ? ";
        int altiNoeud;
        cin>>altiNoeud;
        n.altitude = altiNoeud;

        cout<<endl;

        cout<<"Valeur en i de votre noeud ? ";
        int iNoeud;
        cin>>iNoeud;
        n.i = iNoeud;

        cout<<endl;

        cout<<"Valeur en j de votre noeud ? ";
        int jNoeud;
        cin>>jNoeud;
        n.j = jNoeud;

        g2.ajoutNoeud(n);
        cout<<endl;
        g2.affichage();
        cout<<endl;
    }

    int valAlti;
    char boolTrouverAlti;

    cout<<"Voulez vous trouver l'altitude d'un indice ? Y/N ";
    cin>>boolTrouverAlti;

    if(boolTrouverAlti == 'Y') {
        cout<<endl;
        cout<<"Quel noeud voulez-vous trouver son altitude ? (Donnez l'indice) ";
        cin>>valAlti;
        cout<<g2.altitude(valAlti);
        cout<<endl;
    }

    g2.calculeRoute(0);

    return 0;
}
