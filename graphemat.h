#define N 8
#include <limits.h>
#include "liste.h"
typedef int  booleen;
#define faux 0
#define vrai 1
typedef char NomSom[20];  // nom d'un sommet
#define INFINI INT_MAX

typedef int* Matrice;

typedef struct {
int somSuc; // pointeur sur le sommet successeur
int cout;
char  chemin[20];
int f;
} Dounia;

typedef struct {
  int      n;       // nombre de sommets
  int      nMax;    // nombre max de sommets
  booleen  value;   // graphe valué ou non
  NomSom*  nomS;    // noms des sommets
  Matrice  element; // existence d'un arc (i, j)
  Matrice  valeur;  // cout de l'arc (i, j)
  booleen* marque;  // sommet marqué (visité) ou non
} GrapheMat;

GrapheMat* creerGrapheMat     (int nMax, int value);
void       detruireGraphe     (GrapheMat* graphe);
void       ajouterUnSommet    (GrapheMat* graphe, NomSom nom);
void       ajouterUnArc       (GrapheMat* graphe, NomSom somD, NomSom somA, int cout);
void       ecrireGraphe       (GrapheMat* graphe);
void rechprofond (GrapheMat* graphe);
static void rechprofondeur (GrapheMat* graphe, int numSommet, char but[] );
void       parcoursProfond    (GrapheMat* graphe);
void parcoursLargeur(GrapheMat* graphe);
void largeur (GrapheMat* graphe, Liste* li, int numSommet,char but[]);
void       floyd              (GrapheMat* graphe);
void       parcoursProfondeurIteratif(GrapheMat* graphe);
void ExplorationUniforme (GrapheMat* graphe , int but1) ;
static void ajouterDsFilePrio (GrapheMat* graphe, Liste* file, int cout,int numSommet ,char * chemin,int but1) ;
//Liste* ppv( GrapheMat* probleme,int* cout);
void ppv(GrapheMat* probleme, char* retour[N], int a);
void deuxOptv1(char* tour[N], int i , int j, char* retour[N]);
<<<<<<< HEAD
void deuxOptv2(GrapheMat* probleme,char* z[N],int y);
=======
void deuxOptv2(GrapheMat* probleme);
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
void escaladeS(GrapheMat* probleme);
//void listToAr(Liste* li, char** l);
int coutCircuit(GrapheMat* probleme,char* tour[N]);
void escaladeC(GrapheMat* probleme);
void recuitS(GrapheMat* probleme);
void randomTour(GrapheMat* probleme, char* tour[N]);
void randomTou(int* tour);
