#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "UAL/SMF/AcceleratorNode.hh"

#include "UAL/APDF/APDF_Builder.hh"
#include "PAC/Beam/Position.hh"
#include "PAC/Beam/Bunch.hh"
#include "UAL/UI/Shell.hh"

#include "PAC/Beam/Spin.hh"

#include "EMTEAPOT/Integrator/embend.cc"
#include "EMTEAPOT/Integrator/quad.cc"

#include "EMTEAPOT/Integrator/genMethods/spinExtern"
#include "EMTEAPOT/Integrator/genMethods/spinDef"
#include "EMTEAPOT/Integrator/genMethods/designExtern"
#include "EMTEAPOT/Integrator/genMethods/designDef"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleExtern"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleDef"

using namespace UAL;

int main(int argc,char * argv[]){
 int startTime, endTime, totalTime;

//#include "include/getArgs"

//if(argc!=10){
if(argc!=2){
  std::cout << "usage: ./sxfCheck ./sxf/measured.sxf\n";
//std::cout << "usage: ./sxfCheck ./sxf/measured.sxf 1.0504653e+06 1 0 1 0.0 1 45 9\n";
 std::cout << "argv[0] is this executable         - ./sxfCheck                                 \n";
 std::cout << "argv[1] is the input sxf file      - ./sxf/measured.sxf                         \n";
/*
 std::cout << "argv[2] is the design frequency, fD, 1.0504653e+06                              \n";
 std::cout << "argv[3] is the nominal electrode m - 1                                          \n";
 std::cout << "argv[4] is the initialSpin file creation type - 0                               \n";
 std::cout << "argv[5] is the number of turns - 1                                              \n";
 std::cout << "argv[6] is the fringe field length - 0.0                                        \n";
 std::cout << "argv[7] is the ""decimation factor"" - 1                                        \n";
 std::cout << "argv[8] is Kinetic Energy (MeV)                                                 \n";
 std::cout << "argv[9] is Design Bend Radius (m) - 9                                           \n";
*/
 exit(0);
}
ofstream m_m;
m_m.open ("m_m");
m_m << "1";   //   argv[2];
m_m.close();
EMTEAPOT::embend* edt=new EMTEAPOT::embend();
//EMTEAPOT::quad*    mdt=new EMTEAPOT::quad();
std::cerr << "EMTEAPOT::embend::dZFF " << EMTEAPOT::embend::dZFF << "\n";
std::cerr << "EMTEAPOT::embend::m_m " << EMTEAPOT::embend::m_m << "\n";
//std::cerr << "EMTEAPOT::quad::m_m    " << EMTEAPOT::quad::m_m    << "\n";
              EMTEAPOT::embend::m_m=1;   //   atof( argv[3] );
//            EMTEAPOT::quad::m_m   =atof( argv[3] );
              EMTEAPOT::embend::dZFF=1;   //   atof( argv[6] );
std::cerr << "EMTEAPOT::embend::dZFF " << EMTEAPOT::embend::dZFF << "\n";
std::cerr << "EMTEAPOT::embend::m_m " << EMTEAPOT::embend::m_m << "\n";
//std::cerr << "EMTEAPOT::quad::m_m    " << EMTEAPOT::quad::m_m    << "\n";
//#include "include/setStatic"

 double f0=1;   //   atof(argv[2]);
 double r0=1;   //   atof(argv[9]);

/*
 double rD=r0;
 double RE_GeV   = UAL::pmass;
 double KE_D_MeV = atof(argv[8]);
 double KE_D_GeV = KE_D_MeV/1000.;
 double TE_D_GeV = RE_GeV+KE_D_GeV;
 double EscrD    = TE_D_GeV;
 double gammaD   = 1.+KE_D_GeV/RE_GeV;
// double LD       = L0;
*/

 std::string mysxf    =argv[1];
 std::string mysxfbase=mysxf.substr(7,mysxf.size()-11);
 std::cout << "mysxf     " << mysxf.c_str() << "\n";
 std::cout << "mysxfbase " << mysxfbase.c_str() << "\n";

 UAL::Shell shell;

#include "userManifest/designBeamValues.hh"

//
  mDcc=m0;
  qD=q0;

       betaD=b0;
       vD=betaD*UAL::clight;
double vDMKS=betaD*UAL::clight;
      gammaD=gamma0;

  eD=e0;
  pDc=p0;
double pcD=p0;
double LD       = rD*pcD;      //    L0;

  fD=f0;

  tofDT=0;
//

#include "userManifest/extractParameters.h"

#include "userManifest/probeDataForTwiss"
#include "userManifest/userBunch"
 int spltBndsPrBend=pow(2,splitForBends);

 // ************************************************************************
 std::cout << "\nDefine the space of Taylor maps." << std::endl;
 // ************************************************************************

 std::cout << "order " << order << "\n";
 shell.setMapAttributes(UAL::Args() << UAL::Arg("order", order));

 shell.readSXF(UAL::Args() << UAL::Arg("file",  sxfFile.c_str()));
// shell.writeSXF(UAL::Args() << UAL::Arg("file",  outputFile.c_str()));
const string L="ring";
//UAL::AcceleratorNode* uanA = shell.getLattice(L);

  UAL::AcceleratorNode* uanA = shell.getLattice("ring");   //    <<<<----

//UAL::AcceleratorNode* uanA = shell.getLattice(UAL::Args() << UAL::Arg("lattice", "ring"));
//UAL::AcceleratorNode* uanA = shell.getLattice("ring");
//UAL::AcceleratorNode* Shell::getLattice("ring");
//UAL::AcceleratorNode* UAL::Shell::getLattice("ring");
//std::cerr << "UAL::AcceleratorNode* uanA.typeid() " << uanA.typeid() << "\n";

/*
  std::cerr << "__FILE__ " << __FILE__ << " UAL::AcceleratorNode* typeid(uanA).name() " << typeid(uanA).name() << "\n";
  std::cerr << "__FILE__ " << __FILE__ << " uanA->getDesignName() " << uanA->getDesignName() << "\n";
  std::cerr << "__FILE__ " << __FILE__ << " uanA->getType() " << uanA->getType() << "\n";
*/

 shell.addSplit(UAL::Args() << UAL::Arg("lattice", "ring") << UAL::Arg("types", "Sbend")      << UAL::Arg("ir", split-1));  // JDT 7/18/2012 new split specification
 shell.addSplit(UAL::Args() << UAL::Arg("lattice", "ring") << UAL::Arg("types", "Quadrupole") << UAL::Arg("ir", 0));
 shell.addSplit(UAL::Args() << UAL::Arg("lattice", "ring") << UAL::Arg("types", "Sextupole")  << UAL::Arg("ir", 0));

 UAL::Args() << UAL::Arg("lattice", "ring");
 //shell.use(UAL::Args() << UAL::Arg("lattice", "ring"));

 UAL::APDF_Builder apBuilder;

 UAL::AcceleratorPropagator* ap = apBuilder.parse(apdfFile);

 if(ap == 0) {
   std::cout << "Accelerator Propagator has not been created " << std::endl;
   return 1;
 }

 UAL::PropagatorSequence& apSeq = ap->getRootNode();
//int ualPSs = apSeq.size();
      ualPSs = apSeq.size();
  std::cout << "\n\n\nsize : " << ualPSs << " propagators \n\n\n";
//std::cout << "\n\n\nsize : " << ap->getRootNode().size() << " propagators \n\n\n";

 int counter = 0;
 std::list<UAL::PropagatorNodePtr>::iterator it;
 for(it = apSeq.begin(); it != apSeq.end(); it++){
  std::cout << counter++ << " (*it)->getType() " << (*it)->getType() << std::endl;
 }

 // ************************************************************************
 std::cout << "\nBunch Part." << std::endl;
 // ************************************************************************

 // ************************************************************************
 std::cout << "\nTracking. " << std::endl;
 // ************************************************************************

 double t; // time variable

 turns = 10;
 turns=1;   //   atoi( argv[5] );
 #include"userManifest/S"
 #include"userManifest/spin"

 decFac=1;   //   atoi(argv[7]);
 startTime = time(NULL);
 for(int iturn = 0; iturn <= (turns-1); iturn++){
  for(int ip=0; ip < bunch.size(); ip++){
  }
  ap -> propagate(bunch);
 }
 endTime = time(NULL);
 totalTime = endTime - startTime;
 std::cerr << "Runtime: " << setiosflags( ios::scientific ) << setprecision(7) << totalTime << " seconds\n";

#ifdef sxfCheck
 std::cerr << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  UAL::pmass                            " << UAL::pmass << "                              ++\n";
 std::cerr << "++  RE_GeV                                " << RE_GeV   << "                              ++\n";
 std::cerr << "++  KE_D_GeV                              " << KE_D_GeV << "                              ++\n";
 std::cerr << "++  Total design energy in GeV (RE+KE)    " << TE_D_GeV << "                              ++\n";
 std::cerr << "++  EscrD                                 " << EscrD    << "                              ++\n";
 std::cerr << "++  gammaD                                " << gammaD   << "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  betaD                                 " << betaD    << "                              ++\n";
 std::cerr << "++  vD (c=1)                              " << v0       << "                              ++\n";
 std::cerr << "++  vDMKS                                 " << vDMKS    << "                              ++\n";
 std::cerr << "++  UAL::clight                           " << UAL::clight << "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  EscrD                                 " << EscrD    << "                              ++\n";
 std::cerr << "++  pcD                                   " << pcD      << "                              ++\n";
 std::cerr << "++  sqrt(EscrD*EscrD-RE_GeV*RE_GeV)       " << sqrt(EscrD*EscrD-RE_GeV*RE_GeV)         << "                              ++\n";
// std::cerr << "++  rD                                    " << rD       << "                              ++\n";
// std::cerr << "++  LD (rD * pcD)                         " << LD       << "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  tofDT                                 " << tofDT    << "                              ++\n";
 std::cerr << "++  SXF Equilibrium Frequency: 1./tofDT   " << 1./tofDT << "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  sDT                                   " << sDT      << "                              ++\n";
 std::cerr << "++  sDT/vDMKS                             " << sDT/vDMKS<< "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++  bendsDT                               " << bendsDT  << "                              ++\n";
 std::cerr << "++  thetaDT (total bend angle - E plus M) " << thetaDT  << "                              ++\n";
 std::cerr << "++                                                                                   ++\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "++===================================================================================++\n";
 std::cerr << "\n";
#endif

 return 0;
}
