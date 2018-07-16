//# Library     : SXF
//# File        : SXF.hh
//# Copyright   : see Copyrigh file
//# Author      : Nikolay Malitsky

#ifndef SXF_H
#define SXF_H

#include "sxfVerbose/OStream.hh"
#include "sxfVerbose/hashes/ElemAlignHash.hh"
#include "sxfVerbose/hashes/ElemApertureHash.hh"
#include "sxfVerbose/hashes/ElemBendHash.hh"
#include "sxfVerbose/hashes/ElemBeamBeamHash.hh"
#include "sxfVerbose/hashes/ElemElSeparatorHash.hh"
#include "sxfVerbose/hashes/ElemMultipoleHash.hh"
#include "sxfVerbose/hashes/ElemRfCavityHash.hh"
#include "sxfVerbose/hashes/ElemSolenoidHash.hh"
#include "sxfVerbose/hashes/ElemEmptyHash.hh"
#include "sxfVerbose/hashes/ElemCollimatorHash.hh"
#include "sxfVerbose/ElemBucketRegistry.hh"
#include "sxfVerbose/Element.hh"
#include "sxfVerbose/Sequence.hh"
#include "sxfVerbose/NodeRegistry.hh"
#include "sxfVerbose/AcceleratorReader.hh"

namespace SXF {

  /** Types */
  typedef SXF_Key                 Key;

}


#endif
