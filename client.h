#ifndef __CLIENT_H__
#define __CLIENT_H__ 

#include <iostream>
#include <string>
#include "tableau.h"

using namespace std;

class Client {
  public:
    Client();
    bool veutEcouterFilm(const std::string) const;
    bool estSatisfait;

  private:
  	std::string nom;
    Tableau<std::string> *films;

  friend std::ostream& operator << (std::ostream&, const Client&);
  friend std::istream& operator >> (std::istream&, Client&);
};

#endif

