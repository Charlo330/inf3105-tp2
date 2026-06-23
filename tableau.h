/* Squelette pour classe générique Tableau<T>.
 * Lab3 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab3/
 */

#if !defined(TABLEAU_INF3105_E26_)
#define TABLEAU_INF3105_E26_

#include <cassert>

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale = 4);
    Tableau(const Tableau&);
    ~Tableau();

    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;
    // Ajoute un element à la fin
    void           ajouter(const T& element);
    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index = 0);

    // Vide le tableau
    void           vider();
    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index = 0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element) const;

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    Tableau<T>&    operator= (const Tableau<T>& autre);
    bool           operator== (const Tableau<T>& autre) const;

  private:
    struct         ElementIndexe;
    T*             elements;
    int            nbElements;
    int            capacite;
};

// ---------- Définitions, modèles de -------------
// En C++, les définitions sont habituellement dans des fichiers sources .cpp.
// Les classes "template" sont souvent une exception à cette règle.
// Ces modèles devant être instanciés, on les mets dans un fichier .h.

template <class T>
struct Tableau<T>::ElementIndexe {
    T valeur;
    int indexOriginal;
};

template <class T>
Tableau<T>::Tableau(int capacite_initiale): nbElements(0), capacite(capacite_initiale){
    elements = new T[capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre): nbElements(autre.nbElements), capacite(autre.nbElements * 2) {
    elements = new T[capacite];

    for (int i = 0; i < nbElements; i++) {
        elements[i] = autre[i];
    }
}

template <class T>
Tableau<T>::~Tableau() {
    delete[] elements;
    elements = nullptr;
    capacite = 0;
    nbElements = 0;
}

template <class T>
int Tableau<T>::taille() const {
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item) {
    if (nbElements >= capacite && nbElements >= 0) {
        capacite = capacite * 2;
        T* t = new T[capacite];
        for (int i = 0; i < nbElements; ++i) {
            t[i] = elements[i];
        }

        delete[] elements;
        elements = t;
    }

    elements[nbElements] = item;
    nbElements++;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index) {
    assert(nbElements >= 0 && nbElements <= capacite);
    assert(index >= 0 && index <= nbElements);

    if(nbElements >= capacite) {
        capacite *= 2;
        T *tmp = new T[capacite];

        int i = 0;

        for(; i < index; ++i) {
            tmp[i] = elements[i];
        }
        for(; i < nbElements; ++i) {
            tmp[i+1] = elements[i];
        }

        delete[] elements;
        elements = tmp;
    } else {
        for (int i = nbElements; i > index; --i) {
            elements[i] = elements[i-1];
        }
    }

    elements[index] = element;
    ++nbElements;
}

template <class T>
void Tableau<T>::vider() {
    nbElements = 0;
}

template <class T>
void Tableau<T>::enlever(int index) {
    assert(nbElements >= 0 && nbElements <= capacite);
    assert(index >= 0 && index < nbElements);

    --nbElements;
    for(int i = index; i < nbElements; ++i)
        elements[i] = elements[i+1];
}

template <class T>
int Tableau<T>::chercher(const T& element) const {
    for (int i = 0; i < nbElements; i++) {
        if (elements[i] == element)
            return i;
    }
    return -1;
}

template <class T>
const T& Tableau<T>::operator[] (int index) const {
    assert(index >= 0 && index < nbElements);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index) {
    assert(index >= 0 && index < nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator= (const Tableau<T>& autre) {
    if (this == &autre) return *this;

    nbElements = autre.nbElements; 
    if(nbElements <= capacite / 4 || capacite <= nbElements) {
        capacite = (nbElements < 4) ? 4 : nbElements * 2;

        delete[] elements;
        elements = new T[capacite];
    }

    for(int i = 0; i < nbElements; ++i)
        elements[i] = autre.elements[i];

    return *this;
}

template <class T>
bool Tableau<T>::operator== (const Tableau<T>& autre) const {
    if(this == &autre) return true;
    
    if(nbElements != autre.nbElements) return false;

    for(int i = 0; i < nbElements; ++i) {
        if(elements[i] != autre.elements[i])
            return false;
    }

    return true;
}

#endif //define TABLEAU_INF3105_E26_
