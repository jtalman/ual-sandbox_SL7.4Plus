#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "UAL/Common/AttributeSet.hh"
#include "PAC/Beam/Position.hh"

//#define sElems 10000
  int     sElems=10000;

//#define sElems 1006
//#define sElems 286
//#define sElems 206
//#define sElems 160

using namespace std;
int main(int argc, char* argv[]){

//if( argc != 7 ){
  if( argc != 6 ){
//cerr << "Usage: ./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 206 > ! betaFunctions\n";
//cerr << "Usage: ./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 160 >! betaFunctions\n";
  cerr << "Usage: ./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 >! betaFunctions\n";
  exit(1);
 }

//int sElems = atoi( argv[6] );
 int ip=1;
 int bend=0;
 string alp;
 int i;
 PAC::Position p1[sElems],p2[sElems],p3[sElems],p4[sElems],p5[sElems],p6[sElems],p7[sElems],p8[sElems],p9[sElems],p10[sElems];
 double M[sElems][6][6];

 cout << setiosflags( ios::showpos    );  
 cout << setiosflags( ios::uppercase  );  
 cout << setiosflags( ios::scientific );
 cout << setfill( ' ' );
 cout << setiosflags( ios::left );
 cout << setprecision(13) ;

 char bfr[10];
 sprintf(bfr,"%+5.2f",atof(argv[1]));
 string m(bfr);
 cerr << "m          " << m          << "\n";
 cerr << "m.length() " << m.length() << "\n";

/*
#include "sip1"
#include "sip2"
#include "sip3"
#include "sip4"
#include "sip5"
#include "sip6"
#include "sip7"
#include "sip8"
#include "sip9"
#include "sip10"
*/

 int ipx,split_bnd,z;
 double sp1,sp2,sp3;

 int sp1T=0;
 fstream SP1;
         SP1.open("./out/StndrdPrtcl1",fstream::in);
 while(SP1 >> ip >> split_bnd >> z >> p1[sp1T][0] >> p1[sp1T][1] >> p1[sp1T][2] >> p1[sp1T][3] >> p1[sp1T][4] >> p1[sp1T][5] >> sp1 >> sp2 >> sp3){sp1T++;}
std::cerr << "sp1T  " << sp1T << "\n";

 int sp2T=0;
 fstream SP2;
         SP2.open("./out/StndrdPrtcl2",fstream::in);
 while(SP2 >> ip >> split_bnd >> z >> p2[sp2T][0] >> p2[sp2T][1] >> p2[sp2T][2] >> p2[sp2T][3] >> p2[sp2T][4] >> p2[sp2T][5] >> sp1 >> sp2 >> sp3){sp2T++;}
std::cerr << "sp2T  " << sp2T << "\n";

 int sp3T=0;
 fstream SP3;
         SP3.open("./out/StndrdPrtcl3",fstream::in);
 while(SP3 >> ip >> split_bnd >> z >> p3[sp3T][0] >> p3[sp3T][1] >> p3[sp3T][2] >> p3[sp3T][3] >> p3[sp3T][4] >> p3[sp3T][5] >> sp1 >> sp2 >> sp3){sp3T++;}
std::cerr << "sp3T  " << sp3T << "\n";

 int sp4T=0;
 fstream SP4;
         SP4.open("./out/StndrdPrtcl4",fstream::in);
 while(SP4 >> ip >> split_bnd >> z >> p4[sp4T][0] >> p4[sp4T][1] >> p4[sp4T][2] >> p4[sp4T][3] >> p4[sp4T][4] >> p4[sp4T][5] >> sp1 >> sp2 >> sp3){sp4T++;}
std::cerr << "sp4T  " << sp4T << "\n";

 int sp5T=0;
 fstream SP5;
         SP5.open("./out/StndrdPrtcl5",fstream::in);
 while(SP5 >> ip >> split_bnd >> z >> p5[sp5T][0] >> p5[sp5T][1] >> p5[sp5T][2] >> p5[sp5T][3] >> p5[sp5T][4] >> p5[sp5T][5] >> sp1 >> sp2 >> sp3){sp5T++;}
std::cerr << "sp5T  " << sp5T << "\n";

 int sp6T=0;
 fstream SP6;
         SP6.open("./out/StndrdPrtcl6",fstream::in);
 while(SP6 >> ip >> split_bnd >> z >> p6[sp6T][0] >> p6[sp6T][1] >> p6[sp6T][2] >> p6[sp6T][3] >> p6[sp6T][4] >> p6[sp6T][5] >> sp1 >> sp2 >> sp3){sp6T++;}
std::cerr << "sp6T  " << sp6T << "\n";

 int sp7T=0;
 fstream SP7;
         SP7.open("./out/StndrdPrtcl7",fstream::in);
 while(SP7 >> ip >> split_bnd >> z >> p7[sp7T][0] >> p7[sp7T][1] >> p7[sp7T][2] >> p7[sp7T][3] >> p7[sp7T][4] >> p7[sp7T][5] >> sp1 >> sp2 >> sp3){sp7T++;}
std::cerr << "sp7T  " << sp7T << "\n";

 int sp8T=0;
 fstream SP8;
         SP8.open("./out/StndrdPrtcl8",fstream::in);
 while(SP8 >> ip >> split_bnd >> z >> p8[sp8T][0] >> p8[sp8T][1] >> p8[sp8T][2] >> p8[sp8T][3] >> p8[sp8T][4] >> p8[sp8T][5] >> sp1 >> sp2 >> sp3){sp8T++;}
std::cerr << "sp8T  " << sp8T << "\n";

 int sp9T=0;
 fstream SP9;
         SP9.open("./out/StndrdPrtcl9",fstream::in);
 while(SP9 >> ip >> split_bnd >> z >> p9[sp9T][0] >> p9[sp9T][1] >> p9[sp9T][2] >> p9[sp9T][3] >> p9[sp9T][4] >> p9[sp9T][5] >> sp1 >> sp2 >> sp3){sp9T++;}
std::cerr << "sp9T  " << sp9T << "\n";

 int sp10T=0;
 fstream SP10;
         SP10.open("./out/StndrdPrtcl10",fstream::in);
 while(SP10 >> ip >> split_bnd >> z >> p10[sp10T][0] >> p10[sp10T][1] >> p10[sp10T][2] >> p10[sp10T][3] >> p10[sp10T][4] >> p10[sp10T][5] >> sp1 >> sp2 >> sp3){sp10T++;}
std::cerr << "sp10T " << sp10T << "\n";

 double PI=3.141592654;

 double a0x=atof(argv[2]);
 double b0x=atof(argv[3]);
 double muX_OfS;
 double xTrace;
 double xMu;
 double psiX_OfS=0.0;
 double betaX_OfS;

 double a0y=atof(argv[4]);
 double b0y=atof(argv[5]);
 double muY_OfS;
 double yTrace;
 double yMu;
 double psiY_OfS=0.0;
 double betaY_OfS;

 double tolerance=+0.000001;
 double betaX_OfSLAST=b0x;
 double betaY_OfSLAST=b0y;
 double psiX_OfSLAST=0.0;
 double psiY_OfSLAST=0.0;
 int intTuneX_LAST=0;
 int intTuneY_LAST=0;

//#include "probeDataForTwiss"
// i=atoi(argv[2]);

 double x1typ=1.0e-06,x2typ=1.0e-06,y1typ=1.0e-06,y2typ=1.0e-06,deltyp=1.0e-06;

 sElems=sp1T;
 for(int i=0;i<sElems;i++){

  // #include "col0"
  M[i][0][0]=(p1[i][0]-p2[i][0])/2/x1typ;
  M[i][1][0]=(p1[i][1]-p2[i][1])/2/x1typ;
  M[i][2][0]=(p1[i][2]-p2[i][2])/2/x1typ;
  M[i][3][0]=(p1[i][3]-p2[i][3])/2/x1typ;
  M[i][4][0]=(p1[i][4]-p2[i][4])/2/x1typ;
  M[i][5][0]=(p1[i][5]-p2[i][5])/2/x1typ;

  // #include "col1tld"
  M[i][0][1]=(p3[i][0]-p4[i][0])/2/x2typ;
  M[i][1][1]=(p3[i][1]-p4[i][1])/2/x2typ;
  M[i][2][1]=(p3[i][2]-p4[i][2])/2/x2typ;
  M[i][3][1]=(p3[i][3]-p4[i][3])/2/x2typ;
  M[i][4][1]=(p3[i][4]-p4[i][4])/2/x2typ;
  M[i][5][1]=(p3[i][5]-p4[i][5])/2/x2typ;

  // #include "col2tld"
  M[i][0][2]=(p5[i][0]-p6[i][0])/2/y1typ;
  M[i][1][2]=(p5[i][1]-p6[i][1])/2/y1typ;
  M[i][2][2]=(p5[i][2]-p6[i][2])/2/y1typ;
  M[i][3][2]=(p5[i][3]-p6[i][3])/2/y1typ;
  M[i][4][2]=(p5[i][4]-p6[i][4])/2/y1typ;
  M[i][5][2]=(p5[i][5]-p6[i][5])/2/y1typ;

  // #include "col3tld"
  M[i][0][3]=(p7[i][0]-p8[i][0])/2/y2typ;
  M[i][1][3]=(p7[i][1]-p8[i][1])/2/y2typ;
  M[i][2][3]=(p7[i][2]-p8[i][2])/2/y2typ;
  M[i][3][3]=(p7[i][3]-p8[i][3])/2/y2typ;
  M[i][4][3]=(p7[i][4]-p8[i][4])/2/y2typ;
  M[i][5][3]=(p7[i][5]-p8[i][5])/2/y2typ;

  // #include "col4tld"
  M[i][0][4]=0;
  M[i][1][4]=0;
  M[i][2][4]=0;
  M[i][3][4]=0;
  M[i][4][4]=1;
  M[i][5][4]=0;

  // #include "col5tld"
  M[i][0][5]=(p9[i][0]-p10[i][0])/2/deltyp;
  M[i][1][5]=(p9[i][1]-p10[i][1])/2/deltyp;
  M[i][2][5]=(p9[i][2]-p10[i][2])/2/deltyp;
  M[i][3][5]=(p9[i][3]-p10[i][3])/2/deltyp;
  M[i][4][5]=(p9[i][4]-p10[i][4])/2/deltyp;
  M[i][5][5]=(p9[i][5]-p10[i][5])/2/deltyp;

  psiX_OfS=2*PI*intTuneX_LAST + atan2( M[i][0][1], b0x*M[i][0][0]-a0x*M[i][0][1] );
  if( psiX_OfS < psiX_OfSLAST ){ 
    intTuneX_LAST++;
    psiX_OfS+=2*PI;
  }
  psiX_OfSLAST = psiX_OfS;

  if( fabs( sin(psiX_OfS) ) > tolerance ){
    betaX_OfS = M[i][0][1]*M[i][0][1]/sin(psiX_OfS)/sin(psiX_OfS)/b0x;
    betaX_OfSLAST = betaX_OfS;
  }
  else{
   betaX_OfS = betaX_OfSLAST;
  }
  betaX_OfSLAST = betaX_OfS;

  psiY_OfS=2*PI*intTuneY_LAST + atan2( M[i][2][3],b0y*M[i][2][2]-a0y*M[i][2][3] );
  if( psiY_OfS < psiY_OfSLAST ){ 
    intTuneY_LAST++;
    psiY_OfS+=2*PI;
  }
  psiY_OfSLAST = psiY_OfS;

  if( fabs( sin(psiY_OfS) ) > tolerance ){
    betaY_OfS = M[i][2][3]*M[i][2][3]/sin(psiY_OfS)/sin(psiY_OfS)/b0y;
    betaY_OfSLAST = betaY_OfS;
  }
  else{
   betaY_OfS = betaY_OfSLAST;
  } 
  betaY_OfSLAST = betaY_OfS;

  cout << i << " " <<                                  betaX_OfSLAST << " " << betaY_OfSLAST << " " << psiX_OfSLAST << " " <<  psiY_OfSLAST << "\n";
//cout << setw(12) << name[i] << " " << s[i] << " " << betaX_OfSLAST << " " << betaY_OfSLAST << " " << psiX_OfSLAST << " " <<  psiY_OfSLAST << "\n";
 }
 return 0;
}
