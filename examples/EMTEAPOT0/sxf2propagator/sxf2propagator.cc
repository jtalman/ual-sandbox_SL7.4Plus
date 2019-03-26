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

 if(argc!=3){
  std::cout << "usage: ./sxf2propagator ./sxf/EM_BM_Z_sl4.sxf 0\n";
  std::cout << "argv[0] is this executable         - ./sxf2propagator                \n";
  std::cout << "argv[1] is the input sxf file      - ./sxf/EM_BM_Z_sl4.sxf     \n";
  std::cout << "argv[2] is the scalar of Z (0)     - 0                         \n";
  exit(0);
 }

 #include"for_postSxfPropagator"

 double f0=1;   //   atof(argv[2]);
 double r0=1;   //   atof(argv[9]);

 std::string mysxf    =argv[1];
 std::string mysxfbase=mysxf.substr(7,mysxf.size()-11);
 std::cout << "mysxf     " << mysxf.c_str() << "\n";
 std::cout << "mysxfbase " << mysxfbase.c_str() << "\n";

 UAL::Shell shell;

 int turns = 1;
 std::string sxfFile = "./working.sxf";     // argv[1];
 std::string apdfFile = "./working.apdf";   // "./apdf/emteapot.apdf";

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
 PacElemComplexity* p_complexity;   // 7: n
 PacElemAttributes* attributes;
 int size;
 double*data;
 int j;
 std::string Slngth, SklE0,SklE1,SklE2, SklM0,SklM1, SklM2;
 double       lngth, klE0, klE1, klE2, klM0, klM1, klM2;

 for_postSxfPropagator.setf( ios::fixed );

 for_postSxfPropagator.precision( 11 );

 for(int i=0;i<lattice.size();i++){
  const PacLattElement& ple = lattice[i];
  attributes = ple.getBody();
  ple_gt=ple.getType();
  ple_P=ple.getPosition();
  ple_L=ple.getLength();
  actualPosition=(int)(10000.*(ple_P + ple_L/2.))/10000.;

  if(ple_gt==""){ple_gt="Drift";for_postSxfPropagator << "  implicitDrift.driftPropagate(bunch, " << ple_L << ");\n";}

  if(ple_gt=="Marker"){for_postSxfPropagator << "  /* " << ple.getDesignName() << " " << actualPosition << " */" << " marker.propagate(bunch);\n";}

  if(ple_gt=="Quadrupole"){for_postSxfPropagator << "  /* " << ple.getDesignName() << " " << actualPosition << " */";
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
     }                                      // end switch   
    }   
   }
   for_postSxfPropagator << "  quad.quadPropagate(bunch, " << lngth << ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ");\n";
  }                                        // end Quadrupole

  if(ple_gt=="Sbend"){for_postSxfPropagator << "  /* " << ple.getDesignName() << " " << actualPosition << " */";
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
   for_postSxfPropagator << "  bend.bendPropagate_m(bunch, " << lngth<< ", " << klE0 << ", " << klE1 << ", " << klM0 << ", " << klM1 << ", " << argv[2] << ");\n";
  }                                                             // end Sbend
 }                                                              // end lattice elemnt for loop

 for_postSxfPropagator << "  std::cerr << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"quadsDT = \" << quadsDT << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"bendsDT = \" << bendsDT << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"sDT = \" << sDT << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"tofDT = \" << tofDT << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"\\n\";";
 for_postSxfPropagator << "  std::cerr << \"turns = \" << turns << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"sDT/turns = \" << sDT/(double)turns << \"\\n\";" << "\n";
 for_postSxfPropagator << "  std::cerr << \"turns/tofDT = \" << (double)turns/tofDT << \"\\n\";" << "\n";
 for_postSxfPropagator << " }\n";

  for_postSxfPropagator << " twissImplications( outputFileName, bendsDT*2-1, sDT, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], bunch[1].getPosition() );" << "\n";
//for_postSxfPropagator << " twissImplications( outputFileName, sDT, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], bunch[1].getPosition() );" << "\n";
//for_postSxfPropagator << " twissImplications( outputFileName, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], bunch[1].getPosition() );" << "\n";
 for_postSxfPropagator << "}\n";
 for_postSxfPropagator.close();

 return 0;
}
