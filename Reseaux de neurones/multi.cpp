#define N 8
#define M 7

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>



float w[M][N]=
{
    {0,0,0,0,0,0,0,0},
    {0,0,0,0.5,-1,0,0,0},
    {0,0,0,1.5,-2,0,0,0},
    {0,0,0,0,0,1,-1,0},
    {0,0,0,0,0,3,-4,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,-3}

};
float alpha=0.1;
float d=1;
float x[3]= {0,2,-1};
float in[M];
float delta[M];
float a[M+1];

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}
void alea(float w[M][N])
{
    int i,j;
    for(i=1; i<M; i++)
    {
        for(j=1; j<N; j++)
        {
            w[i][j]=rand_a_b(-1,1);

        }
    }
}


float g(float x)
{
    return 1/(1+exp(-x));
}

void retroPropagation(float x[3],float w[M][N],float delta[M+1])
{
   printf(" \n-------------------\n ");

    int i,j;
    for(i=1; i<3; i++)
    {
        a[i]=x[i];
    }

    for(j=3; j<=M; j++)
    {
        for(i=1; i<M; i++)
        {
            in[j]+=w[i][j]*a[i];
        }
        a[j]=g(in[j]);
    }
    for(j=1; j<=M; j++)
    {
        printf("a[%d]=%f\n",j,a[j]);
    }
    delta[M]=1-a[M];
    float sum=0;
    printf("\n ***************** \n");
    printf("delta[7]=%f\n",delta[M]);
    for(i=M-1; i>=3; i--)
    {
        for(j=1; j<=M; j++)
        {
            sum+=w[i][j]*delta[j];
        }
        delta[i]=g(in[i])*(1-g(in[i]))*sum;
        printf("delta[%d]=%f\n",i,delta[i]);
        sum=0;
    }
    printf("\n*************** \n");
//modification des poids
    for(i=1; i<M; i++)
    {
        for(j=1; j<=M; j++)
        {
            w[i][j]=w[i][j]+alpha*a[i]*delta[j];
        }
    }
//affichage des poids
printf(" Affichage des poids \n");
    for(i=1; i<M; i++)
    {
        for(j=1; j<=M; j++)
        {
            printf(" w[%d][%d]=%f\t",i,j,w[i][j]);
        }
        printf("\n");
    }

}
int main()
{
    do
    {
        retroPropagation(x,w,delta);
    }while(delta[M]<0.1);

}
