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
#include "UAL/SMF/AcceleratorNodeFinder.hh"

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

//if(argc!=10){
if(argc!=2){
  std::cout << "usage: ./sxfCheck ./sxf/current2.sxf\n";
//std::cout << "usage: ./sxfCheck ./sxf/measured.sxf 1.0504653e+06 1 0 1 0.0 1 45 9\n";
 std::cout << "argv[0] is this executable         - ./sxfCheck                                 \n";
 std::cout << "argv[1] is the input sxf file      - ./sxf/current2.sxf                         \n";
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

#include"for_postSxfPropagate"

 double f0=1;   //   atof(argv[2]);
 double r0=1;   //   atof(argv[9]);

 std::string mysxf    =argv[1];
 std::string mysxfbase=mysxf.substr(7,mysxf.size()-11);
 std::cout << "mysxf     " << mysxf.c_str() << "\n";
 std::cout << "mysxfbase " << mysxfbase.c_str() << "\n";

 UAL::Shell shell;

#include "userManifest/designBeamValues.hh"

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

#include "userManifest/extractParameters.h"

#include "userManifest/probeDataForTwiss"
#include "userManifest/userBunch"
 int spltBndsPrBend=pow(2,splitForBends);

 shell.readSXF(UAL::Args() << UAL::Arg("file",  sxfFile.c_str()));
 UAL::APDF_Builder apBuilder;
 UAL::AcceleratorPropagator* ap = apBuilder.parse(apdfFile);
 UAL::PropagatorSequence& apSeq = ap->getRootNode();

 UAL::AcceleratorNode& ual_an_r = apSeq.getFrontAcceleratorNode();
 UAL::AcceleratorNode  ual_an   = apSeq.getFrontAcceleratorNode();

 UAL::AcceleratorNodeFinder::Iterator ual_anf_it = UAL::AcceleratorNodeFinder::getInstance().find("ring");
 UAL::AcceleratorNode*  m_lattice = (ual_anf_it->second).operator->();
 UAL::AcceleratorNode*       anode;
 const PacLattice& p_lattice     = (PacLattice&) m_lattice;

 const UAL::AcceleratorNode& sequence=*m_lattice;
 const PacLattice& lattice     = (PacLattice&) sequence;
//      PacLattElement& ple = lattice[0];
  std::string ple_gt;
/*
  PacElemBend* m_bnd;
  PacElemAttributes* attributes;
//PacElemAttributes* attributes = e.getBody();
  PacElemMultipole* m_mlt;
  PacElemOffset* m_offset;
  PacElemRotation* m_rotation;
*/

  for(int i=0;i<lattice.size();i++){
   const PacLattElement& ple = lattice[i];
   ple_gt=ple.getType();
//std::cerr << "ple_gt " << ple_gt << "\n";
   if(ple_gt==""){for_postSxfPropagate << "em_d.propagate(bunch);\n";}
   if(ple_gt=="Marker"){for_postSxfPropagate << "/* " << ple.getDesignName() << " " << ple.getPosition() << " */" << " em_m.propagate(bunch);\n";}
   if(ple_gt=="Quadrupole"){for_postSxfPropagate << "/* " << ple.getDesignName() << " " << ple.getPosition() << " */" << " em_q.propagate(bunch);\n";}
   if(ple_gt=="Sbend"){for_postSxfPropagate << "/* " << ple.getDesignName() << " " << ple.getPosition() << " */" << " em_em.propagate(bunch);\n";}
// if(ple_gt=="Quadrupole"){PacElemMultipole* quadSet = (PacElemMultipole*) &(*it); std::cerr << "JDT Quadrupole\n";}
// if(ple_gt==""){"drift\n";}
// else{std::cerr << " ple.getType() " << ple_gt << " ple_gt.length() " << ple_gt.length() << "\n";}
// std::cerr << " ple.getType() " << ple.getType() << "\n\n";
//
/*
std::cerr << "ple.getLength() " << ple.getLength() << "\n";
   attributes = ple.getBody();
   if(attributes){
    for(PacElemAttributes::iterator it = attributes->begin(); it != attributes->end(); it++){
      switch((*it).key()){
      case PAC_BEND:
      m_bnd = (PacElemBend*) &(*it);
std::cerr << "JDT Bend\n";
//std::cerr << "m_bnd->length() " << m_bnd->length() << "\n";
std::cerr << "m_bnd->angle() " << m_bnd->angle() << "\n";
std::cerr << "m_bnd->fint() " << m_bnd->fint() << "\n";
      break;
      case PAC_MULTIPOLE:
        m_mlt = (PacElemMultipole*) &(*it);
std::cerr << "JDT Multipole\n";
std::cerr << "m_mlt->kl(0) " << m_mlt->kl(0) << "\n";
std::cerr << "m_mlt->kl(1) " << m_mlt->kl(1) << "\n";
std::cerr << "m_mlt->kl(2) " << m_mlt->kl(2) << "\n";
std::cerr << "m_mlt->kl(3) " << m_mlt->kl(3) << "\n";
std::cerr << "m_mlt->ktl(0) " << m_mlt->kl(0) << "\n";
std::cerr << "m_mlt->ktl(1) " << m_mlt->kl(1) << "\n";
std::cerr << "m_mlt->ktl(2) " << m_mlt->kl(2) << "\n";
std::cerr << "m_mlt->ktl(3) " << m_mlt->kl(3) << "\n";
        break;
      case PAC_OFFSET:
        m_offset = (PacElemOffset*) &(*it);
        break;
      case PAC_APERTURE:
        // m_aperture = (PacElemAperture*) &(*it);
        break;
      case PAC_ROTATION:
        m_rotation = (PacElemRotation*) &(*it);
        break;
        default:
        break;
       }   
      }   
     }
*/
      
  }

/*
 const PacLattice& p_lattice2     = (PacLattice&) ual_an_r;
 ualPSs = apSeq.size();
 std::cerr << "\n\n\nsize : " << ualPSs << " propagators \n\n\n";

 int counter = 0;
 std::list<UAL::PropagatorNodePtr>::iterator it;
 anode = m_lattice->getNodeAt(counter);
 UAL::PropagatorNodePtr ual_pnp;
// std::string ple_gt;
 for(it = apSeq.begin(); it != apSeq.end(); it++){
  ual_pnp = *(it);
  std::cerr << counter++ << " (*(ual_pnp)).getType() " << (*(ual_pnp)).getType() << "\n";
  std::cerr << " typeid( *(ual_pnp) ).name() " << typeid( *(ual_pnp) ).name() << "\n";
  const PacLattElement& ple = lattice[counter];
//ple_gt=ple.getType();
//std::cerr << " ple.getType() " << ple_gt << "\n\n";
//std::cerr << " ple.getType() " << ple.getType() << "\n\n";
 }
*/

 for_postSxfPropagate << "}\n";
 for_postSxfPropagate.close();

 double t; // time variable

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
// std::cerr << "++  RE_GeV                                " << RE_GeV   << "                              ++\n";
// std::cerr << "++  KE_D_GeV                              " << KE_D_GeV << "                              ++\n";
// std::cerr << "++  Total design energy in GeV (RE+KE)    " << TE_D_GeV << "                              ++\n";
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
// std::cerr << "++  sqrt(EscrD*EscrD-RE_GeV*RE_GeV)       " << sqrt(EscrD*EscrD-RE_GeV*RE_GeV)         << "                              ++\n";
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
