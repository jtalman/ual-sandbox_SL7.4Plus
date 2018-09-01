#include "EMTEAPOT/Integrator/marker.cc"
#include "EMTEAPOT/Integrator/drift.cc"
#include "EMTEAPOT/Integrator/quad.cc"
#include "EMTEAPOT/Integrator/embend.cc"
#include "EMTEAPOT/Integrator/sext.cc"
#include "EMTEAPOT/Integrator/oct.cc"
#include "EMTEAPOT/Integrator/rfCavity.cc"
#include "EMTEAPOT/Integrator/genMethods/spinExtern"
#include "EMTEAPOT/Integrator/genMethods/spinDef"
#include "EMTEAPOT/Integrator/genMethods/designExtern"
#include "EMTEAPOT/Integrator/genMethods/designDef"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleExtern"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleDef"
#include "userManifest/probeDataForTwiss"
int main(int argc,char * argv[]){
PAC::Bunch bunch(2);
bunch[0].getPosition().set(      0,       0,      0,      0,      0,      0 );
bunch[1].getPosition().set( +x1typ,       0,      0, +y2typ,      0,      0 );
                     
EMTEAPOT::marker em_m;
EMTEAPOT::drift em_d;
EMTEAPOT::quad em_q;
EMTEAPOT::embend em_em;
EMTEAPOT::sext em_s;
EMTEAPOT::oct em_o;
EMTEAPOT::rfCavity em_rf;
em_m.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_m.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_m.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_m.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_m.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_m.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_em.propagate(bunch);
em_em.propagate(bunch);
em_d.propagate(bunch);
em_q.propagate(bunch);
em_q.propagate(bunch);
em_d.propagate(bunch);
em_m.propagate(bunch);
}
