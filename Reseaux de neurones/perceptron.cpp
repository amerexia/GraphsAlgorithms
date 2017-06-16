#define N 4
#define NBRPOIDS 2
#define TETA 0.1
#define NU 0.1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	int calculerSortie(double w[NBRPOIDS],int e[NBRPOIDS]){
		double a=0;
		for(int i=0;i<NBRPOIDS; i++){
			a+= w[i]*e[i];
		}
		a-=TETA;
		if(a>0) a=1;
		else a= 0;
		return a;
}
void modifierPoids(double* w,int d[NBRPOIDS],int a[N],int e[NBRPOIDS],int j){
	for(int i=0; i< NBRPOIDS;i++){
		w[i]+=NU*(d[j]-a[j])*e[i];
}
}
bool sortir(int d[N], int a[N]){
	for(int i=0; i<N; i++)
		if(d[i]!=a[i])
			return false;
	return true;
		
}

void perceptron(){
	double w[NBRPOIDS] = {0.3,-0.1};
	int e[N][NBRPOIDS]={{0,0},{0,1},{1,0},{1,1}};
	int d[N]={0,0,0,1};
	int a[N];
	int cmp=0;
	bool fini=false;
	printf("e1	e2	d	w1	w2	x	w1	w2\n");
	printf("---------------------------------------------------------------------\n");
	while(!fini){
		for( int i=0; i<N;i++){
			a[i]= calculerSortie(w,e[i]);
			printf("%d	%d	%d	%.1f	%.1f	%d",e[i][0],e[i][1],d[i],w[0],w[1],a[i]);
			if(a[i]!= d[i]){
				modifierPoids(w,d,a,e[i],i);
			}
			if(sortir(d,a))	fini=true;
			printf("	%.1f	%.1f\n",w[0],w[1]);
			
		}
		printf("---------------------------------------------------------------------\n");
	}
}

 int main(){
	perceptron();
 }
	
