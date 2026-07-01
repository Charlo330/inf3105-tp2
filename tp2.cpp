/* INF3105 / TP2 */
#include "client.h"
#include "tableau.h"
#include "tuple.h"
#include <fstream>
#include <iostream>

using namespace std;

void trierFilmsParPopularite(Tableau<int> &ordreFilms,
                             Tableau<int> &populariteFilms)
{
  for (int i = 0; i < ordreFilms.taille() - 1; ++i)
  {
    int indiceMax = i;
    for (int j = i + 1; j < ordreFilms.taille(); ++j)
    {
      if (populariteFilms[j] > populariteFilms[indiceMax])
      {
        indiceMax = j;
      }
    }

    if (indiceMax != i)
    {
      int filmTmp = ordreFilms[i];
      ordreFilms[i] = ordreFilms[indiceMax];
      ordreFilms[indiceMax] = filmTmp;

      int populariteTmp = populariteFilms[i];
      populariteFilms[i] = populariteFilms[indiceMax];
      populariteFilms[indiceMax] = populariteTmp;
    }
  }
}

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

void combinaison(const Tableau<std::string> &films,
                 const Tableau<int> &ordreFilms,
                 const Tableau<int> &populariteFilms,
                 const Tableau<int> &meilleurScorePossible,
                 const Tableau<Tableau<int>> &clientsParFilm,
                 int k,
                 int pos,
                 Tableau<int> &current,
                 Tuple<std::string, int> &combinaisonMax,
                 Tableau<int> &satisfait,
                 int nbSatisfait)
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

  if (pos + k > ordreFilms.taille())
  {
    return;
  }

  if (nbSatisfait + meilleurScorePossible[pos + k] - meilleurScorePossible[pos] <= combinaisonMax.getJ())
  {
    return;
  }

  for (int i = pos; i <= ordreFilms.taille() - k; i++)
  {
    int filmId = ordreFilms[i];
    current.ajouter(filmId);

    int nouveauNbSatisfait = nbSatisfait;
    const Tableau<int> &clientsDuFilm = clientsParFilm[filmId];

    for (int j = 0; j < clientsDuFilm.taille(); j++)
    {
      int clientId = clientsDuFilm[j];
      if (satisfait[clientId] == 0)
      {
        nouveauNbSatisfait++;
      }
      satisfait[clientId]++;
    }

    combinaison(films,
                ordreFilms,
                populariteFilms,
                meilleurScorePossible,
                clientsParFilm,
                k - 1,
                i + 1,
                current,
                combinaisonMax,
                satisfait,
                nouveauNbSatisfait);

    for (int j = 0; j < clientsDuFilm.taille(); j++)
    {
      int clientId = clientsDuFilm[j];
      satisfait[clientId]--;
    }

    current.enlever(current.taille() - 1);
  }
}

Tableau<Tableau<int>> construction_clients_par_film(const Tableau<std::string> &films, const Tableau<Client> &clients)
{
  int taille_film = films.taille();
  int taille_clients = clients.taille();

  Tableau<Tableau<int>> clients_par_film;
  for (int i = 0; i < taille_film; i++)
  {
    Tableau<int> clients_du_film;
    for (int j = 0; j < taille_clients; j++)
    {
      if (clients[j].veutEcouterFilm(films[i]))
      {
        clients_du_film.ajouter(j);
      }
    }
    clients_par_film.ajouter(clients_du_film);
  }
  return clients_par_film;
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
    Tableau<Tableau<int>> clientsParFilm = construction_clients_par_film(films, clients);
    Tableau<int> ordreFilms;
    Tableau<int> populariteFilms;
    Tableau<int> meilleurScorePossible;
    Tableau<int> satisfait;

    for (int i = 0; i < films.taille(); i++)
    {
      int popularite = 0;
      for (int j = 0; j < clients.taille(); j++)
      {
        if (clientsParFilm[i].chercher(j) != -1)
        {
          popularite++;
        }
      }

      ordreFilms.ajouter(i);
      populariteFilms.ajouter(popularite);
    }

    trierFilmsParPopularite(ordreFilms, populariteFilms);

    meilleurScorePossible.ajouter(0);
    for (int i = 0; i < populariteFilms.taille(); i++)
    {
      meilleurScorePossible.ajouter(meilleurScorePossible[i] + populariteFilms[i]);
    }

    for (int i = 0; i < clients.taille(); i++)
    {
      satisfait.ajouter(0);
    }

    combinaison(films,
                ordreFilms,
                populariteFilms,
                meilleurScorePossible,
                clientsParFilm,
                nbsalles,
                0,
                current,
                tuple,
                satisfait,
                0);
    std::cout << tuple.getI();
    std::cout << tuple.getJ() << '\n';
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
