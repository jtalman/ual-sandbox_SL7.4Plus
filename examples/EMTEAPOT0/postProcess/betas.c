#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include"functions.c"

int main (int argc, char*argv[])
{
 int i=0;
// fp = fopen (argv[1],"r");
 int numSP1x;
 int wcl=getNumLines(argv[1]);
// int wcl=getNumLines("../propagate/out/StndrdPrtcl8");
 printf("   # of elmts in %s is %d\n",argv[1],wcl);
// printf("SP1x lines %d\n",fillSP1x());

 numSP1x = fillSP1x("../propagate/out/StndrdPrtcl1");
 printf("SP1x lines %d\n",numSP1x);

 for(i=0;i<numSP1x;i++){
  printf("allSP1x[%d] %+e\n",i,allSP1x[i]);
 }

 return 0;
}
