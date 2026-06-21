/* Squelette pour classe générique Tableau<T>.
 * Lab3 + TP1 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/tp1/
 */

#if !defined(TABLEAU_H_3105)
#define TABLEAU_H_3105

#include <cassert>

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau&);
    ~Tableau();

    // Ajoute un element à la fin
    void           ajouter(const T& element);
    // Vide le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index=0);

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element) const;

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

    // ----------------- Fonctionnalités spécifiques au TP1 ------------
    // Retourne une copie du tableau, mais sans doublons.
    Tableau<T> sans_doublons(bool garderPremier=true) const;
    // Supprime les doublons du tableau et retourne le nombre d'occurrences supprimées.
    int supprimer_doublons(bool garderPremier=true);
    // -----------------------------------------------------------------
    
    
  private:
    T*             elements;
    int            nbElements;
    int            capacite;
};


// ---------- Définitions, modèles de -------------
// En C++, les définitions sont habituellement dans des fichiers sources .cpp.
// Les classes "template" sont souvent une exception à cette règle.
// Ces modèles devant être instanciés, on les mets dans un fichier .h.


template <class T>
Tableau<T>::Tableau(int capacite_)
{
    // À compléter
    elements = new T[1024]; // cette ligne n'est peut-être pas bonne.
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    // À compléter
}

template <class T>
Tableau<T>::~Tableau()
{
    // À compléter
}

template <class T>
int Tableau<T>::taille() const
{
    // À compléter
    return 0;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
    // À compléter
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    // À compléter
}

template <class T>
void Tableau<T>::enlever(int index)
{
    // À compléter
}

template <class T>
int Tableau<T>::chercher(const T& element) const
{
    // À compléter
    // Voir la fonction Tableau<T>::contient() dans les notes de cours (Section 4.7).
    // Il suffit de l'adapter pour retourner la position au lieu d'un booléen.
    return -1;
}

template <class T>
void Tableau<T>::vider()
{
    // À compléter
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
    // À compléter
    return elements[0];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    // À compléter
    return elements[0];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    // À compléter
    return *this;
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    // À compléter
    return false;
}

// Retourne une copie du tableau, mais sans doublons.
template <class T>
Tableau<T> Tableau<T>::sans_doublons(bool garderPremier) const {
    // À compléter
    Tableau<T> resultat;
    return resultat;
}

// Supprime les doublons du tableau et retourne le nombre d'occurrences supprimées.
template <class T>
int Tableau<T>::supprimer_doublons(bool garderPremier) {
    // À compléter
    return 0;
}


#endif //define TABLEAU_H_3105
