#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"
#include <time.h>
#include <math.h>


clock_t begin, end;
double time5;


static int d=0;
booleen  grapheDetruit = vrai;
static  bool trouveS=false, trouve=false;

// remise à zéro du tableau de marquage
static void razMarque (GrapheMat* graphe)
{

    for (int i=0; i<graphe->n; i++) graphe->marque [i] = faux;
}

GrapheMat* creerGrapheMat (int nMax, int value)
{
    // allocation de graphe
    GrapheMat* graphe  = (GrapheMat*) malloc (sizeof (GrapheMat));
    graphe->n       = 0;
    graphe->nMax    = nMax;
    graphe->value   = value; // value : vrai si le graphe est valué
    graphe->nomS    = (NomSom*)  malloc (sizeof(NomSom)  *nMax);
    graphe->marque  = (booleen*) malloc (sizeof(booleen) *nMax);
    graphe->element = (int*)     malloc (sizeof(int)*nMax*nMax);
    graphe->valeur  = (int*)     malloc (sizeof(int)*nMax*nMax);
    // initialisation par défaut
    for (int i=0; i<nMax; i++)
    {
        for (int j=0; j<nMax; j++)
        {
            graphe->element [i*nMax+j] = faux;
            graphe->valeur  [i*nMax+j] = INFINI;
        }
    }
    razMarque (graphe);
    grapheDetruit = faux;
    return graphe;
}


// désallocation d'un graphe
void detruireGraphe (GrapheMat* graphe)
{
    free (graphe->nomS);
    free (graphe->marque);
    free (graphe->element);
    free (graphe->valeur);
    free (graphe);
    grapheDetruit = vrai;
}

static int rang (GrapheMat* graphe, NomSom nom)
{
    int      i      = 0;
    booleen  trouve = faux;
    while ( (i<graphe->n) && !trouve)
    {
        trouve = strcmp (graphe->nomS [i], nom) == 0;
        if (!trouve) i++;
    }
    return trouve ? i : -1;
}

void ajouterUnSommet (GrapheMat* graphe, NomSom nom)
{
    if (rang (graphe, nom) == -1)
    {
        if (graphe->n < graphe->nMax)
        {
            strcpy (graphe->nomS [graphe->n++], nom);
        }
        else
        {
            printf ("\nNombre de sommets > %d\n", graphe->nMax);
        }
    }
    else
    {
        printf ("\n%s déjà défini\n", nom);
    }
}

void ajouterUnArc (GrapheMat* graphe, NomSom somD, NomSom somA, int cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);
    int rg = rang (graphe, somA);
    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
}

void ecrireGraphe (GrapheMat* graphe)
{
    if (grapheDetruit == vrai)
    {
        printf ("Le graphe a ete detruit ou n'est pas encore cree\n");
    }
    else
    {
        int nMax = graphe->nMax;
        for (int i=0; i<graphe->n; i++) printf ("%s ", graphe->nomS[i]);
        printf (";\n");
        for (int i=0; i<graphe->n; i++)
        {
            printf ("\n%s : ", graphe->nomS[i]);
            for (int j=0; j<graphe->n; j++)
            {
                if (graphe->element [i*nMax+j] == vrai)
                {
                    printf ("%s ", graphe->nomS[j]) ;
                    if (graphe->value)
                    {
                        printf (" (%3d) ", graphe->valeur [i*nMax+j] );
                    }
                }
            }
            printf (";");
        }
    }
}

static void profondeur (GrapheMat* graphe, int numSommet)
{
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("%s\n", graphe->nomS [numSommet]);

    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            profondeur (graphe, i);
        }
    }
}


void parcoursProfond (GrapheMat* graphe)
{
    razMarque (graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) profondeur (graphe, i);
    }
}

//recherche profondeur

static void rechprofondeur (GrapheMat* graphe, int numSommet, char but[] )
{
       if(!trouveS){
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("->%s", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i]&&!trouve )
        {
             if(strcmp(graphe->nomS [i],but)==0){
                printf("->%s (Noeud but) ",but);
                trouveS=true;
             }
            rechprofondeur (graphe, i,but);

        }
    }
}}
void rechprofond (GrapheMat* graphe)
{

    clock_t begin, end;
    double time_spent;
    razMarque (graphe);
    char str[20];
    printf("Entrez le sommet but : \n ");
    scanf("%s", str);
    printf("Chemin suivi par le parcous :   ");



    begin = clock();

    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) rechprofondeur (graphe, i,str);
    }
    if(!trouveS){

        printf("\nLe noeud %s est INTROUVABLE\n",str);
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nLe temps pris :  %f",time_spent);


}
// recherche largeur

 void largeur (GrapheMat* graphe, Liste* li, int numSommet,char but[])
{
    int nMax = graphe->nMax;
    NomSom* extraite=NULL;
    insererEnFinDeListe (li,graphe->nomS[numSommet]);
    graphe->marque [numSommet]=true;
  printf("Chemin pris par le parcours  :   ");

    while (!listeVide (li) )
    {
     extraite = (NomSom*) extraireEnTeteDeListe (li);
        if(strcmp(*extraite,but)==0){

                printf("->%s (Noeud but) ",but);
                return;
             }
    numSommet = rang (graphe,*extraite);
  printf("->%s",*extraite);
    for (int i=0; i<graphe->nMax; i++)
    {
         if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
           insererEnFinDeListe(li,graphe->nomS[i]);
           graphe->marque[i] = vrai;
        }
    }
}
printf("\nLe noeud but %s est INTROUVABLE. ",but);
}

void parcoursLargeur(GrapheMat* graphe){
clock_t begin, end;
double time_spent;

razMarque(graphe);
 Liste* li = creerListe();
 char str[20];

   printf("Entrez le sommet but : \n");
   scanf("%s", str);
   begin = clock();
 for (int i=0; i<graphe->n; i++)
    {
        if(!graphe->marque[i]){
            largeur(graphe,li,i,str);}
            break;
    }

end = clock();
time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("\n Le temps pris :  %f",time_spent);
}


//
static void ecrireEtape (Matrice a, Matrice p, int k, int ns, int nMax)
{
    printf ("Passage par le sommet numéro %d\n", k);

    for (int i=0; i<ns; i++)
    {
        for (int j=0; j<ns; j++)
        {
            if (a [i*nMax+j]==INFINI)
            {
                printf (" %3s", "*");

            }
            else
            {
                printf (" %3d", a [i*nMax+j]);
            }
        }
        printf ("%6s", " ");
        for (int j=0; j<ns; j++)
        {
            printf ("%3d", p [i*nMax+j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

// initialiser les matrices a et p à partir de graphe
static void initFloyd (GrapheMat* graphe, Matrice* a, Matrice* p)
{
    int nMax = graphe->nMax;

    Matrice ta = (int*) malloc (sizeof(int)*nMax*nMax);
    Matrice tp = (int*) malloc (sizeof(int)*nMax*nMax);


    for (int i=0; i<graphe->n; i++)
    {
        for (int j=0; j<graphe->n; j++)
        {
            if(i==j){
                ta [i*nMax+j]=0;
                tp [i*nMax+j] = i;
            }
            else{
                ta [i*nMax+j] = graphe->valeur [i*nMax+j];
                tp [i*nMax+j] = i;
            }
        }
    }
    *a = ta;
    *p = tp;
}

void floyd (GrapheMat* graphe)
{
    Matrice a, p;
    int n = graphe->n;
    int nMax = graphe->nMax;

    initFloyd (graphe, &a, &p);


    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if ( (a [i*nMax+k] != INFINI) &&
                        (a [k*nMax+j] != INFINI) &&
                        (a [i*nMax+k] + a [k*nMax+j] < a [i*nMax+j]) )
                {
                    a [i*nMax+j] = a [i*nMax+k] + a [k*nMax+j];
                    p [i*nMax+j] = p [k*nMax+j];
                }
            }
        }
        ecrireEtape (a, p, k, n, nMax);
    }
}

// profondeur itérative


static void profondeurIteratif (GrapheMat* graphe, int numSommet,int d,char but[])
{ if(!trouveS){
     if(strcmp(graphe->nomS[numSommet],but)==0){

                printf("->%s (Noeud but) ",but);
               trouveS=true;
             }

       else if(d==0){
     printf ("->%s", graphe->nomS [numSommet]);

     graphe->marque [numSommet] = vrai;
     }
        else {
            if (d>0){
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
printf ("->%s", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {

        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {

            profondeurIteratif(graphe, i, d-1,but);

        }

    }
     }}
}}

void parcoursProfondeurIteratif(GrapheMat* graphe){
 char str[20];
 int niveau;
 printf("Entrez le sommet but : \n ");
 scanf("%s", str);
  printf("Entrez le niveau maximal ");
 scanf("%d", &niveau);
  razMarque (graphe);
Liste* li = creerListe();
printf("Chemin suivi par le parcous :   ");
  d=0;
    for ( d=0; d<niveau; d++)
    {razMarque (graphe);
 for (int i=0; i<graphe->n; i++)
    {

        if(!graphe->marque[i])
            profondeurIteratif(graphe,i,d,str);

            break;

    }
}
 if(!trouveS){
        trouveS=false;
        printf("\nLe noeud %s est INTROUVABLE",str);
    }
    trouveS=false;
}
//cout uniforme
static void ajouterDsFilePrio (GrapheMat* graphe, Liste* file, int cout,int numSommet ,char * chemin,int but)
{
	// ajouter dans la file les sommet marquee

	graphe->marque [numSommet] = vrai;
	Dounia* nouveau = (Dounia*) malloc (sizeof (Dounia) );
	nouveau->somSuc = numSommet;
	nouveau->cout=cout;
	if(!strcmp(graphe->nomS[numSommet],graphe->nomS[but]))
	{
		graphe->marque [numSommet] = false;
	}
	strcpy(nouveau->chemin,chemin);
	insererEnOrdre (file, nouveau);
	//printf("%d",cout);




}
/*void ExplorationUniforme (GrapheMat* graphe , int but)

{
	int nMax = graphe->nMax;
	razMarque (graphe);
	Liste* file = creerListe();
	clock_t begin,end;
	begin=clock();
	for (int i=0; i<graphe->n; i++)
	{
		if (!graphe->marque[i])
		{
			//printf (" %s ", graphe->nomS [i]);
			ajouterDsFilePrio (graphe, file, 0,i,"A",but);
			while (!listeVide(file))

			{
				Dounia* succes = (Dounia*) extraireEnTeteDeListe (file);
				printf (" %s \n", (char*)graphe->nomS [succes->somSuc]);
				//printf (" %d ", succes->cout);

				int s = succes->somSuc;
				int precedent=succes->cout;
				char * ch=succes->chemin;
				for (int j=0; j<graphe->n; j++)

				{
					Dounia* copyc = (Dounia*) malloc (sizeof (Dounia) );
					copyc->cout=succes->cout;
					strcpy(copyc->chemin,succes->chemin);
					copyc->somSuc=succes->somSuc;
					if ( (graphe->element [s*nMax+j] == vrai) && !graphe->marque[j] )
					{

						ch = strcat(copyc->chemin,graphe->nomS[j]);
						ajouterDsFilePrio (graphe, file,precedent+graphe->valeur [s*nMax+j],j,ch,but);
					}
				}
				if(!strcmp( graphe->nomS[succes->somSuc],graphe->nomS[but]))
				{
					if(succes->cout!=0)
					{
		printf("Chemin : %s  Cout :%d ",succes->chemin,succes->cout);
					}
				}

			}

		}
	}
	end=clock();
	//printf("%d ",graphe->valeur[graphe->nMax+5]);
	time5= (double)(end-begin)/CLOCKS_PER_SEC;
	printf("le temps CPU : %f10\n",time5);

}


//d'une liste à un tableau

/*void listToAr(Liste* li, char* l[N]){
	Element* elt1= li->premier;
	for( int i=0; i<li->nbElt; i++){
		l[i] = (char*) elt1->reference;
		elt1 = elt1->suivant;
			}
}*/
// fonction calculant le cout d'un circuit donné CA MARCHE !!
int coutCircuit(GrapheMat* probleme,char* tour[N]){
	int tmp, tmp1=-1,tmp2=0, cout=0, n=probleme->nMax;
	for(int i=1 ; i<N; i++){
		for(int j=0; j<n;j++){
			if(tour[i] == probleme->nomS[j]){
				tmp=tmp2;
				tmp2=j;
				tmp1=tmp;break;}}
		if(tmp1!=-1 && tmp2!=-1){
			cout+= probleme->valeur[tmp1*n+tmp2];
			}
		}
	return cout;


}
/*int coutCircuit(GrapheMat* probleme,char* tour[N]){
	int tourc[N], n= probleme->n, cout;
	for(int i=0;i<N;i++)
		for(int j=0;j<n;j++)
			if(tour[i]==probleme->nomS[j])
				tourc[i]=j;
	for(int i=1;i<N;i++){
		cout+= probleme->valeur[n*tourc[i-1]+tourc[i]];
	}
	return cout;

}*/
// plus proche voisin avec les listes CA MARCHE!!
/*Liste* ppv( GrapheMat* probleme,int *cout){
	char* sommetDebut= (char*)probleme->nomS[0];
	int nMax= probleme -> nMax, n = probleme->n;
	Liste* li = creerListe();
	int valeur=INFINI, j=0,cmp=0,k=0;
	insererEnFinDeListe(li,sommetDebut);
	while(cmp < n-1){
		for( int i=0;i<n; i++){
	if (probleme->element [i*probleme->nMax+j] == vrai)
			if((valeur > probleme->valeur[k*nMax+i]) && !chercherUnObjetBis(li,probleme->nomS[i]) && (probleme->valeur[k*nMax+i]!= 0)){
				valeur = probleme->valeur[k*nMax+i];
				j= i;
			}
		}
		insererEnFinDeListe(li,probleme->nomS[j]);
		cout += valeur ;
		k=j;
		valeur= INFINI ;
		cmp++;
	}
	cout += probleme->valeur[k*nMax];
	insererEnFinDeListe(li,sommetDebut);
	//printf("Le cout du ppv : %d\n",cout);
	return li;
}*/
bool find(char* tour[N],char* objet){
	for(int i=0; i<N;i++)
		if(tour[i]== objet) return true;
	return false;
}
//PPV version tableau CA MAARCHE
void ppv(GrapheMat* probleme, char* tour[N], int a ){
	char* sommetDebut= (char*)probleme->nomS[a];
	int nMax= probleme->nMax, n= probleme->n, valeur= INFINI,l=a;
	tour[0]= sommetDebut;
	for(int k=1;k<n;k++){
		for(int i=0;i<n;i++){
			if (probleme->element [i*probleme->nMax+a] == vrai)
				if((valeur > probleme->valeur[l*nMax+i]) && find(tour,(char*)probleme->nomS[i])==false && (probleme->valeur[l*nMax+i]!= 0)){
					valeur = probleme->valeur[l*nMax+i];
					a= i;
			}
		}
		tour[k]= (char*)probleme->nomS[a];
		l=a;
		valeur= INFINI;
		}
		tour[n]= sommetDebut;

	}




//2opt v1 CA MARCHE !!
void deuxOptv1(char* tour[N], int i , int j, char* retour[N]){
	int tmp,n=N;
	if(j<i) { tmp=i; i=j ; j=tmp; }
	tmp=j;
	for(int k= 0; k< n; k++){
		if(k<i || k>j){
			retour[k]=tour[k];
			printf("'%s'",retour[k]);
			if(k<n-1) printf("->");
			else printf("\n");
		}
		else if ((k >=i) && (k<=j)){
			retour[k]= tour[tmp];
			printf("'%s'",retour[k]); printf("->");
			tmp--;
		}
	}
}

//2opt v2 CA MARCHE !!


void deuxOptv2(GrapheMat* probleme,char* z[N],int y){
	int cout;
	int nMax= probleme->n;
	char* l[N] ,*retour[N];
	ppv(probleme,l,y);
	cout=coutCircuit(probleme,l);
	int i,j,cmp=0,k;
	for (i= 1; i<N-2;i++)
		for (j=i+1;j<N-1;j++)
			if(i!=1 || j!=N-2){
				if( i<j){
				printf("%d i= %d,j= %d- ",++cmp,i,j);
				deuxOptv1(l,i,j,retour);
				printf("	cout= %d", coutCircuit(probleme,retour));
				if(cout>coutCircuit(probleme,retour)){
					cout=coutCircuit(probleme,retour);
					for(k=0;k<N;k++){
						z[k]=retour[k];}
				}
				printf("\n");}
			}


}



//escalade simple CA MAARCHE!!
void escaladeS(GrapheMat* probleme){

	bool out= false;
	int nMax= probleme->n;
	char* l[N] ,*retour[N], *precedent[N];
	ppv(probleme,retour,0);
	int cout=coutCircuit(probleme,retour);
	printf("cout initial %d \n",cout);
	ppv(probleme,l,0);
	ppv(probleme,precedent,0);
	int i,j,cmp=0;
	for (i= 1; i<N-2;i++){
		for (j=i+1;j<N-1;j++)
			if(i!=1 || j!=N-2){
				if( i<j){
				deuxOptv1(l,i,j,retour);
				if(coutCircuit(probleme,retour)>cout){
					printf("\n ******Le cout min = %d*****\n", cout);
					printf("le chemin avec le cout min \n");
					for(int i=0; i<N; i++){
						printf("'%s'", precedent[i]);
						if(i<N-1) printf("->");
						}
					printf("\n");
					out=true;break;
				}
				else
				cout=coutCircuit(probleme,retour);
				deuxOptv1(l,i,j,precedent);
				}
			}
		if(out) break;}


	}


	// escalade Complet

	void escaladeC(GrapheMat* probleme){
	bool out= false;
	int nMax= probleme->n;
	char* l[N] ,*retour[N], *precedent[N];
	for(int k=0; k<N;k++){
		ppv(probleme,retour,k);
		int cout=coutCircuit(probleme,retour);
		printf("cout initial %d \n",cout);
		ppv(probleme,l,k);
		ppv(probleme,precedent,k);
		int i,j,cmp=0;
		for (i= 1; i<N-2;i++){
			for (j=i+1;j<N-1;j++)
				if(i!=1 || j!=N-2){
					if( i<j){
					deuxOptv1(l,i,j,retour);
					if(coutCircuit(probleme,retour)>cout){
						printf("\n ******Le cout min = %d*****\n", cout);
						printf("le chemin avec le cout min \n");
						for(int i=0; i<N; i++){
							printf("'%s'", precedent[i]);
							if(i<N-1) printf("->");
							}
						printf("\n");
						out=true;break;
					}
					else
					cout=coutCircuit(probleme,retour);
					deuxOptv1(l,i,j,precedent);
					}
				}
			if(out) break;}

	}
}




//random circuit


void randomTour(GrapheMat* probleme, char* tour[N]){
	srand(time(NULL));
	int r[N];
	randomTou( r);
	for(int i=0;i<N;i++){
		tour[i]= probleme->nomS[r[i]];
	}
}



//tablea de rand integer
void randomTou( int* tab){
int i,x,k;
	for (i=0; i<(N-1); i++){

		x=rand()%(N-1);
		if (i < 1){
			tab[i] = rand()%(N-1);
		}
		else{
			for (k=0; k<i; k++) {

				if ( x != tab[k]){

				}
				else{
					x=rand()%(N-1);
					k=-1;

				}
			}
		tab[i]=x;
		}
	}
	tab[i]=tab[0];
printf("\n");
}




// ca marche
void recuitS(GrapheMat* probleme){
	int tempD=100, cout= INFINI,i,k,cmp=0;
	float factD=0.93;
	int p1,p2;
	float p3;
	char* tab1[N], *tab2[N], *tab3[N];


	while(tempD>0 && cmp<N-1){
		ppv(probleme,tab1,cmp);
		for( i=0; i<N;i++)
			tab2[i]=tab1[i];
		for(k=0;k<N;k++)
			printf("'%s'->",tab2[k]);
		printf("%d",coutCircuit(probleme,tab2));
		printf("\n");
		deuxOptv2(probleme,tab2,cmp);
		if(coutCircuit(probleme,tab2)<coutCircuit(probleme,tab1)){
			for(i=0;i<N;i++)
				tab1[i]=tab2[i];
			if(cout>coutCircuit(probleme,tab2)){
				cout= coutCircuit(probleme,tab2);
				for(k=0;k<N;k++)
					tab3[k]=tab2[k];

			}
		}
		else {
			if(exp(-(coutCircuit(probleme,tab2)-coutCircuit(probleme,tab1))/tempD)>0.5)
				for(i=0;i<N;i++)
					tab1[i]=tab2[i];
		}
		tempD*=factD; cmp++;
	}
	printf("Le circuit optimal: \n");
	for(k=0;k<N;k++)
		printf("'%s'->",tab3[k]);
	printf("\n");
	printf("Le cout optimal: %d",cout);
}

//recuit simulé v1= avec 2opt simple !!! aléatoire ? ???





//2-opt v1
//void deuxOptv1(GrapheMat* probleme,int i){




//ppv version tableau ca marche pas
/*bool chercherObjet(char* li, char* c){
	bool a;
	for(int i=0;i<sizeof(li);i++)
		if(strcmp(li[i],c))
			a= true;
<<<<<<< HEAD
	return a;
=======
	return a; 
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
}

void ppv( GrapheMat* probleme,char* li){
	char* sommetDebut= (char*)probleme->nomS[0];
	int nMax= probleme->nMax, n = probleme->n, cout=0;
	int valeur=INFINI, j=0,cmp=0,k=0;
	li[0]=sommetDebut;
	while(cmp < n-1){
		for( int i=0;i<n; i++){
	if (probleme->element [i*probleme->nMax+j] == vrai)
			if((valeur > probleme->valeur[k*nMax+i]) && !strchr(li,(int*)probleme->nomS[i]) && (probleme->valeur[k*nMax+i]!= 0)){
<<<<<<< HEAD

=======
				
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
				valeur = probleme->valeur[k*nMax+i];
				j= i;
			}
		}
		li[cmp+1]=&(char*)probleme->nomS[j];
		cout += valeur ;
		k=j;
		valeur= INFINI ;
		cmp++;
	}
	cout += probleme->valeur[k*nMax];
	strcpy(li[cmp+1],sommetDebut);
	//printf("Le cout du ppv : %d\n",cout);

}*/




// 2opt sans cout

/*void deuxOptv2(GrapheMat* probleme){
	Liste* init=ppv(probleme);
	Liste* tour = init;// reference tour->courant->reference
	Objet* tmp;
	int n=nbElement(ppv(probleme)),cmp1=0,cmp2=0;
	Element* elt1= tour->premier ;
	Element* elt2= psuivant(psuivant(init->premier)) ;

<<<<<<< HEAD

=======
	
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
	while(cmp1 < n-4){
		while(cmp2 <n-4-cmp1){
			if( elt1->reference != elt2->reference && elt1->reference != psuivant(elt2)->reference && psuivant(elt1)->reference != elt2->reference && psuivant(elt1)->reference != psuivant(elt2)->reference){
				printf("elt1  ( %s, %s)\n",(char*)elt1->reference,(char*)psuivant(elt1)->reference);
				tmp= elt2->reference;
				elt2->reference= psuivant(elt1)->reference;
				psuivant(elt1)->reference= tmp;
				printf("------Tour : %d--------\n",cmp1+cmp2+1);
				listerListe(tour);
				printf("-----------------------\n");
<<<<<<< HEAD

	}

=======
				
	}		
			
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d
			*tour=*init;
			elt2= psuivant(elt2);
			cmp2++;
			elt1= init->premier ;
			printf("boucle2\n");

			}
		elt1=psuivant(elt1);
		cmp1++;
		printf("boucle1\n");
<<<<<<< HEAD

=======
		
>>>>>>> f5e5ac748d0c93143ce8c1a9488f996d51e5f25d


/*void deuxOpt(GrapheMat* probleme){
	int n=nbElement(ppv(probleme)),i;
	Element* elt1=ppv(probleme)->premier;
	char* l;
	char* tmp;
	for( i=0; i<n; i++){
		l[i] = *(char*) elt1->reference;
		elt1 = elt1->suivant;
			}
	char* r=l;// reference = initial
	for( i=0;i<n-2;i++)
		for(int j = i+2;j<n;j++)
			if( l[i]!= l[j] && l[i]!= l[j+1] && l[i+1]!= l[j] && l[i]!= l[j]  ) {
				*tmp=l[i+1];
				l[i+1]=l[i];
				l[j]=*tmp;
				for( i=0; i<n; i++){
				printf("%s->",(char*)l[i]);}
				l=r;
<<<<<<< HEAD

			}
}

*/



