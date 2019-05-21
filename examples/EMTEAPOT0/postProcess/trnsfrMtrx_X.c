#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793

double  M_L[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};
double  M_N[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};
double  M_R[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};

int main (int argc, char*argv[]){
 int numSP;
 int i;
 double x1typ=1.e-06;

 double trace=0;
 int numSP1=0,numSP2=0,numSP3=0,numSP4=0;
 double cosMu0=0,dsc=0,alpha0=0,beta0=0,gamma0=0;
 double det=0;

 double AbsSinMu0=0;
 double    sinMu0=0;

 double Mu0=0,Mu0_PMtw0=0,Q=0;
 double alpha0_alternate=0,alpha0_alternateSq=0;
 double Mtw0[3][3]={0,0,0,0,0,0,0,0,0};
 double zero=0,one=1,two=2,fac=1;

 numSP=atoi(argv[1]);
 i=atoi(argv[2]);

 printf("Processing X Transfer Matrix at index %d\n",i);

 numSP1 = processSP(1);printf("# lines %d\n",numSP1);if(numSP!=numSP1){printf("wrong numSP1\n");exit(1);}
 numSP2 = processSP(2);printf("# lines %d\n",numSP2);if(numSP!=numSP2){printf("wrong numSP2\n");exit(1);}
 numSP3 = processSP(3);printf("# lines %d\n",numSP3);if(numSP!=numSP3){printf("wrong numSP3\n");exit(1);}
 numSP4 = processSP(4);printf("# lines %d\n",numSP4);if(numSP!=numSP4){printf("wrong numSP4\n");exit(1);}

 return 0;
}
