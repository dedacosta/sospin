/*! \mainpage SOSpin Reference
 *
 * Here you can browse the <a href="files.html">files</a> and <a href="annotated.html">classes</a>
 * internal to the SOSpin library.
 *
 * <br><br><a href="http://sospin.hepforge.org/">Return to the main SOSpin page.</a>
 */



// ----------------------------------------------------------------------------
// SOSpin Library
// Copyright (C) 2015 SOSpin Project
//
//   Authors:
//
//     Nuno Cardoso (nuno.cardoso@tecnico.ulisboa.pt)
//     David Emmanuel-Costa (david.costa@tecnico.ulisboa.pt)
//     Nuno Gonçalves (nunogon@deec.uc.pt)
//     Catarina Simoes (csimoes@ulg.ac.be)
//
// ----------------------------------------------------------------------------
// This file is part of SOSpin Library.
//
// SOSpin Library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or any
// later version.
//
// SOSpin Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SOSpin Library.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

//       son.h created on 27/02/2015
//
//      This file contains the functions necessary to do things
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//

/*!
  \file
  \brief Main Sospin header file. Includes C++ macros, to simplify expression writing, B operator, Verbosity level and memory usage.
*/

#ifndef SON_H
#define SON_H


#include "timer.h"
#include "index.h"
#include "dlist.h"
#include "braket.h"
#include "form.h"
#include "enum.h"

#if DOXYGEN
#define nAsserts
#endif

namespace sospin {


/*! \def bb(a)
  \brief C++ Macro for DList b operator
  \param[in] a is the index in string format or enclosed in quotation marks
*/
#define bb(a) DList(0, newIdx(a))

/*! \def bbt(a)
  \brief C++ Macro for DList b\\dagger operator
  \param[in] a is the index in string format or enclosed in quotation marks
*/
#define bbt(a) DList(1, newIdx(a))

/*! \def b(a)
  \brief C++ Macro for DList b operator
  \param[in] a is the index without quotation marks
*/
#define b(a) DList(0, newIdx(#a))

/*! \def bt(a)
  \brief C++ Macro for DList b\\dagger operator
  \param[in] a is the index without quotation marks
*/
#define bt(a) DList(1, newIdx(#a))

/*! \def delta(a,b)
  \brief C++ Macro for DList delta
  \param[in] a is the first delta index without quotation marks
  \param[in] b is the second delta index without quotation marks
*/
#define delta(a,b) DList(2, newIdx(#a), newIdx(#b))
/*! \def identity
  \brief C++ Macro for DList identity/one
*/
#define identity DList(3, 0)

/*! \def bra(i,a,b)
  \brief C++ Macro for bra expression
  \param i index sum
  \param a constant part without quotation marks
  \param b DList expression
*/
#define bra(i,a,b) Braket(i,#a, b, bra)
/*! \def ket(i,a,b)
  \brief C++ Macro for ket expression
  \param i index sum
  \param a constant part without quotation marks
  \param b DList expression
*/
#define ket(i,a,b) Braket(i,#a, b, ket)
/*! \def braket(i,a,b)
  \brief C++ Macro for braket expression
  \param i index sum
  \param a constant part without quotation marks
  \param b DList expression
*/
#define braket(i,a,b) Braket(i,#a, b, braket)
/*! \def free(i,a,b)
  \brief C++ Macro for none expression
  \param i index sum
  \param a constant part without quotation marks
  \param b DList expression
*/
#define free(i,a,b) Braket(i,#a, b, none)


/*! \def Field(a, b, c, d)
  \brief C++ Macro to declare field properties none expression
  \param a field name without quotation marks
  \param b number of upper indexes
  \param c number of lower indexes
  \param d field with/without flavor index and symmetric/asymmetric field (SYM, ASYM, SYM_WITH_FLAVOR or ASYM_WITH_FLAVOR)
  \return field name in string format
*/
#define Field(a, b, c, d)  FormField(#a, b, c, d)

/*!
  \brief Set the group dimension
*/
void setDim(int n);
/*!
  \brief Get the group dimension
*/
int getDim();


/*!
  \brief Return Group parity
*/
bool GroupEven();


/*!
  \brief Clean all indexes and function declarations
*/
void CleanGlobalDecl();


/*!
  \brief Set verbosity level
  \param verb verbosity options: SILENT, SUMMARIZE, VERBOSE, DEBUG_VERBOSE
*/
void setVerbosity(Verbosity verb);

/*!
  \brief Return current verbosity level
  \return active current verbosity level
*/
Verbosity getVerbosity();

/*!
  \brief Return current ostream verbosity level
  \return ostream for output
*/
ostream& operator<<(ostream& out,const Verbosity &a);

//Braket BopN1();
Braket Bop(std::string startid="i");
Braket BopIdnum();

//void process_mem_usage(double& vm_usage, double& resident_set); //only works for linux

/*!
  \brief Gets current resident set size (RSS) - physical memory use.
  \return Returns the current resident set size (physical memory use) measured in bytes, or zero if the value cannot be determined on this OS.
*/
size_t getCurrentRSS( );


/*!
  \brief Gets highest (peak) value so far for resident set size (RSS) - physical memory use.
  \return Returns the peak (maximum so far) resident set size (physical memory use) measured in bytes, or zero if the value cannot be determined on this OS.
*/
size_t getPeakRSS( );


/*!
  \brief Prints memory stats (current and peak resident set size) in MB.
*/
void print_process_mem_usage();


}

#endif



