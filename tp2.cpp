/* INF3105 / TP2 */
#include <iostream>
#include <fstream>
#include "tableau.h"
#include "client.h"

using namespace std;

void lire(std::istream& entree, Tableau<std::string>& films, Tableau<Client>& clients){
    // Lecture. Les opérateurs >> pour Clients est à compléter.
    int nbDeFilms=0;
    entree >> nbDeFilms; // m

    for(int i=0;i<nbDeFilms;i++) {
        std::string film;
        entree >> film;
        films.ajouter(film);
    }

    int nbDeClients=0;
    entree >> nbDeClients; // p

    
    for(int i=0;i<nbDeClients;i++) {
        Client c;
        entree >> c;
        clients.ajouter(c);
    }

    // Lecture terminée.
    /*
    std::cerr << "Lecture terminée" << std::endl;
    std::cerr << "Nombre de films: " << nbDeFilms << " : ";
    std::cerr << "Nombre de clients: " << nbDeClients << std::endl;
    */
}

void tp2(const Tableau<std::string>& films, const Tableau<Client>& clients, int nbsalles=2){

    // Pour commencer, supportez une seule salle de cinéma station.
    // Ensuite, améliorez votre programme pour 2.
    // Ensuite, généralisez à n.
    if(nbsalles == 1){
        // Mettez l'algorithme ici.
        // Affichez le résultat;
    }else{
        std::cout << "Cette version ne supporte que les problèmes avec exactement une salle de cinéma!" << endl;
    }
}

int main(int argc, const char** argv) {
    // Entrée:
    int nbsalles = 1;
    const char* nom_fichier = nullptr;
    
    // Traitement des arguments reçus en ligne de commande
    for(int i=1;i<argc;i++){
        if(argv[i][0]=='-'){
            nbsalles = atoi(argv[i]+1);
        }else if(nom_fichier==nullptr){
            nom_fichier = argv[i];
        }else{
            std::cout << "Erreur de syntaxe d'appel au programme!" << std::endl;
            return 1;
       }
    }

    Tableau<std::string> films;
    Tableau<Client> clients;

    // Appel à la fonction tp2
    if(nom_fichier!=nullptr){
        std::ifstream lecteurfichier(nom_fichier);
        if(lecteurfichier.fail()){
            std::cout << "Erreur d'ouverture du fichier '" << nom_fichier << "'" << std::endl;        
            return 2;
        }
        lire(lecteurfichier, films, clients);
    }else{
        lire(std::cin, films, clients);
    }
    
    tp2(films, clients, nbsalles);
    return 0;
}

