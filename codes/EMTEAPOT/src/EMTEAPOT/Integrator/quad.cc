#ifndef EMTEAPOT_QUAD_CC
#define EMTEAPOT_QUAD_CC

#include <iomanip>
#include <stdlib.h>

#include "SMF/PacElemMultipole.h"
#include "SMF/PacLattice.h"
#include "ETEAPOT/Integrator/MltData.hh"
#include "ETEAPOT/Integrator/BasicTracker.hh"
#include "EMTEAPOT/Integrator/genMethods/Matrices.hh"

#include "EMTEAPOT/Integrator/genMethods/Vectors.h"
#include "EMTEAPOT/Integrator/genMethods/spinExtern"
#include "EMTEAPOT/Integrator/genMethods/designExtern"
#include "EMTEAPOT/Integrator/genMethods/bunchParticleExtern"

namespace EMTEAPOT {

  class quad : public ETEAPOT::BasicTracker {

  public:

#include"EMTEAPOT/Integrator/quadMethods/classMethods"

   inline ETEAPOT::MltData& getMltData();

#include "EMTEAPOT/Integrator/quadMethods/propagate.method"
#include "EMTEAPOT/Integrator/quadMethods/propagateWithArguments.method"
#include "EMTEAPOT/Integrator/quadMethods/propagateWith_1Plus5_Arguments.method"

#include "EMTEAPOT/Integrator/quadMethods/quadPropagate.method"

#include "EMTEAPOT/Integrator/genMethods/get_vlcyMKS.method"
#include "EMTEAPOT/Integrator/genMethods/passDrift.method"

#include "EMTEAPOT/Integrator/quadMethods/passQuadDrift.method"

#include "EMTEAPOT/Integrator/quadMethods/my_cos"

#include "EMTEAPOT/Integrator/quadMethods/perQuadOutput.method"

    /** Element length */
    // double m_l;

    /** Complexity number */
    double m_ir;

    /** Mlt attributes */
    ETEAPOT::MltData m_mdata;

  };

  inline ETEAPOT::MltData& quad::getMltData()
  {
      return m_mdata;
  }

}

#endif
