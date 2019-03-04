#include <stdio.h>
#include <stdlib.h>                       // for exit
#include <string.h>
#include <math.h>                         // for sqrt, acos
#include <errno.h>
#include <iostream>
//#include <iomanip>
#include <fstream>

#include "EMTEAPOT/Integrator/genMethods/designExtern"
#include "EMTEAPOT/Integrator/genMethods/designDef"

using namespace std;

int main(int argc,char * argv[]){

 if(argc!=2){
  std::cout << "usage: ./tunesPlus 160\n";
  std::cout << "argv[0] is this executable - ./tunesPlus \n";
  std::cout << "argv[1] is number of split bends - 160 \n";
  exit(0);
 }

 double trtrout[7][21];
 for(int i=0;i<7;i++){
  for(int j=0;j<21;j++){
   trtrout[i][j]=0;
  }
 }

 double x1typ = +1e-06;
 double x2typ = +1e-06;
 double y1typ = +1e-06;
 double y2typ = +1e-06;

ifstream inFile;
//ifstream inFile("./out/forTwiss");
//cout << "inFile " << inFile << "\n";    

  inFile.open("./out/forTwiss");
//inFile.open("/home/ualusrPERL/ual-sandbox_SL7.4Plus/examples/EMTEAPOT/out/forTwiss");
//inFile.open("/home/ualusrPERL/ual-sandbox_SL7.4Plus/examples/EMTEAPOT/out/forTwiss",ifstream::in);
 cout << "inFile " << inFile << "\n";
 if (!inFile) {
   cout << "Unable to open file " << strerror(errno) << "\n";
  exit(1);
 }

 int spi=1;
 while(inFile >> trtrout[1][spi] >> trtrout[2][spi] >> trtrout[3][spi] >> trtrout[4][spi] >> trtrout[5][spi] >> trtrout[6][spi]){
// while(!EOF){
//inFile >> trtrout[1][spi] >> trtrout[2][spi] >> trtrout[3][spi] >> trtrout[4][spi] >> trtrout[5][spi] >> trtrout[6][spi];
std::cerr << trtrout[1][spi] << " " << trtrout[2][spi] << " " << trtrout[3][spi] << " " << trtrout[4][spi] << " " << trtrout[5][spi] << " " << trtrout[6][spi] <<"\n";
  spi++;
 }
/*
 while(inFile >> trtrout[spi][ 1] >> trtrout[spi][ 2] >> trtrout[spi][ 3] >> trtrout[spi][ 4] >> trtrout[spi][ 5] >> trtrout[spi][ 6]){
  std::cerr << trtrout[spi][ 1] << " " << trtrout[spi][ 2] << " " << trtrout[spi][ 3] << " " << trtrout[spi][ 4] << " " << trtrout[spi][ 5] << " " << trtrout[spi][ 6] <<"\n";
  spi++;
 }
*/

inFile.close();

#include"rs"

 double a0x=     (double)0;
 double b0x=     (double)0;
 double mu_xTent=(double)0;
 double a0y=     (double)0;
 double b0y=     (double)0;
 double mu_yTent=(double)0;
 #define PI 3.141592653589793
 double MX11=rx[1][1];double MX12=rx[1][2];
 double MX21=rx[2][1];double MX22=rx[2][2];
 double MXtr=MX11+MX22;
 double cosMuX=MXtr/2;
 if( (1-MXtr*MXtr/4)<0 ){std::cerr << "X: Trying to take square root of a negative number!\n";exit(1);}
 double betaX=abs(MX12)/sqrt(1-MXtr*MXtr/4);
 double sinMuX=MX12/betaX;
 double alphaX=(MX11-MX22)/2/sinMuX;
 std::cerr << "JDT: betaX  " << betaX  << "\n";
 std::cerr << "JDT: cosMuX " << cosMuX << "\n";
 std::cerr << "JDT: sinMuX " << sinMuX << "\n";
 std::cerr << "JDT: alphaX " << alphaX << "\n";
 double MuX_PR=acos(cosMuX);
 double MuX;
                                               // half integer tune ambiguity resolution
                                               // NOT full integer tune ambiguity
 if     (cosMuX>=0 && sinMuX>=0){MuX=MuX_PR;}       
 else if(cosMuX<=0 && sinMuX>=0){MuX=MuX_PR;}
 else if(cosMuX<=0 && sinMuX<=0){MuX=2*PI-MuX_PR;}
 else if(cosMuX>=0 && sinMuX<=0){MuX=2*PI-MuX_PR;}

 a0x=alphaX;
 b0x=betaX;
 mu_xTent=MuX;

 std::cerr << "JDT:    MuX " <<    MuX << "\n";
 double QX=MuX/2/PI;
 std::cerr << "JDT:    QX  " <<    QX  << "\n";
 std::cerr <<                             "\n";

 double MY11=ry[1][1];double MY12=ry[1][2];
 double MY21=ry[2][1];double MY22=ry[2][2];
 double MYtr=MY11+MY22;
 double cosMuY=MYtr/2;
 if( (1-MYtr*MYtr/4)<0 ){std::cerr << "Y: Trying to take square root of a negative number!\n";exit(1);}
 double betaY=abs(MY12)/sqrt(1-MYtr*MYtr/4);
 double sinMuY=MY12/betaY;;
 double alphaY=(MY11-MY22)/2/sinMuY;
 std::cerr << "JDT: betaY  " << betaY  << "\n";
 std::cerr << "JDT: cosMuY " << cosMuY << "\n";
 std::cerr << "JDT: sinMuY " << sinMuY << "\n";
 std::cerr << "JDT: alphaY " << alphaY << "\n";
 double MuY_PR=acos(cosMuY);
 double MuY;
 if     (cosMuY>=0 && sinMuY>=0){MuY=MuY_PR;}
 else if(cosMuY<=0 && sinMuY>=0){MuY=MuY_PR;}
 else if(cosMuY<=0 && sinMuY<=0){MuY=2*PI-MuY_PR;}
 else if(cosMuY>=0 && sinMuY<=0){MuY=2*PI-MuY_PR;}
 a0y=alphaY;
 b0y=betaY;
 mu_yTent=MuY;

 std::cerr << "JDT:    MuY " <<    MuY << "\n";
 double QY=MuY/2/PI;
 std::cerr << "JDT:    QY  " <<    QY  << "\n";
 std::cerr <<                             "\n";

//      cerr << "Usage: ./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 206 > ! betaFunctions\n";
// std::cerr <<        "./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 " << bendsDT << ">! betaFunctions" << "\n";
// std::cerr <<        "./betaOf_s +1.0 0.0 31.9793 0.0 77.1718 " << argv[1] << ">! betaFunctions" << "\n";
// std::cerr <<        "./betaOf_s +1.0 " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[1] << ">! betaFunctions" << "\n";
 std::cerr <<        "./betaOf_s +1.0 " << a0x << " " << b0x << " " << a0y << " " << b0y << " " << argv[1] << " >! betaFunctions" << "\n";

 return (int)0;
}
