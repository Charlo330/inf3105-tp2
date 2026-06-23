
#include "client.h"

Client::Client(): estSatisfait(false), nom("") {
    this->films = new Tableau<std::string>();
}

bool Client::veutEcouterFilm(const std::string film) const {
    return this->films->chercher(film) != -1;
}

std::istream& operator >> (std::istream& is, Client& c){
    is >> c.nom;

    int n;
    std::string s;
    is >> n;

    for(int i=0;i<n;i++) {
        is >> s;
        c.films->ajouter(s);
    }
    
    return is;
}


std::ostream& operator << (std::ostream& os, const Client& c) {
	// À compléter.

	return os;
}
