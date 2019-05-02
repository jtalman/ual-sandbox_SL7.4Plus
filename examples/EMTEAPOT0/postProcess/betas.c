#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793

int main (int argc, char*argv[])
{
 double x1typ=1.e-06;

 double R11,R21,R12,R22;
 double Rtr=0;
 int numSP;// = processSP(1);
 double cosMu=0,dsc=0,a0=0,b0=0;
 double det=0;
 double sinMu=0;
 double Mu=0,Mu_PR=0,Q=0;

 numSP = processSP(1);
 R11=SP1x[numSP-1]/x1typ;
 R21=SP1xP[numSP-1]/x1typ;
 printf("SP1 lines %d:  SP1x[numSP1-1]/x1typ (R11) %+e\n",numSP,R11);
 printf("SP1 lines %d: SP1xP[numSP1-1]/x1typ (R21) %+e\n",numSP,R21);

 numSP = processSP(3);
 R12=SP3x[numSP-1]/x1typ;
 R22=SP3xP[numSP-1]/x1typ;
 printf("SP3 lines %d:  SP3x[numSP3-1]/x1typ (R12) %+e\n",numSP,R12);
 printf("SP3 lines %d: SP3xP[numSP3-1]/x1typ (R22) %+e\n\n",numSP,R22);

/*
 Rtr=R11+R22;
 cosMu=Rtr/2.;
 det=1.-Rtr*Rtr/4.;
 if( (det<0) ){printf("X: Trying to take square root of a negative number!\n");exit(1);};
 b0=R12/sqrt(det); 
 sinMu=R21/b0;
 a0=(R11-R22)/2./sinMu;
*/

 Rtr=R11+R22;
 cosMu=Rtr/2.;
 dsc=1.-Rtr*Rtr/4.;
 if( (dsc<0) ){printf("X: Trying to take square root of a negative number!\n");exit(1);}
 else{ printf("'discriminant' %+.17g so mu can be inferred\n\n",dsc);}
 b0=R12/sqrt(dsc); 
 sinMu=R12/b0;
 a0=(R11-R22)/2./sinMu;

 det=R11*R22-R12*R21;

 printf("\ntrace %+e\n",Rtr);
 printf("determinant %+.17g\n\n",det);

 printf("betaX %+e\n",b0);
 printf("cosMuX %+e\n",cosMu);
 printf("sinMuX %+e\n",sinMu);
 printf("alphaX %+e\n",a0);

 Mu_PR=acos(cosMu);
                                               // half integer tune ambiguity resolution
                                               // NOT full integer tune ambiguity
 if     (cosMu>=0 && sinMu>=0){Mu=Mu_PR;}       
 else if(cosMu<=0 && sinMu>=0){Mu=Mu_PR;}
 else if(cosMu<=0 && sinMu<=0){Mu=2.*PI-Mu_PR;}
 else if(cosMu>=0 && sinMu<=0){Mu=2.*PI-Mu_PR;}

 Q=Mu/2./PI;
 printf("MuX %+e\n",Mu);
 printf("QX %+e\n",Q);

 return 0;
}
