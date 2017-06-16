#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

// liste.h


#define faux   0
#define vrai   1
typedef int    booleen;

typedef void Objet;

#define NONORDONNE  0
#define CROISSANT   1
#define DECROISSANT 2

// un élément de la liste
typedef struct element {
  Objet*          reference;
  Objet*          priority;
  // référence un objet (de l'application)
  struct element* suivant;     // élément suivant de la liste
} Element;

// le type Liste
typedef struct {
  Element* premier; // premier élément de la liste
  Element* dernier; // dernier élément de la liste
  Element* courant; // élément en cours de traitement (parcours de liste)
  int      nbElt;   // nombre d'éléments dans la liste
  int      type;    // 0:simple, 1:croissant, 2:décroissant
  char*    (*toString) (Objet*);
  int      (*comparer) (Objet*, Objet*);
} Liste;

void     initListe              (Liste* li, int type, char* (*toString) (Objet*),
				 int (*comparer) (Objet*, Objet*) );
void     initListe              (Liste* li);
Liste*   creerListe             (int type, char* (*toString) (Objet*),
				 int (*comparer) (Objet*, Objet*) );
Liste*   creerListe             (int type);
Liste*   creerListe             ();

booleen  listeVide              (Liste* li);
int      nbElement              (Liste* li);

void     insererEnTeteDeListe   (Liste* li, Objet* objet);
void     insererEnFinDeListe    (Liste* li, Objet* objet);
void     insererEnTeteDeListe   (Liste* li, Objet* objet, Objet* priority);
void     insererEnFinDeListe    (Liste* li, Objet* objet, Objet* priority);
// parcours de liste
void     ouvrirListe            (Liste* li);
booleen  finListe               (Liste* li);
Objet*   objetCourant           (Liste* li);
void     listerListe            (Liste* li);
void     listerListe            (Liste* li, void (*f) (Objet*));
Objet*   chercherUnObjet        (Liste* li, Objet* objetCherche);
bool   chercherUnObjetBis        (Liste* li, Objet* objetCherche);
char*   chercherPath        (Liste* li, Objet* objetCherche);
Objet*   extraireEnTeteDeListe  (Liste* li);
Objet*   extraireEnTeteDeListeBis  (Liste* li);
Objet*   extraireEnFinDeListe   (Liste* li);
booleen  extraireUnObjet        (Liste* li, Objet* objet);

void     detruireListe          (Liste* li);
void     recopierListe          (Liste* l1, Liste* l2);

//Element* pPremier             (Liste* li);
//Element* pDernier             (Liste* li);
//Objet*   pDernier             (Liste* li);
Element* psuivant             (Element* elt);


// LISTE ORDONNEE
void     insererEnOrdre         (Liste* li, Objet* objet);
void     insererEnOrdre         (Liste* li, Objet* objet, Objet* priority);



#endif // LISTE_H_INCLUDED
