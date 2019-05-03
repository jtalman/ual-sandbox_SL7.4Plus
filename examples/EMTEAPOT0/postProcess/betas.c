#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793

int main (int argc, char*argv[])
{
 double x1typ=1.e-06;

 double R11,R21,R12,R22;
 double S11,S21,S12,S22;
 double Rtr=0;
 int numSP;// = processSP(1);
 double cosMu=0,dsc=0,alpha0=0,beta0=0;
 double det=0;
 double sinMu=0;
 double Mu=0,Mu_PR=0,Q=0;
 double alpha0_alternateSq=0;

 numSP = processSP(1);
 R11=SP1x[numSP-1]/x1typ;
 R21=SP1xP[numSP-1]/x1typ;
 printf("SP1 lines %d:  SP1x[numSP1-1]/x1typ  (R11) %+e\n",numSP,R11);
 printf("SP1 lines %d: SP1xP[numSP1-1]/x1typ  (R21) %+e\n",numSP,R21);

 numSP = processSP(2);
 S11=SP2x[numSP-1]/-x1typ;
 S21=SP2xP[numSP-1]/-x1typ;
 printf("SP2 lines %d:  SP2x[numSP2-1]/-x1typ (S11) %+e\n",numSP,S11);
 printf("SP2 lines %d: SP2xP[numSP2-1]/-x1typ (S21) %+e\n",numSP,S21);

 numSP = processSP(3);
 R12=SP3x[numSP-1]/x1typ;
 R22=SP3xP[numSP-1]/x1typ;
 printf("SP3 lines %d:  SP3x[numSP3-1]/x1typ  (R12) %+e\n",numSP,R12);
 printf("SP3 lines %d: SP3xP[numSP3-1]/x1typ  (R22) %+e\n",numSP,R22);

 numSP = processSP(4);
 S12=SP4x[numSP-1]/-x1typ;
 S22=SP4xP[numSP-1]/-x1typ;
 printf("SP4 lines %d:  SP4x[numSP4-1]/-x1typ (S12) %+e\n",numSP,S12);
 printf("SP4 lines %d: SP4xP[numSP4-1]/-x1typ (S22) %+e\n",numSP,S22);

 R11=(R11+S11)/2.;
 R21=(R21+S21)/2.;
 R12=(R12+S12)/2.;
 R22=(R22+S22)/2.;

 Rtr=R11+R22;
 det=R11*R22-R12*R21;
 printf("\ntrace %+e\n",Rtr);
 printf("determinant %+.17g\n\n",det);
 if(Rtr<-2.||Rtr>2.){printf("invalid implied angle mu!");exit(1);}

 cosMu=Rtr/2.;
 sinMu=sqrt(1.-cosMu*cosMu);
 beta0=R12/sinMu; 
 alpha0=(R11-R22)/2./sinMu;

 printf("cosMuX %+e\n",cosMu);
 printf("sinMuX %+e\n\n",sinMu);

 printf("alphaX %+e\n",alpha0);
 printf("betaX %+e\n\n",beta0);

 alpha0_alternateSq=-R21*beta0/sinMu-1.;
 printf("alphaX_alternate (from R21) %+e\n",sqrt(alpha0_alternateSq));
 printf("\n");

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
 printf("\n");

 return 0;
}
