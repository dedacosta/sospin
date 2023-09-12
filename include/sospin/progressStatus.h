// ----------------------------------------------------------------------------
// SOSpin Library
// Copyright (C) 2015,2023 SOSpin Project
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

//       progressStatus.h created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

/*!
  \file
  \brief Specific functions progress status bar.
*/

#ifndef PROGRESSSTATUS_H_DEF

#define PROGRESSSTATUS_H_DEF

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

namespace sospin {

void DoProgress(std::string label, unsigned int step, unsigned int total);

void DoProgress(std::string label, unsigned int step, unsigned int total, unsigned int print_at_steps);

}  // namespace sospin

#endif  // PROGRESSSTATUS_H_DEF
