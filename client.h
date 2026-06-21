#ifndef __CLIENT_H__
#define __CLIENT_H__ 

#include <iostream>
#include <string>

using namespace std;

class Client {
  public:
    // À compléter.

  private:
  	std::string nom;
    // À compléter.

  friend std::ostream& operator << (std::ostream&, const Client&);
  friend std::istream& operator >> (std::istream&, Client&);
};

#endif

