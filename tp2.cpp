/* INF3105 / TP2 */
#include "client.h"
#include "tableau.h"
#include "tuple.h"
#include <fstream>
#include <iostream>

using namespace std;

void lire(std::istream &entree, Tableau<std::string> &films,
          Tableau<Client> &clients)
{
  // Lecture. Les opérateurs >> pour Clients est à compléter.
  int nbDeFilms = 0;
  entree >> nbDeFilms; // m

  for (int i = 0; i < nbDeFilms; i++)
  {
    std::string film;
    entree >> film;
    films.ajouter(film);
  }

  int nbDeClients = 0;
  entree >> nbDeClients; // p

  for (int i = 0; i < nbDeClients; i++)
  {
    Client c;
    entree >> c;
    clients.ajouter(c);
  }
}

/**
 * Détermine le film qui satisfait le plus grand nombre de clients.
 *
 * @param films Le tableau des films disponibles.
 * @param clients Le tableau des clients et de leurs préférences.
 * @return Le film qui maximise le nombre de clients satisfaits.
 */
std::string uneSalleCinema(const Tableau<std::string> &films,
                           const Tableau<Client> &clients)
{

  int nbClients;
  int nbClientsMax = -1;
  std::string choixFilm;
  for (int i = 0; i < films.taille(); i++)
  {
    nbClients = 0;
    for (int j = 0; j < clients.taille(); j++)
    {
      if (clients[j].veutEcouterFilm(films[i]))
      {
        ++nbClients;
      }
    }
    if (nbClients > nbClientsMax)
    {
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
 * @return La combinaison de films qui maximise le nombre de clients satisfaits ainsi que le nombre de clients satisfaits.
 */
Tuple<std::string, int>
plusieursSallesCinema(Tableau<Client> &clients, const Tableau<std::string> &films,
                      Tableau<int> &combinaisonFilms, Tableau<Tableau<bool>> &appreciation)
{
  int nombreCombinaisons = combinaisonFilms.taille();
  std::string stringCombinaisonFilm;
  int nbSatisfait = 0;

  for (int j = 0; j < clients.taille(); j++)
  {
    clients[j].estSatisfait = false;
  }

  for (int k = 0; k < nombreCombinaisons; k++)
  {
    int filmId = combinaisonFilms[k];

    stringCombinaisonFilm += films[filmId];
    stringCombinaisonFilm += '\n';

    for (int j = 0; j < clients.taille(); j++)
    {
      if (!clients[j].estSatisfait &&
          appreciation[filmId][j])
      {
        clients[j].estSatisfait = true;
        nbSatisfait++;
      }
    }
  }

  return Tuple<std::string, int>(stringCombinaisonFilm, nbSatisfait);
}

/**
 * Génère récursivement toutes les combinaisons de k éléments du tableau.
 *
 * @param tableau Le tableau contenant les éléments à combiner.
 * @param k Le nombre d'éléments restant à ajouter à la combinaison courante.
 * @param current La combinaison en cours de construction.
 * @param resultats Le tableau dans lequel sont enregistrées les combinaisons générées.
 * @param pos L'indice à partir duquel les prochains éléments peuvent être sélectionnés.
 */
void combinaison(const Tableau<std::string> &tableau,
                 unsigned int k,
                 Tableau<int> &current,
                 const Tableau<string> &films,
                 Tuple<std::string, int> &combinaisonMax,
                 Tableau<Tableau<bool>> &appreciation,
                 Tableau<bool> &satisfait,
                 int nbSatisfait,
                 unsigned int pos)
{
  if (k == 0)
  {
    if (nbSatisfait > combinaisonMax.getJ())
    {
      std::string str;

      for (int i = 0; i < current.taille(); i++)
      {
        str += films[current[i]];
        str += '\n';
      }

      combinaisonMax = Tuple<std::string, int>(str, nbSatisfait);
    }
    return;
  }

  for (unsigned int i = pos; i <= tableau.taille() - k; i++)
  {
    current.ajouter(i);

    Tableau<int> nouveauxClients;
    int nouveauNbSatisfait = nbSatisfait;

    for (int j = 0; j < satisfait.taille(); j++)
    {
      if (!satisfait[j] && appreciation[i][j])
      {
        satisfait[j] = true;
        nouveauxClients.ajouter(j);
        nouveauNbSatisfait++;
      }
    }

    combinaison(tableau,
                k - 1,
                current,
                films,
                combinaisonMax,
                appreciation,
                satisfait,
                nouveauNbSatisfait,
                i + 1);

    for (int j = 0; j < nouveauxClients.taille(); j++)
    {
      satisfait[nouveauxClients[j]] = false;
    }

    current.enlever(current.taille() - 1);
  }
}

Tableau<Tableau<bool>> construction_tableau_client_film(const Tableau<std::string> &films, Tableau<Client> &clients)
{
  int taille_film = films.taille();
  int taille_clients = clients.taille();

  Tableau<Tableau<bool>> client_film;
  for (int i = 0; i < taille_film; i++)
  {
    Tableau<bool> tableau_clients;
    for (int j = 0; j < taille_clients; j++)
    {
      tableau_clients.ajouter(clients[j].veutEcouterFilm(films[i]));
    }
    client_film.ajouter(tableau_clients);
  }
  return client_film;
}

void tp2(const Tableau<std::string> &films, Tableau<Client> &clients,
         int nbsalles = 2)
{

  if (nbsalles == 1)
  {
    std::cout << uneSalleCinema(films, clients);
  }
  else
  {
    Tableau<int> current;
    Tuple<std::string, int> tuple("", -1);
    Tableau<Tableau<bool>> appreciation = construction_tableau_client_film(films, clients);
    Tableau<bool> satisfait;
    for (int i = 0; i < clients.taille(); i++)
    {
      satisfait.ajouter(false);
    }

    combinaison(films,
                nbsalles,
                current,
                films,
                tuple,
                appreciation,
                satisfait,
                0,
                0);
    std::cout << tuple.getI();
  }
}

int main(int argc, const char **argv)
{
  // Entrée:

  int nbsalles = 1;
  const char *nom_fichier = nullptr;

  // Traitement des arguments reçus en ligne de commande
  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
      nbsalles = atoi(argv[i] + 1);
    }
    else if (nom_fichier == nullptr)
    {
      nom_fichier = argv[i];
    }
    else
    {
      std::cout << "Erreur de syntaxe d'appel au programme!" << std::endl;
      return 1;
    }
  }

  Tableau<std::string> films;
  Tableau<Client> clients;

  // Appel à la fonction tp2
  if (nom_fichier != nullptr)
  {
    std::ifstream lecteurfichier(nom_fichier);
    if (lecteurfichier.fail())
    {
      std::cout << "Erreur d'ouverture du fichier '" << nom_fichier << "'"
                << std::endl;
      return 2;
    }
    lire(lecteurfichier, films, clients);
  }
  else
  {
    lire(std::cin, films, clients);
  }

  tp2(films, clients, nbsalles);
  return 0;
}
