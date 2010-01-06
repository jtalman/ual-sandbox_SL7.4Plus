// Library       : THINSPIN
// File          : examples/THINSPIN/positionPrinter.hh
// Copyright     : see Copyright file
// Author        :
// C++ version   : J.Talman

#ifndef _POSITIONPRINTER_H
#define	_POSITIONPRINTER_H

#include <fstream>
#include <math.h>

#include "PAC/Beam/Bunch.hh"
#include "UAL/UI/Shell.hh"

class positionPrinter
{
public:

    /** Constructor */
    positionPrinter();

    /** open file*/
    void open(const char* filename);

    void write(int iturn, int ip, PAC::Bunch& bunch);

    /** close file */
    void close();

 protected:

     double get_psp0(PAC::Position& p, double v0byc);

 protected:

    std::ofstream output;

};



#endif	/* _OUTPUTPRINTER_H */


