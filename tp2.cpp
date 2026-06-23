/* INF3105 / TP2 */
#include "client.h"
#include "pile.h"
#include "tableau.h"
#include <fstream>
#include <iostream>

using namespace std;

void combinaison(const Tableau<std::string> &tableau, unsigned int k,
                 Pile<std::string> &current,
                 Tableau<Pile<std::string>> &resultats, unsigned int pos = 0) {
  if (k == 0) {
    resultats.ajouter(current);
    return;
  }
  for (int i = pos; i < tableau.taille(); i++) {
    current.empiler(tableau[i]);
    combinaison(tableau, k - 1, current, resultats, i + 1);
    current.depiler();
  }
}

void lire(std::istream &entree, Tableau<std::string> &films,
          Tableau<Client> &clients) {
  // Lecture. Les opérateurs >> pour Clients est à compléter.
  int nbDeFilms = 0;
  entree >> nbDeFilms; // m

  for (int i = 0; i < nbDeFilms; i++) {
    std::string film;
    entree >> film;
    films.ajouter(film);
  }

  int nbDeClients = 0;
  entree >> nbDeClients; // p

  for (int i = 0; i < nbDeClients; i++) {
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

std::string uneSalleCinema(const Tableau<std::string> &films,
                           const Tableau<Client> &clients) {

  int nbClients;
  int nbClientsMax = -1;
  std::string choixFilm;
  for (int i = 0; i < films.taille(); i++) {
    nbClients = 0;
    for (int j = 0; j < clients.taille(); j++) {
      if (clients[j].veutEcouterFilm(films[i])) {
        ++nbClients;
      }
    }
    if (nbClients > nbClientsMax) {
      nbClientsMax = nbClients;
      choixFilm = films[i];
    }
  }
  return choixFilm;
}

std::string
plusieursSallesCinema(const Tableau<std::string> &films,
                      Tableau<Client> &clients,
                      Tableau<Pile<std::string>> &combinaisonsFilms) {
  int nbMaxSatisfait = -1;
  std::string stringCombinaisonFilmMaximise;
  std::string stringCombinaisonFilm;
  // pour chaque film de combinaison
  int nombreCombinaisons = combinaisonsFilms.taille();

  for (int i = 0; i < nombreCombinaisons; i++) {
    int nbSatisfait = 0;
    std::string film;
    while (!combinaisonsFilms[i].vide()) {
      combinaisonsFilms[i].depiler(film);
      stringCombinaisonFilm += film + " ";
      for (int j = 0; j < clients.taille(); j++) {
        if (!clients[j].estSatisfait && clients[j].veutEcouterFilm(film)) {
          nbSatisfait++;
          clients[j].estSatisfait = true;
        }
      }
    }
    if (nbSatisfait > nbMaxSatisfait) {
      nbMaxSatisfait = nbSatisfait;
      stringCombinaisonFilmMaximise = stringCombinaisonFilm;
    }
  }
  return stringCombinaisonFilmMaximise;
}

void tp2(const Tableau<std::string> &films, Tableau<Client> &clients,
         int nbsalles = 2) {

  // Pour commencer, supportez une seule salle de cinéma station.
  // Ensuite, améliorez votre programme pour 2.
  // Ensuite, généralisez à n.
  if (nbsalles == 1) {
    std::cout << uneSalleCinema(films, clients);
  } else {
    Pile<std::string> current;
    Tableau<Pile<std::string>> resultats;
    combinaison(films, nbsalles, current, resultats);
    cout << plusieursSallesCinema(films, clients, resultats) << endl;
  }
}

int main(int argc, const char **argv) {
  // Entrée:
  int nbsalles = 1;
  const char *nom_fichier = nullptr;

  // Traitement des arguments reçus en ligne de commande
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      nbsalles = atoi(argv[i] + 1);
    } else if (nom_fichier == nullptr) {
      nom_fichier = argv[i];
    } else {
      std::cout << "Erreur de syntaxe d'appel au programme!" << std::endl;
      return 1;
    }
  }

  Tableau<std::string> films;
  Tableau<Client> clients;

  // Appel à la fonction tp2
  if (nom_fichier != nullptr) {
    std::ifstream lecteurfichier(nom_fichier);
    if (lecteurfichier.fail()) {
      std::cout << "Erreur d'ouverture du fichier '" << nom_fichier << "'"
                << std::endl;
      return 2;
    }
    lire(lecteurfichier, films, clients);
  } else {
    lire(std::cin, films, clients);
  }

  tp2(films, clients, nbsalles);
  return 0;
}
