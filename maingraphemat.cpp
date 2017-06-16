
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#include "graphemat.h"
#include "liregraphe.h"

typedef GrapheMat Graphe;


int menu () {

  printf ("\n\nGRAPHES avec matrices\n\n");

  printf ("0 - Fin du programme\n");
  printf ("1 - Creation a partir d'un fichier\n");
  printf ("\n");
  printf ("2 - Initialisation d'un graphe vide\n");
  printf ("3 - Ajout d'un sommet\n");
  printf ("4 - Ajout d'un arc\n");
  printf ("\n");
  printf ("5 - Liste des sommets et des arcs\n");
  printf ("6 - Destruction du graphe\n");
  printf ("7 - Parcours en profondeur d'un graphe\n");
  printf("8 - Recherche en profondeur d'un sommet\n");
  printf("9 - Recherche en largeur d'un sommet\n");
  printf("10 - Recherche en profondeur iterative d'un sommet\n");
  printf("11 - Recherche cout uniforme\n");
  printf ("\n");
  printf("12 - Floyd \n");
  printf("13-  ppv\n");
  printf("14-  2opt v1\n");
  printf("15-  2opt v2 \n");
  printf("16-  Escalade Simple \n");
  printf("17-  Escalade Complet \n");
  printf("18-  Recuit simule simple \n");
  printf("19-  Recuit simule complet \n");
  printf ("\n");
  printf ("\n");
  printf ("Votre choix ? ");
  int cod; scanf ("%d", &cod); getchar();
  printf ("\n");
  return cod;
}
int main () {
  Graphe* graphe;
  booleen fini = faux;
  while (!fini) {
    switch ( menu() ) {
    case 0:
      fini = vrai;
      break;
    case 1: {  // création à partir d'un fichier
      printf ("Nom du fichier contenant le graphe ? ");
      char nomFe [50];
      strcpy (nomFe, "graphe.txt");
      FILE* fe = fopen (nomFe, "r");
      if (fe == NULL) {
        perror (nomFe);
      } else {
        graphe = lireGraphe (fe, 20); // 20 sommets maximum
        fclose (fe);
      }
      } break;
   case 2: {             // création d’un graphe vide
      printf ("Nombre maximum de sommets ? ");
      int nMaxSom; scanf  ("%d", &nMaxSom);
      printf ("0) non valué; 1) graphe valué ? ");
      int value; scanf ("%d", &value);

      graphe = creerGrapheMat (nMaxSom, value);

    } break;
    case 3: {  // ajouter un sommet
      printf ("Nom du sommet à insérer ? ");
      NomSom somD; scanf  ("%s", somD);
      ajouterUnSommet (graphe, somD);
    } break;
    case 4: {  // ajouter un arc
      printf ("Nom du sommet de départ ? ");
      NomSom somD; scanf  ("%s", somD);
      printf ("Nom du sommet d'arrivée ? ");
      NomSom somA; scanf  ("%s", somA);
      int cout;
      if (graphe->value) {
        printf ("Cout de la relation ? ");
        scanf ("%d", &cout);
      } else {
        cout = 0;
      }
      ajouterUnArc (graphe, somD, somA, cout);
    } break;
    case 5:
      ecrireGraphe (graphe);
      break;
    case 6:
      detruireGraphe (graphe);
      break;
    case 7:
      parcoursProfond (graphe);
      break;
    case 8:
      rechprofond (graphe);
      break;
     case 9:
     parcoursLargeur(graphe);
      break;
    case 10:
     parcoursProfondeurIteratif(graphe);
      break;
    case 11:
      int but;
      printf("Entrer le but (entier)\n");
      scanf("%d",&but);
      //ExplorationUniforme(graphe,but);
      break;

    case 12:
     if (graphe->value) {
        printf ("\nLes plus courts chemins\n\n");
          floyd (graphe);
      } else {
        printf ("Graphe non valué\n");
      }
      break;
    case 13:{
	char* d[N];
	ppv(graphe,d,0);
	for(int i=0; i<N; i++){
			printf("'%s'", d[i]);
			if(i<N-1) printf("->");
			}
		printf("\n");
		printf("Le cout de ce circuit est : %d", coutCircuit(graphe,d));}
	break;
	
    case 14: {
	char* tour[N];
	char* retour[N] ;
	ppv(graphe,tour,0);
	for(int i=0; i<N; i++){
		printf("'%s'", tour[i]);
		if(i<N-1) printf("->");
		}
	printf("\n");
	printf("------2-Opts------- \n");
	deuxOptv1(tour,1,5,retour);
	printf("\n");
	printf("Le cout de ce circuit est : %d", coutCircuit(graphe,retour));
	}
	break;

    case 15:{
<<<<<<< HEAD
    char* z[N];
    int i;
	printf("------La liste des voisins------- \n");
	deuxOptv2(graphe,z,0);
	printf("Le chemin optimal est \n");
	for(i=0; i<N; i++){
		printf("'%s'", z[i]);
		if(i<N-1) printf("->");
		}
	printf("Le cout optimal est %d\n",coutCircuit(graphe,z));
	
	
=======
	printf("------La liste des voisins------- \n");
	deuxOptv2(graphe);
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
	}break;
	
	case 16:{
		printf("------Escalade Simple------- \n");
		escaladeS(graphe);
		}break;
		
	case 17:{
		printf("------Escalade Complet------- \n");
		escaladeS(graphe);
		}break;
		
	case 18:{
		
		}break;
		
	case 19:{
		recuitS(graphe);
		
		}break;
	case 20: {
		char* tour[N];
		randomTour(graphe, tour);
		for(int i=0; i<N; i++){
		printf("'%s'", tour[i]);
		if(i<N-1) printf("->");
		}
	}break;
	case 21:{
		int tour[N];
		randomTou(tour);
		for(int i=0; i<N; i++){
		printf("'%d'", tour[i]);
		if(i<N-1) printf("->") ; 
		}
		
	}break;

    }   // switch
    if (!fini) {
      printf ("\n\nTaper Return pour continuer\n");
      getchar();
    }
  }

return 0;
}
