#include<stdio.h>
#include<stdlib.h>
#include"functions.c"

int main (int argc, char*argv[])
{
 int numSP = processSP(1);
 printf("SP1 lines %d:  SP1x[numSP1-1] (R11) %+e\n",numSP,SP1x[numSP-1]);
 printf("SP1 lines %d: SP1xP[numSP1-1] (R21) %+e\n",numSP,SP1xP[numSP-1]);

 numSP = processSP(3);
 printf("SP3 lines %d:  SP3x[numSP3-1] (R12) %+e\n",numSP,SP3x[numSP-1]);
 printf("SP3 lines %d: SP3xP[numSP3-1] (R22) %+e\n",numSP,SP3xP[numSP-1]);

 return 0;
}
