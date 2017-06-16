/* liste.cpp
   Ce module de gestion de listes est très général
   et indépendant des applications.
   Il gère des listes simples d'éléments avec tête de liste */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

// fonctions locales au module
static Element* creerElement    ();
static void     insererApres    (Liste* li, Element* precedent, Objet* objet);
static void     insererApres    (Liste* li, Element* precedent, Objet* objet,Objet* priority);
static Objet*   extraireApres   (Liste* li, Element* precedent);
static Element* elementCourant  (Liste* li);

// comparer deux chaînes de caractères
// fournit <0 si ch1 < ch2; 0 si ch1=ch2; >0 sinon
static int comparerCar (Objet* objet1, Objet* objet2) {
  return strcmp ((char*)objet1,(char*)objet2);
}

static char* toChar (Objet* objet) {
  return (char*) objet;
}

// initialiser la liste pointée par li (cas général)
void initListe (Liste* li, int type, char* (*toString) (Objet*),
			   int (*comparer) (Objet*, Objet*)) {
  li->premier  = NULL;
  li->dernier  = NULL;
  li->courant  = NULL;
  li->nbElt    = 0;
  li->type     = type;
  li->toString = toString;
  li->comparer = comparer;
}

// initialisation par défaut
void initListe (Liste* li) {
  initListe (li, NONORDONNE, toChar, comparerCar);
}

Liste* creerListe (int type, char* (*toString) (Objet*),
		   int (*comparer) (Objet*, Objet*)) {
  Liste* li = (Liste*) malloc (sizeof (Liste));
  initListe (li, type, toString, comparer);
  return li;
}

Liste* creerListe (int type) {
  return creerListe (type, toChar, comparerCar);
}

Liste* creerListe () {
  return creerListe (NONORDONNE, toChar, comparerCar);
}

// la liste est-elle vide ?
booleen  listeVide (Liste* li) {
  return li->nbElt == 0;
}

// fournir le nombre d'éléments dans la liste
int nbElement (Liste* li) {
  return li->nbElt;
}

// INSERER UN OBJET DANS UNE LISTE

// insérer objet en tête de la liste li
// l'objet est repéré par le champ reference de l'élément de la liste
void insererEnTeteDeListe (Liste* li, Objet* objet) {
  Element* nouveau   = creerElement();
  nouveau->reference = objet;
  nouveau->suivant   = li->premier;
  li->premier        = nouveau;
  if (li->dernier == NULL) li->dernier = nouveau;
  li->nbElt++;
}
void insererEnTeteDeListe (Liste* li, Objet* objet,Objet* priority) {
  Element* nouveau   = creerElement();

  nouveau->reference = objet;
  nouveau->priority = priority;
  nouveau->suivant   = li->premier;
  li->premier        = nouveau;
  if (li->dernier == NULL) li->dernier = nouveau;
  li->nbElt++;
}
// insérer un objet en fin de la liste li
void insererEnFinDeListe (Liste* li,  Objet* objet) {
  insererApres (li, li->dernier, objet);
}
void insererEnFinDeListe (Liste* li,  Objet* objet, Objet* priority) {
  insererApres (li, li->dernier, objet,priority);
}

// PARCOURS DE LISTE

// se positionner sur le premier élément de la liste li
void ouvrirListe (Liste* li) {
  li->courant = li->premier;
}

// a-t-on atteint la fin de la liste li ?
booleen finListe (Liste* li) {
  return li->courant==NULL;
}

// fournir un pointeur sur l'objet courant de la liste li,
// et se positionner sur le suivant qui devient le courant
Objet* objetCourant (Liste* li) {
  Element* ptc = elementCourant (li);
  return ptc==NULL ? NULL : ptc->reference;
}


void listerListe (Liste* li) {
  ouvrirListe (li);
  while (!finListe (li)) {
    Objet* objet = objetCourant (li);
    printf ("%s ->", li->toString (objet));
  }
}

// lister la liste li;
// f est une fonction passée en paramètre
// et ayant un pointeur de type quelconque.
void listerListe (Liste* li, void (*f) (Objet*)) {
  ouvrirListe (li);
  while (!finListe (li)) {
    Objet* objet = objetCourant (li);
    f (objet);  // appliquer la fonction f() à objet
  }
}


// fournir un pointeur sur l'objet "objetCherche" de la liste li;
// NULL si l'objet n'existe pas
Objet* chercherUnObjet (Liste* li, Objet* objetCherche) {
  booleen trouve = faux;
  Objet* objet;       // pointeur courant
  ouvrirListe (li);
  while (!finListe (li) && !trouve){
    objet  = objetCourant (li);
    trouve = li->comparer (objetCherche, objet) == 0;
  }
  return trouve ? objet : NULL;
}
bool chercherUnObjetBis (Liste* li, Objet* objetCherche) {
  bool trouve = faux;
  Objet* objet;       // pointeur courant
  ouvrirListe (li);
  while (!finListe (li) && !trouve){
    objet  = objetCourant (li);
    trouve = li->comparer (objetCherche, objet) == 0;
  }
  return trouve ;
}


//  UN OBJET D'UNE LISTE

// extraire l'objet en tête de la liste li
Objet* extraireEnTeteDeListe (Liste* li) {
  Element* extrait = li->premier;
  if (!listeVide(li)) {
    li->premier = li->premier->suivant;
    if (li->premier==NULL) li->dernier=NULL; // Liste devenue vide
    li->nbElt--;
  }
  return extrait != NULL ? extrait->reference : NULL;
}
Objet* extraireEnTeteDeListeBis (Liste* li) {
  Element* extrait = li->premier;
  if (!listeVide(li)) {
    li->premier = li->premier->suivant;
    if (li->premier==NULL) li->dernier=NULL; // Liste devenue vide
    li->nbElt--;
  }
  return extrait != NULL ? extrait : NULL;
}
// extraire l'objet en fin de la liste li
Objet* extraireEnFinDeListe (Liste* li) {
  Objet* extrait;
  if (listeVide(li)) {
    extrait = NULL;
  } else if (li->premier == li->dernier) {  // un seul élément
    extrait = extraireEnTeteDeListe (li);
  } else {
    Element* ptc = li->premier;
    while (ptc->suivant != li->dernier) ptc = ptc->suivant;
    extrait = extraireApres (li, ptc);
  }
  return extrait;
}

// extraire de la liste li, l'objet pointé par objet
booleen extraireUnObjet (Liste* li, Objet* objet) {
  Element* precedent = NULL;
  Element* ptc       = NULL;

  // repère l'élement précédent
  booleen trouve = faux;
  ouvrirListe (li);
  while (!finListe (li) && !trouve) {
    precedent = ptc;
    ptc       = elementCourant (li);
    trouve = (ptc->reference == objet) ? vrai : faux;
  }
  if (!trouve) return faux;

  Objet* extrait = extraireApres (li, precedent);
  return vrai;
}

// parcours de liste avec destruction de chaque élément
void detruireListe (Liste* li) {
  ouvrirListe (li);
  while (!finListe (li)) {
    Element* ptc = elementCourant (li);
    //free (ptc->reference);  // si on veut détruire les objets de la liste
    free (ptc);
  }
  initListe (li);
}

// recopie l2 dans l1 et initialise l2
void  recopierListe (Liste* l1, Liste* l2) {
  detruireListe (l1);
  *l1 = *l2; // on recopie les têtes de listes
  initListe (l2);
}


// FONCTIONS LOCALES AU MODULE

// créer un élément de liste
static Element* creerElement () {
  return (Element*) malloc (sizeof (Element));
  //return new Element();
}

// insérer  dans la liste li, objet après precedent
// si precedent est NULL, insérer en tête de liste
static void insererApres (Liste* li, Element* precedent, Objet* objet) {
  if (precedent == NULL) {
    insererEnTeteDeListe (li, objet);
  } else {
    Element* nouveau   = creerElement();
    nouveau->reference = objet;

    nouveau->suivant   = precedent->suivant;
    precedent->suivant = nouveau;
    if (precedent == li->dernier) li->dernier = nouveau;
    li->nbElt++;
  }
}

static void insererApres (Liste* li, Element* precedent, Objet* objet,Objet* priority) {
  if (precedent == NULL) {
    insererEnTeteDeListe (li, objet,priority);
  } else {
    Element* nouveau   = creerElement();
    nouveau->reference = objet;

     nouveau->priority = priority;
    nouveau->suivant   = precedent->suivant;
    precedent->suivant = nouveau;
    if (precedent == li->dernier) li->dernier = nouveau;
    li->nbElt++;
  }
}


// Extraire l'objet de li se trouvant après l'élément precedent;
// si precedent vaut NULL, on extrait le premier de la liste;
// retourne NULL si l'objet à extraire n'existe pas
static Objet* extraireApres (Liste* li, Element* precedent) {
  if (precedent == NULL) {
    return extraireEnTeteDeListe (li);
  } else {
    Element* extrait = precedent->suivant;
    if (extrait != NULL) {
      precedent->suivant = extrait->suivant;
      if (extrait == li->dernier) li->dernier = precedent;
      li->nbElt--;
    }
    return extrait != NULL ? extrait->reference : NULL;
  }
}


// fournir un pointeur sur l'élément courant de la liste li,
// et se positionner sur le suivant qui devient le courant
static Element* elementCourant (Liste* li) {
  Element* ptc = li->courant;
  if (li->courant != NULL) {
    li->courant = li->courant->suivant;
  }
  return ptc;
}
static Element* elementCourantBis (Liste* li) {
  Element* ptc = li->courant;

  return ptc;
}

static Element* ppremier (Liste* li) {
  return li->premier;
}

//static Element* pdernier (Liste* li) {
//  return li->dernier;
//}

Objet* pDernier (Liste* li) {
  return li->dernier == NULL ? NULL : li->dernier->reference;
}

 Element* psuivant (Element* elt) {
  return elt!=NULL ? elt->suivant : NULL;
}


// LISTE ORDONNEE

// objet1 et objet2 sont-ils en ordre ?
static booleen enOrdre (Objet* objet1, Objet* objet2, booleen ordreCroissant,
                 int (*comparer) (Objet*, Objet*)) {
  booleen ordre = comparer (objet1, objet2) < 0;
  if (!ordreCroissant) ordre = !ordre;
  return ordre;
}

// la fonction comparer est passée en paramètre
// et dépend du type de l'objet inséré dans la liste
void insererEnOrdre (Liste* li, Objet* objet) {
  if (listeVide (li) ) {   // liste vide
    insererEnTeteDeListe (li, objet);
    //printf ("insertion dans liste vide\n");
  } else {
    Element* ptc = li->premier;
    if ( enOrdre (objet, ptc->reference, li->type==1, li->comparer) ) {
      // insertion avant le premier élément
      //printf ("insertion en tête de liste non vide\n");
      insererEnTeteDeListe (li, objet);
    } else {    // insertion en milieu ou fin de liste
      //printf ("insertion en milieu ou fin de liste non vide\n");
      booleen  trouve = faux;
      Element* prec   = NULL;
      while (ptc != NULL && !trouve) {
        prec   = ptc;
        ptc    = ptc->suivant;
        if (ptc!=NULL) trouve = enOrdre (objet, ptc->reference, li->type==1, li->comparer);
      }
      // insertion en milieu de liste ou fin de liste
      insererApres (li, prec, objet);
    }
  }
}
void insererEnOrdre (Liste* li, Objet* objet, Objet* priority) {
  if (listeVide (li) ) {   // liste vide
    insererEnTeteDeListe (li, objet,priority);
    //printf ("insertion dans liste vide\n");
  } else {
    Element* ptc = li->premier;
    if ( enOrdre (priority, ptc->priority, li->type==1, li->comparer) ) {
      // insertion avant le premier élément
      //printf ("insertion en tête de liste non vide\n");
      insererEnTeteDeListe (li, objet, priority);
    } else {    // insertion en milieu ou fin de liste
      //printf ("insertion en milieu ou fin de liste non vide\n");
      booleen  trouve = faux;
      Element* prec   = NULL;
      while (ptc != NULL && !trouve) {
        prec   = ptc;
        ptc    = ptc->suivant;
        if (ptc!=NULL) trouve = enOrdre (priority, ptc->priority, li->type==1, li->comparer);
      }
      // insertion en milieu de liste ou fin de liste
      insererApres (li, prec, objet,priority);
    }
  }
}
