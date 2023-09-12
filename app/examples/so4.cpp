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

//      sospin.cpp created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 01/07/2015  nuno
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

#include <son.h>

using namespace std;
using namespace sospin;

int main(int argc, char *argv[]) {

  Timer alltime;
  alltime.start();
  cout << "################################################################" << endl;
  setDim(4);
  setVerbosity(SUMMARIZE);
  cout << "Verbosity type: " << getVerbosity() << endl;

  unsetSimplifyIndexSum();

  Braket psi1_bra = bra(0, M(a), identity);
  psi1_bra += bra(0, Mb(a) * e_(l, m) / 2, b(m) * b(l));

  Braket psi2_bra = bra(1, N10(a, n), b(n));

  Braket psi1_ket = ket(0, M(b), identity);
  psi1_ket += ket(0, Mb(b) * e_(i, j) / 2, bt(i) * bt(j));

  Braket psi2_ket = ket(1, N10(b, k), bt(k));

  Field(M, 0, 0, ASYM_WITH_FLAVOR);
  Field(Mb, 0, 0, ASYM_WITH_FLAVOR);
  Field(N, 1, 0, ASYM_WITH_FLAVOR);
  newId("a");
  newId("b");

  Braket psi1_psi1 = psi1_bra * Bop() * psi1_ket;
  psi1_psi1.evaluate();
  Braket psi1_psi2 = psi1_bra * Bop() * psi2_ket;
  psi1_psi2.evaluate();
  Braket psi2_psi1 = psi2_bra * Bop() * psi1_ket;
  psi2_psi1.evaluate();
  Braket psi2_psi2 = psi2_bra * Bop() * psi2_ket;
  psi2_psi2.evaluate();
  Braket psi_psi = (psi1_bra + psi2_bra) * Bop() * (psi1_ket + psi2_ket);
  psi_psi.evaluate();

  // unsetFormIndexSum();
  // setFormRenumber();
  CallForm(psi1_psi1, true, true, "i");
  CallForm(psi1_psi2, true, true, "i");
  CallForm(psi2_psi1, true, true, "i");
  CallForm(psi2_psi2, true, true, "i");
  CallForm(psi_psi, true, true, "i");
  print_process_mem_usage();
  cout << "################################################################" << endl;
  cout << "Total time: " << alltime.getElapsedTimeInMicroSec() << " us\t" << alltime.getElapsedTimeInSec() << " s" << endl;
  cout << "################################################################" << endl;
  CleanGlobalDecl();
  exit(0);
}
