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

using namespace sospin;

int main(int argc, char *argv[]) {
  Timer alltime;
  alltime.start();
  cout << "################################################################" << endl;

  setDim(10);

  Braket psipbra, psipket, gamma, exp;

  psipbra = bra(0, M(a), identity);
  psipbra += bra(2, 1 / 2 * M20(a, o, p), -b(o) * b(p));
  psipbra += bra(4, 1 / 24 * e_(o, p, q, r, s) * Mb01(a, o), b(p) * b(q) * b(r) * b(s));
  newId("a");

  psipket = ket(0, M(b), identity);
  psipket += ket(2, 1 / 2 * M20(b, j, k), bt(j) * bt(k));
  psipket += ket(4, 1 / 24 * e_(j, k, l, m, n) * Mb01(b, j), bt(k) * bt(l) * bt(m) * bt(n));
  newId("b");

  Field(M, 0, 0, ASYM_WITH_FLAVOR);
  Field(M, 2, 0, ASYM_WITH_FLAVOR);
  Field(Mb, 0, 1, ASYM_WITH_FLAVOR);

  gamma = free(-3, 1 / 6 * (e_(r1, r2, r3, r4, r5) * H20(r4, r5) / sqrt(3)), b(r1) * b(r2) * b(r3));
  gamma += free(3, 1 / 6 * (e_(r1, r2, r3, r4, r5) * H02(r4, r5) / sqrt(3)), bt(r1) * bt(r2) * bt(r3));
  gamma += free(-1, (2 * H12(r1, r2, r3) + d_(r1, r2) * H01(r3) - d_(r1, r3) * H01(r2)) / (2 * sqrt(3)), bt(r1) * b(r2) * b(r3));
  gamma += free(1, (2 * H21(r1, r2, r3) + d_(r1, r3) * H10(r2) - d_(r2, r3) * H10(r1)) / (2 * sqrt(3)), bt(r1) * bt(r2) * b(r3));
  gamma += free(-1, 2 * H01(r1) / sqrt(3), -b(r1));
  gamma += free(1, 2 * H10(r1) / sqrt(3), bt(r1));
  newId("r4");
  newId("r5");

  Field(H, 1, 0, ASYM);
  Field(H, 0, 1, ASYM);
  Field(H, 0, 2, ASYM);
  Field(H, 2, 0, ASYM);
  Field(H, 2, 1, ASYM);
  Field(H, 1, 2, ASYM);

  exp = psipbra * Bop() * gamma * psipket;
  exp.evaluate(false);

  CallForm(exp, true, true, "i");
  setFormRenumber();
  CallForm(exp, true, true, "i");
  cout << "Result: \n"
       << exp << endl;
  print_process_mem_usage();
  cout << "################################################################" << endl;
  cout << "Total time: " << alltime.getElapsedTimeInMicroSec() << " us\t" << alltime.getElapsedTimeInSec() << " s" << endl;
  cout << "################################################################" << endl;
  CleanGlobalDecl();
  exit(0);
}
