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
#include "SMF/PacElemLength.h"
#include "SMF/PacElemComplexity.h"

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
  std::cout << "usage: ./sxfParse ./sxf/current2.sxf\n";
//std::cout << "usage: ./sxfCheck ./sxf/measured.sxf 1.0504653e+06 1 0 1 0.0 1 45 9\n";
 std::cout << "argv[0] is this executable         - ./sxfParse                                 \n";
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

#include"for_postSxfPropagateCommandLineProbe"

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
  double ple_P;
  double ple_L;
  double actualPosition;

    PacElemMultipole* p_entryMlt;
    PacElemMultipole* p_exitMlt;

    PacElemLength* p_length;           // 1: l
    PacElemBend* p_bend;               // 2: angle, fint
    PacElemMultipole* p_mlt;           // 3: kl, ktl
    PacElemOffset* p_offset;           // 4: dx, dy, ds
    PacElemRotation* p_rotation;       // 5: dphi, dtheta, tilt
    // PacElemAperture*p_aperture;     // 6: shape, xsize, ysize
    PacElemComplexity* p_complexity;   // 7: n
    // PacElemSolenoid* p_solenoid;    // 8: ks
    // PacElemRfCavity* p_rf;          // 9: volt, lag, harmon

//PacElemAttributes* attributes = ple.getBody();
  PacElemAttributes* attributes;
  int size;
  double*data;
  int j;
  std::string Slngth, SklE0,SklE1,SklE2, SklM0,SklM1, SklM2;
  double       lngth, klE0, klE1, klE2, klM0, klM1, klM2;

  for_postSxfPropagateCommandLineProbe.setf( ios::fixed );

//for_postSxfPropagateCommandLineProbe.precision( 4 );
//for_postSxfPropagateCommandLineProbe.precision( 9 );
//for_postSxfPropagateCommandLineProbe.precision( 7 );
  for_postSxfPropagateCommandLineProbe.precision( 11 );

  for(int i=0;i<lattice.size();i++){
   const PacLattElement& ple = lattice[i];
   attributes = ple.getBody();
   ple_gt=ple.getType();
   ple_P=ple.getPosition();
   ple_L=ple.getLength();
   actualPosition=(int)(10000.*(ple_P + ple_L/2.))/10000.;

   if(ple_gt==""){ple_gt="Drift";for_postSxfPropagateCommandLineProbe << "  implicitDrift.driftPropagate(bunch, " << ple_L << ");\n";}
// if(ple_gt==""){ple_gt="Drift";for_postSxfPropagateCommandLineProbe << "implicitDrift.propagateWithArguments(bunch, " << ple_L << ");\n";}

   if(ple_gt=="Marker"){for_postSxfPropagateCommandLineProbe << "  /* " << ple.getDesignName() << " " << actualPosition << " */" << " marker.propagate(bunch);\n";}

// if(ple_gt=="Quadrupole"){for_postSxfPropagateCommandLineProbe << "/* " << ple.getDesignName() << " " << actualPosition << " */" << " quad.propagate(bunch);\n";}
   if(ple_gt=="Quadrupole"){for_postSxfPropagateCommandLineProbe << "  /* " << ple.getDesignName() << " " << actualPosition << " */";
    if(attributes){
     for(PacElemAttributes::iterator it = attributes->begin(); it != attributes->end(); it++){
      switch((*it).key()){
       case PAC_LENGTH:                          // 1: l
            p_length = (PacElemLength*) &(*it);
            lngth=p_length->l();
            break;
       case PAC_BEND:                            // 2: angle, fint
            p_bend = (PacElemBend*) &(*it);
            data=p_bend->data();
            size=p_bend->size();
            klE0=p_bend->angle();
            break;
       case PAC_MULTIPOLE:                       // 3: kl, ktl
            p_bend = (PacElemBend*) &(*it);
            p_mlt = (PacElemMultipole*) &(*it);
            data=p_mlt->data();
            size=p_mlt->size();
            klM0=data[1];
            klE1=data[2];
            klM1=data[3];
std::cerr << "QUAD PAC_MULTIPOLE data[0] " << data[0] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[1] " << data[1] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[2] " << data[2] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[3] " << data[3] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[4] " << data[4] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[5] " << data[5] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[6] " << data[6] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[7] " << data[7] << "\n";
            break;
       case PAC_OFFSET:                          // 4: dx, dy, ds
            p_offset = (PacElemOffset*) &(*it);
            break;
       case PAC_ROTATION:                        // 5: dphi, dtheta, tilt
            p_rotation = (PacElemRotation*) &(*it);
            break;
       case PAC_APERTURE:                        // 6: shape, xsize, ysize
            // p_aperture = (PacElemAperture*) &(*it);
            break;
       case PAC_COMPLEXITY:                     // 7: n
            p_complexity = (PacElemComplexity* ) &(*it);
            break;
       case PAC_SOLENOID:                       // 8: ks
            // p_solenoid = (PacElemSolenoid* ) &(*it);
            break;
       case PAC_RFCAVITY:                       // 9: volt, lag, harmon
           // p_rf = (PacElemRfCavity* ) &(*it);
           break;
      default:
        break;
      }   
     }   
    }
   for_postSxfPropagateCommandLineProbe << "  quad.quadPropagate(bunch, " << lngth << ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ");\n";
// for_postSxfPropagateCommandLineProbe << " quad.propagateWith_1Plus5_Arguments(bunch, " << lngth << ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ");\n";
// for_postSxfPropagateCommandLineProbe << " quad.propagateWithArguments(bunch, " << lngth << ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ");\n";
   }

   if(ple_gt=="Sbend"){for_postSxfPropagateCommandLineProbe << "  /* " << ple.getDesignName() << " " << actualPosition << " */";
    if(attributes){
     for(PacElemAttributes::iterator it = attributes->begin(); it != attributes->end(); it++){
      switch((*it).key()){
       case PAC_LENGTH:                          // 1: l
            p_length = (PacElemLength*) &(*it);
            lngth=p_length->l();
            break;
       case PAC_BEND:                            // 2: angle, fint
            p_bend = (PacElemBend*) &(*it);
            data=p_bend->data();
            size=p_bend->size();
            klE0=p_bend->angle();
            break;
       case PAC_MULTIPOLE:                       // 3: kl, ktl
            p_bend = (PacElemBend*) &(*it);
            p_mlt = (PacElemMultipole*) &(*it);
            data=p_mlt->data();
            size=p_mlt->size();
            klM0=data[1];
            klE1=data[2];
            klM1=data[3];
            klM2=data[4];
std::cerr << "BEND PAC_MULTIPOLE data[0] " << data[0] << "\n";
std::cerr << "BEND PAC_MULTIPOLE data[1] " << data[1] << "\n";
std::cerr << "BEND PAC_MULTIPOLE data[2] " << data[2] << "\n";
std::cerr << "BEND PAC_MULTIPOLE data[3] " << data[3] << "\n";
std::cerr << "BEND PAC_MULTIPOLE data[4] " << data[4] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[5] " << data[5] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[6] " << data[6] << "\n";
std::cerr << "QUAD PAC_MULTIPOLE data[7] " << data[7] << "\n";
            break;
       case PAC_OFFSET:                          // 4: dx, dy, ds
            p_offset = (PacElemOffset*) &(*it);
            break;
       case PAC_ROTATION:                        // 5: dphi, dtheta, tilt
            p_rotation = (PacElemRotation*) &(*it);
            break;
       case PAC_APERTURE:                        // 6: shape, xsize, ysize
            // p_aperture = (PacElemAperture*) &(*it);
            break;
       case PAC_COMPLEXITY:                     // 7: n
            p_complexity = (PacElemComplexity* ) &(*it);
            break;
       case PAC_SOLENOID:                       // 8: ks
            // p_solenoid = (PacElemSolenoid* ) &(*it);
            break;
       case PAC_RFCAVITY:                       // 9: volt, lag, harmon
           // p_rf = (PacElemRfCavity* ) &(*it);
           break;
      default:
        break;
      }   
     }   
    }
   for_postSxfPropagateCommandLineProbe << "  bend.bendPropagate(bunch, " << lngth<< ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ");\n";
  }
 }

 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"bendsDT = \" << bendsDT << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"sDT = \" << sDT << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"tofDT = \" << tofDT << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"\\n\";";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"turns = \" << turns << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"sDT/turns = \" << sDT/(double)turns << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << "  std::cerr << \"turns/tofDT = \" << (double)turns/tofDT << \"\\n\";" << "\n";
 for_postSxfPropagateCommandLineProbe << " }\n";
// for_postSxfPropagateCommandLineProbe << " int i = getStndrdPartclIndex(outputFileName);\n";
// for_postSxfPropagateCommandLineProbe << " std::cerr << \"index \" << i << \"\\n\";" << "\n";
// for_postSxfPropagateCommandLineProbe << " trtrout[i][ 1]=bunch[ 1].getPosition().getX();\n";

//for_postSxfPropagateCommandLineProbe << "  std::cerr << fstream forTwiss << \"\\n\";";
  for_postSxfPropagateCommandLineProbe << " fstream forTwiss;" << "\n";
  for_postSxfPropagateCommandLineProbe << " forTwiss.open(\"./out/forTwiss\", fstream::out | fstream::app);" << "\n";
  for_postSxfPropagateCommandLineProbe << " forTwiss.precision(15);" << "\n";
  for_postSxfPropagateCommandLineProbe << " forTwiss << std::scientific;" << "\n";
  for_postSxfPropagateCommandLineProbe << " forTwiss << std::showpos;" << "\n";
//for_postSxfPropagateCommandLineProbe << " forTwiss << bunch[1].getPosition().getX() << ";
  for_postSxfPropagateCommandLineProbe << " forTwiss << bunch[1].getPosition().getX()";
  for_postSxfPropagateCommandLineProbe << " << \" \" << bunch[1].getPosition().getPX()";
  for_postSxfPropagateCommandLineProbe << " << \" \" << bunch[1].getPosition().getY()";
  for_postSxfPropagateCommandLineProbe << " << \" \" << bunch[1].getPosition().getPY()";
  for_postSxfPropagateCommandLineProbe << " << \" \" << bunch[1].getPosition().getCT()";
  for_postSxfPropagateCommandLineProbe << " << \" \" << bunch[1].getPosition().getDE() << \"\\n\";" << "\n";
  for_postSxfPropagateCommandLineProbe << " forTwiss.close();" << "\n";

 for_postSxfPropagateCommandLineProbe << "}\n";
 for_postSxfPropagateCommandLineProbe.close();

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
