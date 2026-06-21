
#include "client.h"

std::istream& operator >> (std::istream& is, Client& c){
    is >> c.nom;
    // À compléter.
    int n;
    std::string s;
    is >> n;
    for(int i=0;i<n;i++)
        is >> s;
    
    return is;
}


std::ostream& operator << (std::ostream& os, const Client& c) {
	// À compléter.

	return os;
}
