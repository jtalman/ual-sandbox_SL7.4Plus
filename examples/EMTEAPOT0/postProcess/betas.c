#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793

int main (int argc, char*argv[])
{
 double x1typ=1.e-06;

 double trace=0;
 int numSP;// = processSP(1);
 double cosMu0=0,dsc=0,alpha0=0,beta0=0,gamma0=0;
 double det=0;

 double AbsSinMu0=0;
 double    sinMu0=0;

 double Mu0=0,Mu0_PMtw=0,Q=0;
 double alpha0_alternate=0,alpha0_alternateSq=0;
 double Mtw[3][3];
 double zero=0,one=1,two=2,fac=1;

 printf("\n*************************** CHECKING Implied Angle mu **************************\n\n");

 numSP = processSP(1);
 numSP = processSP(2);
 numSP = processSP(3);
 numSP = processSP(4);

 Mtw[1][1]=(SP1x[numSP-1]-SP2x[numSP-1])/two/x1typ;//printf("Mtw[1][1]%e",Mtw[1][1]);
 Mtw[2][1]=(SP1xP[numSP-1]-SP2xP[numSP-1])/two/x1typ;//printf("Mtw[2][1]%e",Mtw[2][1]);

 Mtw[1][2]=(SP3x[numSP-1]-SP4x[numSP-1])/two/x1typ;//printf("Mtw[1][2]%e",Mtw[1][2]);
 Mtw[2][2]=(SP3xP[numSP-1]-SP4xP[numSP-1])/two/x1typ;//printf("Mtw[2][2]%e",Mtw[2][2]);
 printf("printArray \n");printArray(Mtw);
 trace=traceArray(Mtw);
 printf("traceArray\n      %+.17e\n",trace);
 det=determinantArray(Mtw);
 printf("determinantArray\n      %+.17e\n",det);

 if(trace<-2.||trace>2.){printf("invalid implied angle mu!\n");exit(1);}
 else{printf("*************************** VALID Implied Angle mu **************************\n");}
 printf("*************************** PROCEEDING ... **************************\n");

 printf("scaling matrix\n");
 fac=sqrt(one/det);
 scaleArray(Mtw,fac);
 trace=traceArray(Mtw);
 printf("new trace\n      %+.17e\n",trace);
 det=determinantArray(Mtw);
 printf("new determinant\n      %+.17e\n\n",det);

 cosMu0=trace/two;
 AbsSinMu0=sqrt(one-cosMu0*cosMu0);
 if(Mtw[1][2]<zero)sinMu0=-AbsSinMu0;
 else{sinMu0=+AbsSinMu0;}
 printf("cosMu0X    %+.17e\n",cosMu0);
 printf("AbsSinMu0X %+.17e\n",AbsSinMu0);
 printf("   sinMu0X %+.17e\n\n",   sinMu0);

 beta0=Mtw[1][2]/AbsSinMu0; 
 printf("beta0X     %+.17e\n\n",beta0);

 alpha0=(Mtw[1][1]-Mtw[2][2])/two/AbsSinMu0;
 gamma0=(one+alpha0*alpha0)/beta0;
 alpha0_alternate=sqrt(gamma0*beta0-one);
 printf("alpha0X (from diagonal)                   %+.17e\n",alpha0);
 printf("alpha0X_alternate (from Mtw21 ie gamma0X) %+.17e\n\n",alpha0_alternate);
 printf("gamma0X %+.17e\n\n",gamma0);

 Mu0_PMtw=acos(cosMu0);
                                               // half integer tune ambiguity resolution
                                               // NOT full integer tune ambiguity
 if     (cosMu0>=0 && AbsSinMu0>=0){Mu0=Mu0_PMtw;}       
 else if(cosMu0<=0 && AbsSinMu0>=0){Mu0=Mu0_PMtw;}
 else if(cosMu0<=0 && AbsSinMu0<=0){Mu0=two*PI-Mu0_PMtw;}
 else if(cosMu0>=0 && AbsSinMu0<=0){Mu0=two*PI-Mu0_PMtw;}

 Q=Mu0/two/PI;
 printf("Mu0X            %+.17e\n",Mu0);
 printf("QX (fractional) %+.17e\n",Q);
 printf("\n");

 return 0;
}
