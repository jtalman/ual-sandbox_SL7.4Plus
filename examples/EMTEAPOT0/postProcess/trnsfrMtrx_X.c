#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"functions.c"
#define PI 3.141592653589793

double SP1x_N0,SP1xP_N0;                // one turn from origin simulated propagated values
double SP2x_N0,SP2xP_N0;
double SP3x_N0,SP3xP_N0;
double SP4x_N0,SP4xP_N0;

double SP1x_i,SP1xP_i;                  // i_th element from origin simulated propagated values
double SP2x_i,SP2xP_i;
double SP3x_i,SP3xP_i;
double SP4x_i,SP4xP_i;

double MX_0i  [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0i,determinantMX_0i;
double MX_0N0 [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0N0,determinantMX_0N0;   // same as MXtw_0
double MX_0iInv [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0iInv,determinantMX_0iInv;

double MXtw_0 [3][3]={1,0,0,0,0,0,0,0,0};double traceMXtw_0,determinantMXtw_0;
double MXtw_i [3][3]={1,0,0,0,0,0,0,0,0};double traceMXtw_i,determinantMXtw_i;                 // Eq. (11)

double MX_0iMXtw_0 [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0iMXtw_0,determinantMX_0iMXtw_0;
double MXtw_0MX_0iInv [3][3]={1,0,0,0,0,0,0,0,0};double traceMXtw_0MX_0iInv,determinantMXtw_0MX_0iInv;

double MX_0iMXtw_0MX_0iInv1 [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0iMXtw_0MX_0iInv1,determinantMX_0iMXtw_0MX_0iInv1;
double MX_0iMXtw_0MX_0iInv2 [3][3]={1,0,0,0,0,0,0,0,0};double traceMX_0iMXtw_0MX_0iInv2,determinantMX_0iMXtw_0MX_0iInv2;

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

 numSP1 = processSP(1);if(numSP!=numSP1){printf("wrong numSP1\n");exit(1);}
 numSP2 = processSP(2);if(numSP!=numSP2){printf("wrong numSP2\n");exit(1);}
 numSP3 = processSP(3);if(numSP!=numSP3){printf("wrong numSP3\n");exit(1);}
 numSP4 = processSP(4);if(numSP!=numSP4){printf("wrong numSP4\n");exit(1);}
 printf("############################## processed lines checks: %d      <<<<<<<<<<----------\n",numSP4);

/*
 printf("# lines %d\n",numSP1);
 printf("# lines %d\n",numSP2);
 printf("# lines %d\n",numSP3);
 printf("# lines %d\n",numSP4);
*/

 SP1x_N0= SP1x[numSP-1];    SP2x_N0 =SP2x[numSP-1];    MX_0N0[1][1]= (SP1x_N0-SP2x_N0)/two/x1typ;
 SP1xP_N0=SP1xP[numSP-1];   SP2xP_N0=SP2xP[numSP-1];   MX_0N0[2][1]=(SP1xP_N0-SP2xP_N0)/two/x1typ;
 SP3x_N0= SP3x[numSP-1];    SP4x_N0 =SP4x[numSP-1];    MX_0N0[1][2]= (SP3x_N0-SP4x_N0)/two/x1typ;
 SP3xP_N0=SP3xP[numSP-1];   SP4xP_N0=SP4xP[numSP-1];   MX_0N0[2][2]=(SP3xP_N0-SP4xP_N0)/two/x1typ; 

 copyArray(MXtw_0,MX_0N0);                    //   <<<<<<------

 SP1x_i= SP1x[i-1];         SP2x_i =SP2x[i-1];         MX_0i[1][1]= (SP1x_i-SP2x_i)/two/x1typ;
 SP1xP_i=SP1xP[i-1];        SP2xP_i=SP2xP[i-1];        MX_0i[2][1]=(SP1xP_i-SP2xP_i)/two/x1typ;
 SP3x_i= SP3x[i-1];         SP4x_i =SP4x[i-1];         MX_0i[1][2]= (SP3x_i-SP4x_i)/two/x1typ;
 SP3xP_i=SP3xP[i-1];        SP4xP_i=SP4xP[i-1];        MX_0i[2][2]=(SP3xP_i-SP4xP_i)/two/x1typ; 

 inverseArray(MX_0i,MX_0iInv);                //   <<<<<<------

 printf("\n");
 printf("X transfer matrix from origin, MX_0N0, determined from  (scaled)\n");
  printf("      SP1x_N0-SP2x_N0  = %+.2e ",MX_0N0[1][1]);
  printf("      SP3x_N0-SP4x_N0  = %+.2e ",MX_0N0[1][2]);
  printf("\n");
  printf("      SP1xP_N0-SP2xP_N0= %+.2e ",MX_0N0[2][1]);
  printf("      SP3xP_N0-SP4xP_N0= %+.2e ",MX_0N0[2][2]);
  printf("\n");
 traceMX_0N0=traceArray(MX_0N0);
 printf("traceMX_0N0             %+.17e\n",traceMX_0N0);
 determinantMX_0N0=determinantArray(MX_0N0);
 printf("determinantMX_0N0       %+.17e\n",determinantMX_0N0);

 printf("\n");
 printf("X one turn transfer matrix from origin, MXtw_0 (=MX_0N0)\n");
  printf("                         %+.2e ",MXtw_0[1][1]);
  printf("                         %+.2e ",MXtw_0[1][2]);
  printf("\n");
  printf("                         %+.2e ",MXtw_0[2][1]);
  printf("                         %+.2e ",MXtw_0[2][2]);
  printf("\n");
 traceMXtw_0=traceArray(MXtw_0);
 printf("traceMXtw_0             %+.17e\n",traceMXtw_0);
 determinantMXtw_0=determinantArray(MXtw_0);
 printf("determinantMXtw_0       %+.17e\n",determinantMXtw_0);

 printf("\n");
 printf("X transfer matrix from ith element, MX_0i, determined from  (scaled)\n");
  printf("      SP1x_i-SP2x_i    = %+.2e ",MX_0i[1][1]);
  printf("      SP3x_i-SP4x_i    = %+.2e ",MX_0i[1][2]);
  printf("\n");
  printf("      SP1xP_i-SP2xP_i  = %+.2e ",MX_0i[2][1]);
  printf("      SP3xP_i-SP4xP_i  = %+.2e ",MX_0i[2][2]);
  printf("\n");
 traceMX_0i=traceArray(MX_0i);
 printf("traceMX_0i             %+.17e\n",traceMX_0i);
 determinantMX_0i=determinantArray(MX_0i);
 printf("determinantMX_0i       %+.17e\n",determinantMX_0i);

 printf("\n");
 printf("X Inverse one turn transfer matrix from ith element, MX_0iInv\n");
  printf("                         %+.2e ",MX_0iInv[1][1]);
  printf("                         %+.2e ",MX_0iInv[1][2]);
  printf("\n");
  printf("                         %+.2e ",MX_0iInv[2][1]);
  printf("                         %+.2e ",MX_0iInv[2][2]);
  printf("\n");
 traceMX_0iInv=traceArray(MX_0iInv);
 printf("traceMX_0iInv          %+.17e\n",traceMX_0iInv);
 determinantMX_0iInv=determinantArray(MX_0iInv);
 printf("determinantMX_0iInv    %+.17e\n",determinantMX_0iInv);

 multiplyArrays(MX_0i,MXtw_0,MX_0iMXtw_0);                      // left * middle of (11)
 printf("\n");
 printf("Eq. (11): X left product, (MX_0i)(MXtw_0)\n");
  printf("                         %+.2e ",MX_0iMXtw_0[1][1]);
  printf("                         %+.2e ",MX_0iMXtw_0[1][2]);
  printf("\n");
  printf("                         %+.2e ",MX_0iMXtw_0[2][1]);
  printf("                         %+.2e ",MX_0iMXtw_0[2][2]);
  printf("\n");
 traceMX_0iMXtw_0=traceArray(MX_0iMXtw_0);
 printf("traceMX_0iMXtw_0       %+.17e\n",traceMX_0iMXtw_0);
 determinantMX_0iMXtw_0=determinantArray(MX_0iMXtw_0);
 printf("determinantMX_0iMXtw_0 %+.17e\n",determinantMX_0iMXtw_0);

 multiplyArrays(MXtw_0,MX_0iInv,MXtw_0MX_0iInv);                // middle * right of (11)
 printf("\n");
 printf("Eq. (11): X right product, (MXtw_0)(MX_0iInv)\n");
  printf("                         %+.2e ",MXtw_0MX_0iInv[1][1]);
  printf("                         %+.2e ",MXtw_0MX_0iInv[1][2]);
  printf("\n");
  printf("                         %+.2e ",MXtw_0MX_0iInv[2][1]);
  printf("                         %+.2e ",MXtw_0MX_0iInv[2][2]);
  printf("\n");
 traceMXtw_0MX_0iInv=traceArray(MXtw_0MX_0iInv);
 printf("traceMXtw_0MX_0iInv       %+.17e\n",traceMXtw_0MX_0iInv);
 determinantMXtw_0MX_0iInv=determinantArray(MXtw_0MX_0iInv);
 printf("determinantMXtw_0MX_0iInv %+.17e\n",determinantMXtw_0MX_0iInv);

 multiplyArrays(MX_0iMXtw_0,MX_0iInv,MX_0iMXtw_0MX_0iInv1);          // (left * middle) * right of (11)
 printf("\n");
 printf("Eq. (11): X total product, (MX_0iMXtw_0)(MX_0iInv)\n");
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv1[1][1]);
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv1[1][2]);
  printf("\n");
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv1[2][1]);
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv1[2][2]);
  printf("\n");
 traceMX_0iMXtw_0MX_0iInv1=traceArray(MX_0iMXtw_0MX_0iInv1);
 printf("traceMX_0iMXtw_0MX_0iInv1       %+.17e\n",traceMX_0iMXtw_0MX_0iInv1);
 determinantMX_0iMXtw_0MX_0iInv1=determinantArray(MX_0iMXtw_0MX_0iInv1);
 printf("determinantMX_0iMXtw_0MX_0iInv1 %+.17e\n",determinantMX_0iMXtw_0MX_0iInv1);

 multiplyArrays(MX_0i,MXtw_0MX_0iInv,MX_0iMXtw_0MX_0iInv2);          // left * (middle * right) of (11)
 printf("\n");
 printf("Eq. (11): X total product, (MX_0i)(MXtw_0MX_0iInv)\n");
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv2[1][1]);
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv2[1][2]);
  printf("\n");
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv2[2][1]);
  printf("                         %+.2e ",MX_0iMXtw_0MX_0iInv2[2][2]);
  printf("\n");
 traceMX_0iMXtw_0MX_0iInv2=traceArray(MX_0iMXtw_0MX_0iInv2);
 printf("traceMX_0iMXtw_0MX_0iInv2       %+.17e\n",traceMX_0iMXtw_0MX_0iInv2);
 determinantMX_0iMXtw_0MX_0iInv2=determinantArray(MX_0iMXtw_0MX_0iInv2);
 printf("determinantMX_0iMXtw_0MX_0iInv2 %+.17e\n",determinantMX_0iMXtw_0MX_0iInv2);

 return 0;
}
