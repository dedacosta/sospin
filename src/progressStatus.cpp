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

//       progressStatus.cpp created on 27/02/2015
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

#include <sospin/progressStatus.h>
#include <sospin/son.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace sospin {

#define PROGRESS_STATUS_BAR_LENGTH 46

void DoProgress(string label, unsigned int step, unsigned int total, unsigned int interval) {

  if (getVerbosity() == SILENT || total < 1) return;

  if (step % interval != 0 && step < total) return;

  // Calculuate the ratio of complete-to-incomplete.

  float ratio = step / (float)total;

  int c = ratio * PROGRESS_STATUS_BAR_LENGTH;

  // Show the percentage completed.

  printf("%s %3d%% [", label.c_str(), (int)(ratio * 100));

  // Show the loading bar.

  for (int x = 0; x < c; x++) printf("=");

  for (int x = c; x < PROGRESS_STATUS_BAR_LENGTH; x++) printf(" ");

  printf("]\n");

  // ANSI Control codes to go back to the previous line and clear it.

  if (getVerbosity() >= VERBOSE) {

    if (step != total)

      printf("\033[F\033[J");

  }

  else {

    printf("\033[F\033[J");
  }
}

void DoProgress(string label, unsigned int step, unsigned int total) {

  DoProgress(label, step, total, 10);
}

#ifdef PROGRESS_STATUS_BAR_LENGTH

#undef PROGRESS_STATUS_BAR_LENGTH

#endif

}  // namespace sospin
