#define N 2 // nombre de couche
#define M 2 // taille de l'entree
#define P 1 // taille de la sortie


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>  

void retroPropagation(){
	srand(time(NULL));
	bool sortir=false;
	int i,j,k,z;
	int e[M], dd[P];
	float w[M][M][N],a[N][M],d[P],delta,delt[M][N]; //la sortie est de dim 1 => delta est de dimension 1 
	printf("Saisir l'entree");
	for( i=0; i<M; i++){ //saisie de l'entree
		scanf("%d",&e[i]);
	}
	printf("Saisir la sortie desiree dd");
	for( i=0; i<P; i++){ //saisie de la sortie desiree
		scanf("%d",&dd[i]);
	}
	for( k=0; k<N; k++){// le dernier calcul n'est pas pris en cons
		/*for( i=0; i<M;i++)
			for(j=0;j<M;j++){
				w[i][j][k]=rand()/(float)RAND_MAX;// remplissage aleatoire de w
			}*/
		for( i=0; i<M;i++)
			for(j=0;j<M;j++){
				printf("entrer w[%d][%d][%d]",i,j,k); scanf("%f",&w[i][j][k]);// remplissage manuelle de w
			}
		for(i=0; i<M;i++){
			a[k][i]=0;
			for(j=0; j<M; j++)
				if (k==0) a[k][i]+=(w[j][i][k]*e[j]); 
				else a[k][i]+=(w[j][i][k]*a[k-1][j]);
			a[k][i]= 1/(1+ exp(-a[k][i]));//printf("%.3f\n",a[k][i]);
		}
	}
	
		
	//calcul de la sortie
	for( i=0; i<M;i++)
	for(j=0;j<P;j++){
				printf("entrer w[%d][%d][%d]",i,j,k); scanf("%f",&w[i][j][k+1]);// manuelle
				//w[i][j][k+1]=rand()/(float)RAND_MAX;// remplissage aleatoire de w
			}
	
	for(i=0; i<P;i++){
			d[i]=0;
			for(j=0; j<M; j++)
				d[i]+=w[j][i][k+1]*a[N-1][j];
			d[i]= 1/(1+ exp(-d[i]));
		}
	
	//affichage
	printf("\n--------propagation--------\n");
	for(i=0; i<M;i++){
		for(j=0;j<N; j++)
			printf("% .3f		",a[j][i]);
		if(i<P) printf("% .3f		",d[i]);
		printf("\n");
		}
	printf("\n-----Les poids de propagation---\n");
	for(k=0; k<N+1;k++){
		printf("Couche %d\n",k+1);
		for(i=0; i<M;i++){
			for(j=0;j<M; j++)
				if(k<N)printf("w[%d][%d][%d] %.3f		",i,j,k,w[i][j][k]); else { printf("% .3f		",w[i][j][k]); sortir=true;}
			printf("\n");
			if(sortir) break;}
	}
	
	delta = dd[0]-d[0]; // la sortie est de dim 1 c'est pas la peine de faire une boucle 
	printf("delta = %.3f\n",delta);
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(i==0){
			delt[i][j]=a[N-1-i][j]*(1-a[N-i-1][j])*w[j][0][N-i]*delta;	printf(" %.3f %.3f",a[N-1-i][j],w[j][0][N-i]);
			printf("delt[%d][%d] = %.3f",i,j,delt[i][j]);}
			else{
				delt[i][j]=a[N-1-i][j]*(1-a[N-1-i][j]);
				for(int l=0;l<M;l++){
					z+=w[j][l][N-i]*delt[i-1][l];
				}
				delt[i][j]*=z;
				printf("delt [%d][%d]= %.3f",i,j,delt[i][j]);
			}
		}
	}
	
	printf("\n-----Les delta de la retropropagation---\n");
		for(i=0; i<N;i++){
			for(j=0;j<M; j++)
				printf("% .3f		",delt[i][j]);
			printf("\n");}
	}
	
		
		
		

int main(){
	retroPropagation();
}
