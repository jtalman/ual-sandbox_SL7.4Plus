#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"                   // has arrays SP1x[1000],SP1xP[1000],...
double SP1x_N0,SP1xP_N0;                // one turn from origin values
double SP2x_N0,SP2xP_N0;
double SP3x_N0,SP3xP_N0;
double SP4x_N0,SP4xP_N0;

#define PI 3.141592653589793

int main (int argc, char*argv[]){
 double x1typ=1.e-06;

 double trace=0;

 int numSP;// = processSP(1);
 int numSP1,numSP2,numSP3,numSP4;

 double cosMu0=0,dsc=0,alpha0=0,beta0=0,gamma0=0;
 double det=0;

 double AbsSinMu0=0;
 double    sinMu0=0;

 double Mu0=0,Mu0_PMtw0=0,Q=0;
 double alpha0_alternate=0,alpha0_alternateSq=0;
 double Mtw0[3][3]={0,0,0,0,0,0,0,0,0};
 double zero=0,one=1,two=2,fac=1;

 double  Mtw0INV[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};
 double  PLR[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};
 double  PRL[3][3]={ {0,0,0}, {0,0,0}, {0,0,0}};

 numSP1 = processSP(1);
 numSP2 = processSP(2);if(numSP2!=numSP1){printf("inconsistency - exiting\n");exit(1);}
 numSP3 = processSP(3);if(numSP3!=numSP2){printf("inconsistency - exiting\n");exit(1);}
 numSP4 = processSP(4);if(numSP4!=numSP3){printf("inconsistency - exiting\n");exit(1);}
 numSP = numSP4;

 SP1x_N0= SP1x[numSP-1];    SP2x_N0 =SP2x[numSP-1];    Mtw0[1][1]= (SP1x_N0-SP2x_N0)/two/x1typ;
 SP1xP_N0=SP1xP[numSP-1];   SP2xP_N0=SP2xP[numSP-1];   Mtw0[2][1]=(SP1xP_N0-SP2xP_N0)/two/x1typ;
 SP3x_N0= SP3x[numSP-1];    SP4x_N0 =SP4x[numSP-1];    Mtw0[1][2]= (SP3x_N0-SP4x_N0)/two/x1typ;
 SP3xP_N0=SP3xP[numSP-1];   SP4xP_N0=SP4xP[numSP-1];   Mtw0[2][2]=(SP3xP_N0-SP4xP_N0)/two/x1typ; 

// Mtw0[1][1]=(SP1x[numSP-1]-SP2x[numSP-1])/two/x1typ;//printf("Mtw0[1][1]%e",Mtw0[1][1]);
// Mtw0[2][1]=(SP1xP[numSP-1]-SP2xP[numSP-1])/two/x1typ;//printf("Mtw0[2][1]%e",Mtw0[2][1]);
// Mtw0[1][2]=(SP3x[numSP-1]-SP4x[numSP-1])/two/x1typ;//printf("Mtw0[1][2]%e",Mtw0[1][2]);
// Mtw0[2][2]=(SP3xP[numSP-1]-SP4xP[numSP-1])/two/x1typ;//printf("Mtw0[2][2]%e",Mtw0[2][2]);

 printf("Array determined from  (scaled)\n");
  printf("SP1x_N0-SP2x_N0  = %+.1e ",Mtw0[1][1]);
  printf("SP3x_N0-SP4x_N0  = %+.1e ",Mtw0[1][2]);
  printf("\n");
  printf("SP1xP_N0-SP2xP_N0= %+.1e ",Mtw0[2][1]);
  printf("SP3xP_N0-SP4xP_N0= %+.1e ",Mtw0[2][2]);
  printf("\n");
//printArray(Mtw0);
//
 trace=traceArray(Mtw0);
 printf("trace                   %+.17e\n",trace);
 det=determinantArray(Mtw0);
 printf("determinant             %+.17e\n",det);
 printf("one - determinant       %+.17e\n",one-det);

 printf("\n*************************** ONE TURN FROM ORIGIN TWISS FUNCTIONS X **************************\n");
 printf("***************************** CHECKING Implied Angle mu *************************************\n");
// trace=-3;
// trace=+3;
 if(trace<-2.||trace>2.){
  printf("################### INVALID IMPLIED ANGLE MU - EXITING ######################\n\n");
  exit(1);
 }
 else{printf("****************************** VALID Implied Angle mu ***************************************\n");}
 printf("*************************** PROCEEDING ... **************************************************\n");

/*
 printf("scaling matrix\n");
 fac=sqrt(one/det);
 scaleArray(Mtw0,fac);
 trace=traceArray(Mtw0);
 printf("new trace               %+.17e\n",trace);
 det=determinantArray(Mtw0);
 printf("new determinant         %+.17e\n\n",det);
*/

 cosMu0=trace/two;
 AbsSinMu0=sqrt(one-cosMu0*cosMu0);
 if(Mtw0[1][2]<zero)sinMu0=-AbsSinMu0;
 else{sinMu0=+AbsSinMu0;}
 printf("cosMu0X                 %+.17e\n",cosMu0);
 printf("AbsSinMu0X              %+.17e\n",AbsSinMu0);
 printf("   sinMu0X              %+.17e\n\n",   sinMu0);

 beta0=Mtw0[1][2]/AbsSinMu0; 
 printf("beta0X                  %+.17e\n\n",beta0);

 alpha0=(Mtw0[1][1]-Mtw0[2][2])/two/AbsSinMu0;
 gamma0=(one+alpha0*alpha0)/beta0;
 alpha0_alternate=sqrt(gamma0*beta0-one);
 printf("alpha0X (from diagonal) %+.17e\n",alpha0);
 printf("alpha0X_alternate       %+.17e\n",alpha0_alternate);
 printf("(from Mtw021 ie gamma0X)\n\n");
 printf("gamma0X                 %+.17e\n\n",gamma0);

 Mu0_PMtw0=acos(cosMu0);
                                               // half integer tune ambiguity resolution
                                               // NOT full integer tune ambiguity
 if     (cosMu0>=0 && AbsSinMu0>=0){Mu0=Mu0_PMtw0;}       
 else if(cosMu0<=0 && AbsSinMu0>=0){Mu0=Mu0_PMtw0;}
 else if(cosMu0<=0 && AbsSinMu0<=0){Mu0=two*PI-Mu0_PMtw0;}
 else if(cosMu0>=0 && AbsSinMu0<=0){Mu0=two*PI-Mu0_PMtw0;}

 Q=Mu0/two/PI;
 printf("Mu0X                    %+.17e\n",Mu0);
 printf("QX (fractional)         %+.17e\n",Q);
 printf("\n");

 inverseArray(Mtw0,Mtw0INV);
// printf("printArray \n");printArray(Mtw0INV);

 multiplyArrays(Mtw0,Mtw0INV,PLR);
// printf("printArray \n");printArray(PLR);

 multiplyArrays(Mtw0INV,Mtw0,PRL);
// printf("printArray \n");printArray(PRL);

 printf("###################### NUMBER OF ELEMENTS TAKEN AS:\n\n");
 printf("                                  %d                   <<<<<<<<<<----------\n\n",numSP);
 printf("###################### NUMBER OF ELEMENTS\n\n");
 printf("This is to be used as input for executables in directory ./postProcess\n\n\n");
 return 0;
}
