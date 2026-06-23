/*
  INF3105 - Structures de données et algorithmes
  UQAM / Département d'informatique
*/

#if !defined(__PILE_H_26E_)
 #define __PILE_H_26E_

#include "assert.h"

template <class T>
class Pile {
  public:
    Pile();// si on défini pas le constructeur par copie, le compilateur le fait pour nous. Et 
    Pile(const Pile& other);
    ~Pile();

    void empiler(const T&);
    void depiler(T& out);  // Depiler et copier le sommet dans out.
    T depiler();

    bool vide() const {return !sommet;}
    void vider();
  private:
    class Cellule {
      public:
        Cellule(const T& e, Cellule* c = nullptr);
        T contenu;
        Cellule* suivante;
    };

    Cellule* sommet;
};

template<class T>
Pile<T>::Pile(const Pile<T>& other) : sommet(nullptr) {
    // Cas d'une pile vide
    if (other.sommet == nullptr)
        return;

    // Copier la première cellule
    sommet = new Cellule(other.sommet->contenu);

    Cellule* courantThis = sommet;
    Cellule* courantOther = other.sommet;

    // Copier les cellules suivantes
    while (courantOther->suivante != nullptr) {
        courantOther = courantOther->suivante;
        courantThis->suivante = new Cellule(courantOther->contenu);
        courantThis = courantThis->suivante;
    }
}

template <class T>
Pile<T>::Pile():sommet(nullptr) { }

template <class T>
Pile<T>::~Pile() {
  vider();
}

template <class T>
void Pile<T>::vider() {
  while(!vide())
    depiler();
}

template <class T>
Pile<T>::Cellule::Cellule(const T& e, Cellule* c) : contenu(e), suivante(c) {}

template <class T>
void Pile<T>::empiler(const T& e) {
  sommet = new Cellule(e, sommet);
  assert(sommet);
}

template <class T>
T Pile<T>::depiler() {
  assert(sommet);

  T contenu = sommet->contenu;
  Cellule* suivante = sommet->suivante;
  delete sommet;
  sommet = suivante;
  return contenu;
}

template <class T>
void Pile<T>::depiler(T& e) {
  e = depiler();
}

#endif
