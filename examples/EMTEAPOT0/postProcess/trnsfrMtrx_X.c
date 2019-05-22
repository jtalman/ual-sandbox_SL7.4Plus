#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793
double SP1x_N0,SP1xP_N0;                // one turn from origin values
double SP2x_N0,SP2xP_N0;
double SP3x_N0,SP3xP_N0;
double SP4x_N0,SP4xP_N0;

double SP1x_i,SP1xP_i;                  // i_th element from origin values
double SP2x_i,SP2xP_i;
double SP3x_i,SP3xP_i;
double SP4x_i,SP4xP_i;

double MX_0i   [3][3]={0,0,0,0,0,0,0,0,0};
double MX_0N0  [3][3]={0,0,0,0,0,0,0,0,0};
double MX_0iInv[3][3]={0,0,0,0,0,0,0,0,0};

double MXtw_0  [3][3]={0,0,0,0,0,0,0,0,0};
double traceMXtw_0,determinatMXtw_0;

double MXtw_i  [3][3]={0,0,0,0,0,0,0,0,0};
double traceMXtw_i,determinatMXtw_i;

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
 double zero=0,one=1,two=2,fac=1;

 numSP=atoi(argv[1]);
 i=atoi(argv[2]);

 printf("Processing X Transfer Matrix at index %d\n",i);

 numSP1 = processSP(1);printf("# lines %d\n",numSP1);if(numSP!=numSP1){printf("wrong numSP1\n");exit(1);}
 numSP2 = processSP(2);printf("# lines %d\n",numSP2);if(numSP!=numSP2){printf("wrong numSP2\n");exit(1);}
 numSP3 = processSP(3);printf("# lines %d\n",numSP3);if(numSP!=numSP3){printf("wrong numSP3\n");exit(1);}
 numSP4 = processSP(4);printf("# lines %d\n",numSP4);if(numSP!=numSP4){printf("wrong numSP4\n");exit(1);}

 SP1x_N0= SP1x[numSP-1];    SP2x_N0 =SP2x[numSP-1];    MXtw_0[1][1]= (SP1x_N0-SP2x_N0)/two/x1typ;
 SP1xP_N0=SP1xP[numSP-1];   SP2xP_N0=SP2xP[numSP-1];   MXtw_0[2][1]=(SP1xP_N0-SP2xP_N0)/two/x1typ;
 SP3x_N0= SP3x[numSP-1];    SP4x_N0 =SP4x[numSP-1];    MXtw_0[1][2]= (SP3x_N0-SP4x_N0)/two/x1typ;
 SP3xP_N0=SP3xP[numSP-1];   SP4xP_N0=SP4xP[numSP-1];   MXtw_0[2][2]=(SP3xP_N0-SP4xP_N0)/two/x1typ; 

 SP1x_i= SP1x[i-1];         SP2x_i =SP2x[i-1];         MXtw_i[1][1]= (SP1x_i-SP2x_i)/two/x1typ;
 SP1xP_i=SP1xP[i-1];        SP2xP_i=SP2xP[i-1];        MXtw_i[2][1]=(SP1xP_i-SP2xP_i)/two/x1typ;
 SP3x_i= SP3x[i-1];         SP4x_i =SP4x[i-1];         MXtw_i[1][2]= (SP3x_i-SP4x_i)/two/x1typ;
 SP3xP_i=SP3xP[i-1];        SP4xP_i=SP4xP[i-1];        MXtw_i[2][2]=(SP3xP_i-SP4xP_i)/two/x1typ; 

 printf("\n");
 printf("X one turn transfer matrix from origin determined from  (scaled)\n");
  printf("   SP1x_N0-SP2x_N0  = %+.2e ",MXtw_0[1][1]);
  printf("   SP3x_N0-SP4x_N0  = %+.2e ",MXtw_0[1][2]);
  printf("\n");
  printf("   SP1xP_N0-SP2xP_N0= %+.2e ",MXtw_0[2][1]);
  printf("   SP3xP_N0-SP4xP_N0= %+.2e ",MXtw_0[2][2]);
  printf("\n");
 traceMXtw_0=traceArray(MXtw_0);
 printf("traceMXtw_0             %+.17e\n",traceMXtw_0);
 determinatMXtw_0=determinantArray(MXtw_0);
 printf("determinatMXtw_0        %+.17e\n",determinatMXtw_0);

 printf("\n");
 printf("X one turn transfer matrix from ith element determined from  (scaled)\n");
  printf("   SP1x_i-SP2x_i    = %+.2e ",MXtw_i[1][1]);
  printf("   SP3x_i-SP4x_i    = %+.2e ",MXtw_i[1][2]);
  printf("\n");
  printf("   SP1xP_i-SP2xP_i  = %+.2e ",MXtw_i[2][1]);
  printf("   SP3xP_i-SP4xP_i  = %+.2e ",MXtw_i[2][2]);
  printf("\n");
 traceMXtw_i=traceArray(MXtw_i);
 printf("traceMXtw_i             %+.17e\n",traceMXtw_i);
 determinatMXtw_i=determinantArray(MXtw_i);
 printf("determinatMXtw_i        %+.17e\n",determinatMXtw_i);

 return 0;
}
