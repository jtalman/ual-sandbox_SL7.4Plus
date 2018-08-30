#include "EMTEAPOT/Integrator/marker.cc"
#include "EMTEAPOT/Integrator/drift.cc"
#include "EMTEAPOT/Integrator/embend.cc"
#include "EMTEAPOT/Integrator/quad.cc"
#include "EMTEAPOT/Integrator/sext.cc"
#include "EMTEAPOT/Integrator/oct.cc"
#include "EMTEAPOT/Integrator/rfCavity.cc"

#include "EMTEAPOT/Integrator/genMethods/spinExtern"
#include "EMTEAPOT/Integrator/genMethods/spinDef"
#include "EMTEAPOT/Integrator/genMethods/designExtern"
#include "EMTEAPOT/Integrator/genMethods/designDef"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleExtern"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleDef"

int main(int argc,char * argv[]){
EMTEAPOT::marker emm;
EMTEAPOT::drift emd;
EMTEAPOT::embend eme;
EMTEAPOT::quad emq;
EMTEAPOT::sext ems;
EMTEAPOT::oct emo;
EMTEAPOT::rfCavity emrf;
}
