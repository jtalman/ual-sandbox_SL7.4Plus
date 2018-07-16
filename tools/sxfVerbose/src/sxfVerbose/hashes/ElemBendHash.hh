//# Library     : SXF
//# File        : ElemBendHash.hh
//# Copyright   : see Copyrigh file
//# Author      : Nikolay Malitsky

#ifndef SXF_ELEM_BEND_HASH
#define SXF_ELEM_BEND_HASH

#include "sxfVerbose/hashes/ElemBucketHash.hh"

namespace SXF {

  /**  
   * The ElemBendHash class implements a bend bucket hash
   * (SXF Bend attribute keys are "kl", "kls", "fint", "hgap",
   * "e1", and "e2").
   */

  class ElemBendHash : public ElemBucketHash
  {
  public:

    enum Attributes { KLE = 0, KLM, FINT, HGAP, E1, E2, SIZE};         // JDT2018

    /** Constructor */
    ElemBendHash();

    /** Map an attribute key to its enum value,
     * Return a corresponding enum value or -1. 
     */
    virtual int index(const char* name) const;

  };
}

#endif
