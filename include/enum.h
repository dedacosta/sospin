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

//       enum.h created on 27/02/2015 
//
//      This file contains the functions necessary to do things 
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated	
//

/*!
  \file 
  \brief Enumerators.
*/

#ifndef ENUM_H
#define ENUM_H
 

/*!
  \enum Enumerator for Braket Type
  \brief Enumerator for Braket Type
*/
typedef enum OPMode_s {
  none,
  bra,
  ket,
  braket
} OPMode;


/*!
  \enum Enumerator for verbosity
  \brief Enumerator for verbosity
*/
typedef enum Verbosity_s {
 SILENT,
 SUMMARIZE,
 VERBOSE,
 DEBUG_VERBOSE
} Verbosity;



/*!
  \enum Enumerator for FuncProp
  \brief Enumerator for field properties
*/
typedef enum FuncProp_s {
  SYM,              // symmetric without flavor indice
  ASYM,             // antisymmetric without flavor indice
  SYM_WITH_FLAVOR,  // symmetric with flavor indice
  ASYM_WITH_FLAVOR  // antisymmetric with flavor indice
} FuncProp;


#endif



