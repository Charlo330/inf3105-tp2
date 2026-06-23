/* INF3105 / TP2 */
#include "client.h"
#include "tableau.h"
#include <fstream>
#include <iostream>

using namespace std;

/**
 * Génère récursivement toutes les combinaisons de k éléments du tableau.
 *
 * @param tableau Le tableau contenant les éléments à combiner.
 * @param k Le nombre d'éléments restant à ajouter à la combinaison courante.
 * @param current La combinaison en cours de construction.
 * @param resultats Le tableau dans lequel sont enregistrées les combinaisons générées.
 * @param pos L'indice à partir duquel les prochains éléments peuvent être sélectionnés.
 */
void combinaison(const Tableau<std::string> &tableau, unsigned int k,
                 Tableau<std::string> &current,
                 Tableau<Tableau<std::string>> &resultats, unsigned int pos = 0) {
  if (k == 0) {
    resultats.ajouter(current);
    return;
  }
  for (int i = pos; i < tableau.taille(); i++) {
    current.ajouter(tableau[i]);
    combinaison(tableau, k - 1, current, resultats, i + 1);
    current.enlever(current.taille() - 1);
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

/**
 * Détermine la combinaison de films qui satisfait le plus grand nombre de clients.
 *
 * @param films Le tableau de tous les films disponibles.
 * @param clients Le tableau des clients et de leurs préférences.
 * @param combinaisonsFilms Le tableau contenant les combinaisons de films à évaluer.
 * @return La combinaison de films qui maximise le nombre de clients satisfaits.
 */
std::string
plusieursSallesCinema(const Tableau<std::string> &films,
                      Tableau<Client> &clients,
                      Tableau<Tableau<std::string>> &combinaisonsFilms) {
  int nbMaxSatisfait = -1;
  std::string stringCombinaisonFilmMaximise;
  std::string stringCombinaisonFilm;
  // pour chaque film de combinaison
  int nombreCombinaisons = combinaisonsFilms.taille();

  for (int i = 0; i < nombreCombinaisons; i++) {
    // Réinitialiser l'état des clients avant chaque évaluation
    for (int j = 0; j < clients.taille(); j++) {
      clients[j].estSatisfait = false;
    }
    
    int nbSatisfait = 0;
    for (int k = 0; k < combinaisonsFilms[i].taille(); k++) {
      std::string film = combinaisonsFilms[i][k];
      stringCombinaisonFilm += film + "\n";
      for (int j = 0; j < clients.taille(); j++) {
        if (!clients[j].estSatisfait && clients[j].veutEcouterFilm(film)) {
          nbSatisfait++;
          clients[j].estSatisfait = true;
        }
      }
    }
    if (nbSatisfait > nbMaxSatisfait) {
      nbMaxSatisfait = nbSatisfait;
      stringCombinaisonFilmMaximise = stringCombinaisonFilm + std::to_string(nbSatisfait);
    }
    stringCombinaisonFilm = "";
  }
  return stringCombinaisonFilmMaximise;
}

void tp2(const Tableau<std::string> &films, Tableau<Client> &clients,
         int nbsalles = 2) {

  if (nbsalles == 1) {
    std::cout << uneSalleCinema(films, clients);
  } else {
    Tableau<std::string> current;
    Tableau<Tableau<std::string>> resultats;
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
