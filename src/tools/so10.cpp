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

//       SO10.cpp created on 24/03/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 24/03/2015 23:19:29 david
//	    Revision 1.2 27/03/2015 CS - Some index corrections
//      License updated
//      Revision 1.3 12/09/2023 16:53:51 david

/*!
  \file
  \brief Specific functions for SO(10) group.
*/

#include <sospin/son.h>
#include <sospin/tools/so10.h>

using namespace std;

namespace sospin {

/*!\brief Gamma's

  GammaH(n):
  n=0:
  \f{eqnarray*}{
  \Gamma_\mu \phi_\mu &=& H
  \f}

  n=1:
  \f{eqnarray*}{
  \Gamma_\mu \phi_\mu &=& \sqrt{2}\left(b_{r_1} H_{r_1} +  b^\dagger_{r_2} H^{r_2}  \right) \quad\quad (normalized)
  \f}

  n=2:
  \f{eqnarray*}{
  \Gamma_\mu\Gamma_\nu \phi_{\mu\nu} &=& -i \frac{\sqrt{2}}{2} H_{r_1,r_2} b_{r_1} b_{r_2}
                                      -i \frac{\sqrt{2}}{2} H^{r_1,r_2} b^\dagger_{r_1} b^\dagger_{r_2}
                                      -i \left(\sqrt{2} H^{r_1}_{r_2} + \frac{\sqrt{10}}{5} \delta_{r1,r2} H\right) b^\dagger_{r_1} b_{r_2}
                                      +\frac{\sqrt{10}}{2} H  \quad\quad (normalized)
  \f}

  n=3:
  \f{eqnarray*}{
  \Gamma_\mu\Gamma_\nu\Gamma_\gamma \phi_{\mu\nu\gamma} &=&   \frac{1}{6\sqrt{3}} \varepsilon_{r1,r2,r3,r4,r5} \left( H^{r_4,r_5} b_{r_1} b_{r_2} b_{r_3} +  H_{r_4,r_5} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3}\right)\\
&& + \frac{1}{2\sqrt{3}} \left(2 H^{r_1}_{r_2,r_3} +  \delta_{r_1,r_2} H_{r_3} - \delta_{r_1,r_3} H_{r_2}\right)
b^\dagger_{r_1} b_{r_2} b_{r_3}\\
&& + \frac{1}{2\sqrt{3}} \left(2 H^{r_1,r_2}_{r_3} +  \delta_{r_1,r_3} H^{r_2} - \delta_{r_2,r_3} H^{r_1}\right)
b^\dagger_{r_1} b^\dagger_{r_2} b_{r_3}\\
&&+\frac{2}{\sqrt{3}} \left(H^{r_1} b^\dagger_{r_1} - H_{r_1} b_{r_1}\right)
   \quad\quad (normalized)
  \f}
  n=4:
  \f{eqnarray*}{
  \Gamma_\mu\Gamma_\nu\Gamma_\gamma \Gamma_\rho \phi_{\mu\nu\gamma\rho} &=&   \frac{1}{3\sqrt{2}} \left(\frac{1}{\sqrt{3}} H^{r_1,r_2,r_3}_{r_4} + \frac{1}{3}\left(\delta_{r_3,r_4} H^{r_1,r_2} - \delta_{r_2,r_4} H^{r_1,r_3} + \delta_{r_1,r_4} H^{r_2,r_3}\right)\right) b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b_{r_4}\\
   &&-\frac{1}{3\sqrt{2}}\left(\frac{1}{\sqrt{3}}H^{r_1}_{r_2,r_3,r_4} + \frac{1}{3} \left(\delta_{r_1,r_4} H_{r_2,r_3} - \delta_{r_1,r_3} H_{r_2,r_4} + \delta_{r_1,r_2} H_{r_3,r_4}\right)\right) b^\dagger_{r_1} b_{r_2} b_{r_3} b_{r_4}\\
   && +\frac{1}{12\sqrt{6}} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H_{r_5} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b^\dagger_{r_4} + \frac{1}{12\sqrt{6}} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H^{r_5} b_{r_1} b_{r_2} b_{r_3} b_{r_4}\\
  &&-\frac{\sqrt{2}}{4} H^{r_1,r_2} b^\dagger_{r_1} b^\dagger_{r_2} +\frac{\sqrt{2}}{4} H_{r_1,r_2} b_{r_1} b_{r_2}\\
  &&+\frac{\sqrt{5}}{2\sqrt{3}} H -\left(\frac{\sqrt{2}}{2} H^{r_1}_{r_2} +\frac{2\sqrt{5}}{5\sqrt{3}} \delta_{r_1,r_2} H\right) b^\dagger_{r_1} b_{r_2} \\
  &&+\frac{1}{4}\left(\sqrt{\frac{2}{3}} H^{r_1,r_2}_{r_3,r_4} + \frac{\sqrt{2}}{3} \left(\delta_{r_1,r_4} H^{r_2}_{r_3} - \delta_{r_1,r_3} H^{r_2}_{r_4} + \delta_{r_2,r3} H^{r_1}_{r_4} - \delta_{r_2,r_4} H^{r_1}_{r_3} \right)
  + \frac{\sqrt{5}}{5\sqrt{3}} \left(\delta_{r_1,r_4}  \delta_{r_2,r_3} - \delta_{r_1,r_3}  \delta_{r_2,r_4}\right) H \right)
  b^\dagger_{r_1} b^\dagger_{r_2} b_{r_3} b_{r_4}
   \quad\quad (normalized)
  \f}

  n=5:
  \f{eqnarray*}{
  \Gamma_\mu\Gamma_\nu\Gamma_\gamma \Gamma_\rho \Gamma_\eta \phi_{\mu\nu\gamma\rho\eta} &=&   +\frac{\sqrt{15}}{60} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H b_{r_1} b_{r_2} b_{r_3} b_{r_4} b_{r_5}
      +\frac{\sqrt{15}}{60} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b^\dagger_{r_4} b^\dagger_{r_5}\\
   &&   +\frac{\sqrt{2}}{2\sqrt{5}} H^{r_1} b^\dagger_{r_1}
      -\frac{2\sqrt{2}}{3\sqrt{5}} H^{r_1}  b^\dagger_{r_1} b^\dagger_{r_n} b_{r_n}
      +\frac{\sqrt{2}}{6\sqrt{5}}  H^{r_1} b^\dagger_{r_1} b^\dagger_{r_n} b_{r_n} b^\dagger_{r_m} b_{r_m}\\
   &&   +\frac{\sqrt{2}}{2\sqrt{5}} H_{r_1}  b_{r_1}
      -\frac{2\sqrt{2}}{3\sqrt{5}} H_{r_1} b^\dagger_{r_n} b_{r_n} b_{r_1}
      +\frac{\sqrt{2}}{6\sqrt{5}} H_{r_1} b^\dagger_{r_n} b_{r_n} b^\dagger_{r_m} b_{r_m} b_{r_1}\\
   &&   +\frac{\sqrt{2}}{12\sqrt{15}}  \varepsilon_{r_1,r_2,r_3,r_4,r_5} H_{r_4,r_5} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3}
      -\frac{\sqrt{2}}{12\sqrt{15}} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H_{r_4,r_5} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b^\dagger_{r_n} b_{r_n}\\
   &&   +\frac{\sqrt{2}}{12\sqrt{15}} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H^{r_4,r_5} b_{r_1} b_{r_2} b_{r_3}
      -\frac{\sqrt{2}}{12\sqrt{15}} \varepsilon_{r_1,r_2,r_3,r_4,r_5} H^{r_4,r_5} b^\dagger_{r_n} b_{r_n} b_{r_1} b_{r_2} b_{r_3} \\
   &&   +\frac{\sqrt{2}}{\sqrt{15}} H^{r_1,r_2}_{r_3} b^\dagger_{r_1} b^\dagger_{r_2} b_{r_3}
      -\frac{\sqrt{2}}{2\sqrt{15}} H^{r_1,r_2}_{r_3} b^\dagger_{r_1} b^\dagger_{r_2} b_{r_3} b^\dagger_{r_n} b_{r_n}\\
   &&   +\frac{\sqrt{2}}{\sqrt{15}} H^{r_1}_{r_2,r_3} b^\dagger_{r_1} b_{r_2} b_{r_3}
      -\frac{\sqrt{2}}{2\sqrt{15}} H^{r_1}_{r_2,r_3} b^\dagger_{r_n} b_{r_n} b^\dagger_{r_1} b_{r_2} b_{r_3}  \\
   &&   +\frac{\sqrt{2}}{24\sqrt{15}}\varepsilon_{r_1,r_2,r_3,r_4,r_n} H^{sym}_{r_n,r_m} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b^\dagger_{r_4} b_{r_m}
      +\frac{\sqrt{2}}{24\sqrt{15}}\varepsilon_{r_2,r_3,r_4,r_m,r_n} H_{sym}^{r_n,r_1} b^\dagger_{r_1} b_{r_2} b_{r_3} b_{r_4} b_{r_m}\\
   &&   +\frac{1}{6\sqrt{15}} H^{r_1,r_2,r_3}_{r_4,r_m} b^\dagger_{r_1} b^\dagger_{r_2} b^\dagger_{r_3} b_{r_4} b_{r_m}
      +\frac{1}{6\sqrt{15}} H^{r_1,r_2}_{r_3,r_4,r_m} b^\dagger_{r_1} b^\dagger_{r_2} b_{r_3} b_{r_4} b_{r_m}
\quad\quad (normalized)
  \f}
 */
Braket GammaH(int n) {
  if (getDim() != 10) {
    cout << "Error: This function is only available for SO(10)...\nExiting." << endl;
    exit(1);
  }
  Braket gamma;
  switch (n) {
    case 0:
      gamma = free(0, H, identity);
      Field(H, 0, 0, ASYM);
      break;
    case 1:
      gamma = free(-1, sqrt(2) * H01(r1), b(r1));
      gamma += free(1, sqrt(2) * H10(r1), bt(r1));
      Field(H, 0, 1, ASYM);
      Field(H, 1, 0, ASYM);
      break;
    case 2:
      gamma = free(-2, i_ * sqrt(2) * H02(r1, r2) / 2, -b(r1) * b(r2));
      gamma += free(2, i_ * sqrt(2) * H20(r1, r2) / 2, -bt(r1) * bt(r2));
      gamma += free(0, i_ * (sqrt(2) * H11(r1, r2) + 1 / 5 * d_(r1, r2) * sqrt(10) * H), -bt(r1) * b(r2));
      gamma += free(0, i_ * sqrt(10) * H / 2, identity);
      Field(H, 0, 0, ASYM);
      Field(H, 1, 1, ASYM);
      Field(H, 2, 0, ASYM);
      Field(H, 0, 2, ASYM);
      break;
    case 3:  // Nath and the minus sign in David normalization ATENCAO AO PSIp E PSIm
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
      Field(H, 2, 0, ASYM);
      Field(H, 0, 2, ASYM);
      Field(H, 2, 1, ASYM);
      Field(H, 1, 2, ASYM);
      break;
    case 4:
      gamma = free(2, sqrt(2) / 6 * (H31(r1, r2, r3, r4) / sqrt(3) + 1 / 3 * (d_(r3, r4) * H20(r1, r2) - d_(r2, r4) * H20(r1, r3) + d_(r1, r4) * H20(r2, r3))), bt(r1) * bt(r2) * bt(r3) * b(r4));
      gamma += free(-2, sqrt(2) / 6 * (H13(r1, r2, r3, r4) / sqrt(3) + 1 / 3 * (d_(r1, r4) * H02(r2, r3) - d_(r1, r3) * H02(r2, r4) + d_(r1, r2) * H02(r3, r4))), -bt(r1) * b(r2) * b(r3) * b(r4));
      gamma += free(4, sqrt(6) / 72 * e_(r1, r2, r3, r4, r5) * H01(r5), bt(r1) * bt(r2) * bt(r3) * bt(r4));
      gamma += free(-4, sqrt(6) / 72 * e_(r1, r2, r3, r4, r5) * H10(r5), b(r1) * b(r2) * b(r3) * b(r4));
      gamma += free(2, sqrt(2) / 4 * H20(r1, r2), -bt(r1) * bt(r2));
      gamma += free(-2, sqrt(2) / 4 * H02(r1, r2), b(r1) * b(r2));
      gamma += free(0, H * sqrt(5) / (2 * sqrt(3)), identity);
      gamma += free(0, (sqrt(2) / 2 * H11(r1, r2) + 2 * d_(r1, r2) * H / sqrt(15)), -bt(r1) * b(r2));
      gamma += free(0, (1 / 4 * (H22(r1, r2, r3, r4) * sqrt(2) / sqrt(3) + sqrt(2) / 3 * (d_(r1, r4) * H11(r2, r3) - d_(r1, r3) * H11(r2, r4) + d_(r2, r3) * H11(r1, r4) - d_(r2, r4) * H11(r1, r3)) + (d_(r1, r4) * d_(r2, r3) - d_(r1, r3) * d_(r2, r4)) * H / sqrt(15))), bt(r1) * bt(r2) * b(r3) * b(r4));
      newId("r5");
      Field(H, 0, 0, ASYM);
      Field(H, 1, 0, ASYM);
      Field(H, 0, 1, ASYM);
      Field(H, 1, 1, ASYM);
      Field(H, 2, 0, ASYM);
      Field(H, 0, 2, ASYM);
      Field(H, 2, 2, ASYM);
      Field(H, 3, 1, ASYM);
      Field(H, 1, 3, ASYM);
      break;
    case 5: /* verified 27/03/2015 */
      gamma = free(-5, 1 / 60 * e_(r1, r2, r3, r4, r5) * H / sqrt(15), b(r1) * b(r2) * b(r3) * b(r4) * b(r5));
      gamma += free(0, 1 / 60 * e_(r1, r2, r3, r4, r5) * H / sqrt(15), bt(r1) * bt(r2) * bt(r3) * bt(r4) * bt(r5));
      gamma += free(1, 1 / 2 * H10(r1) * sqrt(2) / sqrt(5), bt(r1));
      gamma += free(1, 2 / 3 * sqrt(2) * H10(r1) / sqrt(5), -bt(r1) * bt(rn) * b(rn));
      gamma += free(1, 1 / 6 * sqrt(2) * H10(r1) / sqrt(5), bt(r1) * bt(rn) * b(rn) * bt(rm) * b(rm));
      gamma += free(-1, 1 / 2 * sqrt(2) * H01(r1) / sqrt(5), b(r1));
      gamma += free(-1, 2 / 3 * sqrt(2) * H01(r1) / sqrt(5), -bt(rn) * b(rn) * b(r1));
      gamma += free(-1, 1 / 6 * sqrt(2) * H01(r1) / sqrt(5), bt(rn) * b(rn) * bt(rm) * b(rm) * b(r1));
      gamma += free(3, 1 / 12 * sqrt(2) / sqrt(15) * e_(r1, r2, r3, r4, r5) * H02(r4, r5), bt(r1) * bt(r2) * bt(r3));
      gamma += free(3, 1 / 12 * sqrt(2) / sqrt(15) * e_(r1, r2, r3, r4, r5) * H02(r4, r5), -bt(r1) * bt(r2) * bt(r3) * bt(rn) * b(rn));
      gamma += free(-3, 1 / 12 * sqrt(2) / sqrt(15) * e_(r1, r2, r3, r4, r5) * H20(r4, r5), b(r1) * b(r2) * b(r3));
      gamma += free(-3, 1 / 12 * sqrt(2) / sqrt(15) * e_(r1, r2, r3, r4, r5) * H20(r4, r5), -bt(rn) * b(rn) * b(r1) * b(r2) * b(r3));
      gamma += free(1, sqrt(2) * H21(r1, r2, r3) / sqrt(15), bt(r1) * bt(r2) * b(r3));
      gamma += free(1, 1 / 2 * sqrt(2) * H21(r1, r2, r3) / sqrt(15), -bt(r1) * bt(r2) * b(r3) * bt(rn) * b(rn));
      gamma += free(-1, sqrt(2) * H12(r1, r2, r3) / sqrt(15), bt(r1) * b(r2) * b(r3));
      gamma += free(-1, 1 / 2 * sqrt(2) * H12(r1, r2, r3) / sqrt(15), -bt(rn) * b(rn) * bt(r1) * b(r2) * b(r3));
      gamma += free(3, 1 / 24 * sqrt(2) / sqrt(15) * e_(r1, r2, r3, r4, rn) * Hs02(rn, rm), bt(r1) * bt(r2) * bt(r3) * bt(r4) * b(rm));
      gamma += free(-3, 1 / 24 * sqrt(2) / sqrt(15) * e_(r2, r3, r4, rm, rn) * Hs20(rn, r1), bt(r1) * b(r2) * b(r3) * b(r4) * b(rm));
      gamma += free(1, 1 / 6 * H32(r1, r2, r3, r4, rm) / sqrt(15), bt(r1) * bt(r2) * bt(r3) * b(r4) * b(rm));
      gamma += free(-1, 1 / 6 * H23(r1, r2, r3, r4, rm) / sqrt(15), bt(r1) * bt(r2) * b(r3) * b(r4) * b(rm));
      newId("rn");
      newId("rm");
      Field(H, 0, 0, ASYM);
      Field(H, 1, 0, ASYM);
      Field(H, 0, 1, ASYM);
      Field(H, 0, 2, SYM);
      Field(H, 2, 0, SYM);
      Field(H, 0, 2, ASYM);
      Field(H, 2, 0, ASYM);
      Field(H, 1, 2, ASYM);
      Field(H, 2, 1, ASYM);
      Field(H, 2, 3, ASYM);
      Field(H, 3, 2, ASYM);
      break;
    default:
      cout << "Gamma function not implemented for " << n << ".\nExiting..." << endl;
      exit(1);
      break;
  }
  return gamma;
}

/*!\brief Constructs the ket and bra in the 16th SO(10) representation
\param mode: bra, ket
\return bra/ket

 Note that A and B are flavour indices

  OPMode bra:

  \f$\left< \psi^*_{(+)}\right|\f$:
  \f{eqnarray*}{
    M_A \left< 0\right|
    +\frac{1}{2}M^{o,p}_A\left< 0 \right| b_p b_o
    +\frac{1}{24} \varepsilon_{o,p,q,r,s} \bar{M}_{A\,o} \left< 0 \right| b_s b_r b_q b_p
  \f}

  OPMode ket:
  \f$\left| \psi_{(+)}\right>\f$:
  \f{eqnarray*}{
     \left| 0\right> M_B
    +b^\dagger_j b^\dagger_k \left| 0\right> \frac{1}{2}  M^{j,k}_B
    +   b^\dagger_k b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right> \frac{1}{24} \varepsilon_{j,k,l,m,n}  \bar{M}_{B\,j}
  \f}
 */
Braket psi_16p(OPMode mode) {
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:
      exp = bra(0, M(A), identity);
      exp += bra(2, 1 / 2 * M20(A, o, p), b(p) * b(o));
      exp += bra(4, 1 / 24 * e_(o, p, q, r, s) * Mb01(A, o), b(s) * b(r) * b(q) * b(p));
      newId("A");
      break;
    case ket:
      exp = ket(0, M(B), identity);
      exp += ket(2, 1 / 2 * M20(B, j, k), bt(j) * bt(k));
      exp += ket(4, 1 / 24 * e_(j, k, l, m, n) * Mb01(B, j), bt(k) * bt(l) * bt(m) * bt(n));
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  Field(M, 0, 0, ASYM_WITH_FLAVOR);
  Field(M, 2, 0, ASYM_WITH_FLAVOR);
  Field(Mb, 0, 1, ASYM_WITH_FLAVOR);
  return exp;
}

/*!\brief Constructs the ket and bra in the 16th SO(10) representation
\param mode: bra, ket
       id: defines the head of the index, ex: j1, j2, ...
\return bra/ket

 Note that A and B are flavour indices

  OPMode bra:
  \f$\left< \psi^*_{(+)}\right|\f$:
  \f{eqnarray*}{
    M_A \left< 0\right|
    +\frac{1}{2}M^{o,p}_A\left< 0 \right| b_p b_o
    +\frac{1}{24} \varepsilon_{o,p,q,r,s} \bar{M}_{A\,o} \left< 0 \right| b_s b_r b_q b_p
  \f}

  OPMode ket:
  \f$\left| \psi_{(+)}\right>\f$:
  \f{eqnarray*}{
     \left| 0\right> M_B
    +b^\dagger_j b^\dagger_k \left| 0\right> \frac{1}{2}  M^{j,k}_B
    +   b^\dagger_k b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right> \frac{1}{24} \varepsilon_{j,k,l,m,n}  \bar{M}_{B\,j}
  \f}
 */
Braket psi_16p(OPMode mode, string id) {
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:
      exp = bra(0, M(A), identity);
      exp += Braket(2, "1/2 * M20(A," + makeId(id, 1) + "," + makeId(id, 2) + ")", bb(makeId(id, 2)) * bb(makeId(id, 1)), bra);
      exp += Braket(4, "1/24 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * Mb01(A," + makeId(id, 1) + ")",
                    bb(makeId(id, 5)) * bb(makeId(id, 4)) * bb(makeId(id, 3)) * bb(makeId(id, 2)), bra);
      newId("A");
      break;
    case ket:
      exp = ket(0, M(B), identity);
      exp += Braket(2, "1/2 * M20(B," + makeId(id, 1) + "," + makeId(id, 2) + ")", bbt(makeId(id, 1)) * bbt(makeId(id, 2)), ket);
      exp += Braket(4, "1/24 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * Mb01(B," + makeId(id, 1) + ")",
                    bbt(makeId(id, 2)) * bbt(makeId(id, 3)) * bbt(makeId(id, 4)) * bbt(makeId(id, 5)), ket);
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  Field(M, 0, 0, ASYM_WITH_FLAVOR);
  Field(M, 2, 0, ASYM_WITH_FLAVOR);
  Field(Mb, 0, 1, ASYM_WITH_FLAVOR);
  return exp;
}

/*!\brief Constructs the ket and bra in the 16th-bar SO(10) representation

 Note that A and B are flavour indices

  OPMode bra:
  \f$\left< \psi^*_{(-)}\right|\f$:
  \f{eqnarray*}{
    \bar{N}_{A\,o} \left< 0\right| b_o
    +\frac{1}{12} \varepsilon_{o,p,q,r,s} \bar{N}^{o,p}_A\left< 0 \right| b_s b_r b_q
    +\frac{1}{120} \varepsilon_{o,p,q,r,s} \bar{N}_A \left< 0 \right| b_s b_r b_q b_p b_o
  \f}

  OPMode ket:
  \f$\left| \psi_{(-)}\right>\f$:
  \f{eqnarray*}{
     \left| 0\right> \bar{M}_B
    + b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right>\frac{1}{12} \varepsilon_{j,k,l,m,n} \bar{M}^{j,k}_B
    +  b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right> \frac{1}{120} \varepsilon_{j,k,l,m,n} \bar{M}_B
  \f}
 */
Braket psi_16m(OPMode mode) { /* CS corrected some indices! 27/03/2015 */
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:
      exp = bra(1, N10(A, o), b(o));
      exp += bra(3, 1 / 12 * e_(o, p, q, r, s) * Nb02(A, o, p), b(s) * b(r) * b(q));
      exp += bra(5, 1 / 120 * e_(o, p, q, r, s) * N(A), b(s) * b(r) * b(q) * b(p) * b(o));
      newId("A");
      break;
    case ket:
      exp = ket(1, N10(B, j), bt(j));
      exp += ket(3, 1 / 12 * e_(j, k, l, m, n) * Nb02(B, j, k), bt(l) * bt(m) * bt(n));
      exp += ket(5, 1 / 120 * e_(j, k, l, m, n) * N(B), bt(j) * bt(k) * bt(l) * bt(m) * bt(n));
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  Field(N, 1, 0, ASYM_WITH_FLAVOR);
  Field(Nb, 0, 2, ASYM_WITH_FLAVOR);
  Field(N, 0, 0, ASYM_WITH_FLAVOR);
  return exp;
}

/*!\brief Constructs the ket and bra in the 16th-bar SO(10) representation
\param mode: bra, ket
       id: defines the head of the index, ex: j1, j2, ...
\return bra/ket

 Note that A and B are flavour indices

  OPMode bra:
  \f$\left< \psi^*_{(-)}\right|\f$:
  \f{eqnarray*}{
    \bar{N}_{A\,o} \left< 0\right| b_o
    +\frac{1}{12} \varepsilon_{o,p,q,r,s} \bar{N}^{o,p}_A\left< 0 \right| b_s b_r b_q
    +\frac{1}{120} \varepsilon_{o,p,q,r,s} \bar{N}_A \left< 0 \right| b_s b_r b_q b_p b_o
  \f}

  OPMode ket:
  \f$\left| \psi_{(-)}\right>\f$:
  \f{eqnarray*}{
     \left| 0\right> \bar{M}_B
    + b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right>\frac{1}{12} \varepsilon_{j,k,l,m,n} \bar{M}^{j,k}_B
    +  b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m b^\dagger_n \left| 0\right> \frac{1}{120} \varepsilon_{j,k,l,m,n} \bar{M}_B
  \f}
 */
Braket psi_16m(OPMode mode, string id) {
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:
      exp = bra(1, N10(A, o), b(o));
      exp += Braket(3, "1/12 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * Nb02(A," + makeId(id, 1) + "," + makeId(id, 2) + ")", bb(makeId(id, 5)) * bb(makeId(id, 4)) * bb(makeId(id, 3)), bra);
      exp += Braket(5, "1/120 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * N(A)", bb(makeId(id, 5)) * bb(makeId(id, 4)) * bb(makeId(id, 3)) * bb(makeId(id, 2)) * bb(makeId(id, 1)), bra);
      newId("A");
      break;
    case ket:
      exp = ket(1, N10(B, j), bt(j));
      exp += Braket(3, "1/12 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * Nb02(B," + makeId(id, 1) + "," + makeId(id, 2) + ")",
                    bbt(makeId(id, 3)) * bbt(makeId(id, 4)) * bbt(makeId(id, 5)), ket);
      exp += Braket(5, "1/120 * e_(" + makeId(id, 1) + "," + makeId(id, 2) + "," + makeId(id, 3) + "," + makeId(id, 4) + "," + makeId(id, 5) + ") * N(B)",
                    bbt(makeId(id, 1)) * bbt(makeId(id, 2)) * bbt(makeId(id, 3)) * bbt(makeId(id, 4)) * bbt(makeId(id, 5)), ket);
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  Field(N, 1, 0, ASYM_WITH_FLAVOR);
  Field(Nb, 0, 2, ASYM_WITH_FLAVOR);
  Field(N, 0, 0, ASYM_WITH_FLAVOR);
  return exp;
}

// 144+
/*!\brief Constructs the ket and bra in the 144th-bar SO(10) representation

 Note that A and B are flavour indices

  OPMode bra:
  \f$\left< \psi^*_{(-)}\right|\f$:
  \f{eqnarray*}{
   &&   \frac{2}{\sqrt{5}} P_A^n  \left< 0\right|
      +\frac{1}{12} \left( \varepsilon_{o, p, q, r, s}  P^{n}_{A, q, r, s} - \sqrt{\frac{6}{5}}  \varepsilon_{o, p, n, r, s} P_A^{r, s} \right) \left< 0 \right| b_p b_o
      +\frac{1}{24} \varepsilon_{o, p, q, r, s} P^n_{A,o} \left< 0 \right| b_s b_r b_q b_p\\
    &&  +P_{A, n} \left< 0 \right|
      +\left(  \frac{1}{2} P^{o,p}_{A,n} + \frac{1}{4 sqrt(5)} \left(\delta_{o, n} P^p_A - \delta_{p, n} P^o_A \right)\right) \left< 0 \right| b_p b_o
      +\frac{1}{48} \varepsilon_{o, p, q, r, s} \left(   \sqrt{\frac{6}{5}}  P_{A, o, n} + \sqrt{2}  P^{sym}_{A, o, n} \right) \left< 0 \right| b_s b_r b_q b_p
  \f}

  OPMode ket:
  \f$\left| \psi_{(-)}\right>\f$:
  \f{eqnarray*}{
    &&  \left| 0\right> \frac{2}{\sqrt{5}} P_B^n
      +b^\dagger_i b^\dagger_j \left| 0\right>  \frac{1}{12} \left( \varepsilon_{i,j,k,l,m}  P^{n}_{B, k,l,m} - \sqrt{\frac{6}{5}}  \varepsilon_{i,j,n,l,m} P_B^{l,m} \right)
      +b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m \left| 0\right>  \frac{1}{24} \varepsilon_{i,j,k,l,m} P^n_{B,i} \\
    &&  +\left| 0\right>  P_{B, n}
      +b^\dagger_i b^\dagger_j \left| 0\right>  \left(  \frac{1}{2} P^{o,p}_{B,n} + \frac{1}{4 sqrt(5)} \left(\delta_{i, n} P^j_B - \delta_{j, n} P^i_B \right)\right)
      +b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m \left| 0\right>  \frac{1}{48} \varepsilon_{i,j,k,l,m} \left(   \sqrt{\frac{6}{5}}  P_{B, i, n} + \sqrt{2} P^{sym}_{B, i, n} \right)
  \f}
 */
Braket psi_144p(OPMode mode) {
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:
      exp = bra(1, P10(A, n) * 2 / sqrt(5), identity);
      exp += bra(3, (1 / 12 * e_(o, p, q, r, s) * P13(A, n, q, r, s) - 1 / 12 * e_(o, p, n, r, s) * P02(A, r, s) * sqrt(6 / 5)), b(p) * b(o));
      exp += bra(5, 1 / 24 * e_(o, p, q, r, s) * P11(A, n, o), b(s) * b(r) * b(q) * b(p));
      exp += bra(-1, P01(A, n), identity);
      exp += bra(1, (P21(A, o, p, n) / 2 + (d_(o, n) * P10(A, p) - d_(p, n) * P10(A, o)) / (4 * sqrt(5))), b(p) * b(o));
      exp += bra(3, (1 / 48 * e_(o, p, q, r, s) * (P02(A, o, n) * sqrt(6 / 5) + Ps02(A, o, n) * sqrt(2))), b(s) * b(r) * b(q) * b(p));
      newId("A");
      break;
    case ket:
      exp = ket(1, P10(B, n) * 2 / sqrt(5), identity);
      exp += ket(3, (1 / 12 * e_(i, j, k, l, m) * P13(B, n, k, l, m) - 1 / 12 * e_(i, j, n, l, m) * P02(B, l, m) * sqrt(6 / 5)), bt(i) * bt(j));
      exp += ket(5, 1 / 24 * e_(i, j, k, l, m) * P11(B, n, i), bt(j) * bt(k) * bt(l) * bt(m));
      exp += ket(-1, P01(B, n), identity);
      exp += ket(1, (P21(B, i, j, n) / 2 + (d_(i, n) * P10(B, j) - d_(j, n) * P10(B, i)) / (4 * sqrt(5))), bt(i) * bt(j));
      exp += ket(3, 1 / 48 * e_(i, j, k, l, m) * (P02(B, i, n) * sqrt(6 / 5) + Ps02(B, i, n) * sqrt(2)), bt(j) * bt(k) * bt(l) * bt(m));
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  newId("n");
  Field(P, 1, 0, ASYM_WITH_FLAVOR);
  Field(P, 1, 3, ASYM_WITH_FLAVOR);
  Field(P, 0, 2, ASYM_WITH_FLAVOR);
  Field(P, 1, 1, ASYM_WITH_FLAVOR);
  Field(P, 0, 1, ASYM_WITH_FLAVOR);
  Field(P, 0, 2, SYM_WITH_FLAVOR);
  Field(P, 2, 1, ASYM_WITH_FLAVOR);
  return exp;
}

// 144-
/*!\brief Constructs the ket and bra in the 144th SO(10) representation

 Note that A and B are flavour indices

  OPMode bra:
  \f$\left< \psi^*_{(-)}\right|\f$:
  \f{eqnarray*}{
   &&  \frac{1}{120}  \varepsilon_{o, p, q, r, s}  Q_A^n  \left< 0\right| b_o b_p b_q b_r b_s
    +\frac{1}{12}  \varepsilon_{o, p, q, r, s} \left(    Q^n_{A,o,p} + \frac{1}{2 \sqrt{5}} \left(\delta_{n, o}  Q_{A,p} - \delta_{n, p}  Q_{A, o}\right)  \right)
     \left< 0\right| b_s b_r b_q
    +\frac{1}{2} \left( \sqrt{\frac{6}{5}} Q^{o,n}_A + \sqrt{2} Q^{o,n}_{A\, sym} \right) \left< 0\right| b_o\\
  &&  +Q^o_{A, n} \left< 0 \right|  b_o
    + \frac{1}{72} \varepsilon_{o, p, qq, rr, ss} \left( \varepsilon_{o, p, q, r, s} Q^{q,r,s}_{A,n} - \sqrt{\frac{6}{5}} \varepsilon_{o, p, n, r, s} Q^{r,s}_A\right)
    \left< 0 \right|  b_{ss} b_{rr} b_{qq}
    + \frac{1}{60 \sqrt{5}} \varepsilon_{o, p, q, r, s} Q_{A,n} \left< 0 \right| b_o b_p b_q b_r b_s
  \f}

  OPMode ket:
  \f$\left| \psi_{(-)}\right>\f$:
  \f{eqnarray*}{
   && b^\dagger_i b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m \left| 0\right>  \frac{1}{120}  \varepsilon_{i,j,k,l,m}  Q_B^n
    + b^\dagger_k b^\dagger_l b^\dagger_m \left| 0\right>  \frac{1}{12}  \varepsilon_{i,j,k,l,m} \left( Q^n_{B,i,j} + \frac{1}{2\sqrt{5}}
    \left(  \delta_{n,i} Q_{B,j}-\delta_{n,j} Q_{B,i} \right) \right)
    + b^\dagger_i \left| 0\right> \frac{1}{2} \left( \sqrt{\frac{6}{5}} Q^{i,n}_B + \sqrt{2} Q^{i,n}_{B\, sym}  \right)\\
  &&  + b^\dagger_i b^\dagger_j b^\dagger_k b^\dagger_l b^\dagger_m \left| 0\right>  \frac{1}{60\sqrt{5}}  \varepsilon_{i,j,k,l,m} Q_{B,n}
    + b^\dagger_{kk} b^\dagger_{ll} b^\dagger_{mm} \left| 0\right> \frac{1}{72}  \varepsilon_{i,j,kk,ll,mm}
        \left( \varepsilon_{i,j,k,l,m} Q^{k,l,m}_{B,n} - \sqrt{\frac{6}{5}} \varepsilon_{i,j,n,l,m} Q^{l,m}_B \right)
    + b^\dagger_i \left| 0\right> Q^i_{B,n}
  \f}
 */
Braket psi_144m(OPMode mode) {
  if (getDim() != 10) {
    cout << "This is only for SO(10)...\nExiting..." << endl;
    exit(10);
  }
  Braket exp;
  switch (mode) {
    case bra:

      exp = bra(1, 1 / 120 * e_(o, p, q, r, s) * Q10(A, n), b(o) * b(p) * b(q) * b(r) * b(s));
      exp += bra(4, 1 / 12 * e_(o, p, q, r, s) * (Q12(A, n, o, p) + 1 / (2 * sqrt(5)) * (d_(n, o) * Q01(A, p) - d_(n, p) * Q01(A, o))), b(s) * b(r) * b(q));
      exp += bra(2, (1 / 2 * Q20(A, o, n) * sqrt(6 / 5) + 1 / 2 * Qs20(A, o, n) * sqrt(2)), b(o));
      exp += bra(0, Q11(A, o, n), b(o));
      exp += bra(2, 1 / 72 * e_(o, p, qq, rr, ss) * (e_(o, p, q, r, s) * Q31(A, q, r, s, n) - e_(o, p, n, r, s) * Q20(A, r, s) * sqrt(6 / 5)), b(ss) * b(rr) * b(qq));
      exp += bra(-1, 1 / 120 * e_(o, p, q, r, s) * Q01(A, n) * 2 / sqrt(5), b(o) * b(p) * b(q) * b(r) * b(s));
      newId("A");
      break;
    case ket:
      exp = ket(1, Q10(B, n) / 120 * e_(i, j, k, l, m), bt(i) * bt(j) * bt(k) * bt(l) * bt(m));
      exp += ket(4, 1 / 12 * e_(i, j, k, l, m) * (Q12(B, n, i, j) + 1 / (2 * sqrt(5)) * (d_(n, i) * Q01(B, j) - d_(n, j) * Q01(B, i))), bt(k) * bt(l) * bt(m));
      exp += ket(2, (1 / 2 * (Q20(B, i, n) * sqrt(6 / 5) + Qs20(B, i, n) * sqrt(2))), bt(i));
      exp += ket(-1, 1 / 120 * e_(i, j, k, l, m) * Q01(B, n) * 2 / sqrt(5), bt(i) * bt(j) * bt(k) * bt(l) * bt(m));
      exp += ket(2, 1 / 72 * e_(i, j, kk, ll, mm) * (e_(i, j, k, l, m) * Q31(B, k, l, m, n) - e_(i, j, n, l, m) * Q20(B, l, m) * sqrt(6 / 5)), bt(kk) * bt(ll) * bt(mm));
      exp += ket(0, Q11(B, i, n), bt(i));
      newId("B");
      break;
    default:
      cout << "Expression mode not supported: " << mode << endl;
      exit(1);
      break;
  }
  newId("n");
  Field(Q, 1, 0, ASYM_WITH_FLAVOR);
  Field(Q, 0, 1, ASYM_WITH_FLAVOR);
  Field(Q, 1, 1, ASYM_WITH_FLAVOR);
  Field(Q, 2, 0, ASYM_WITH_FLAVOR);
  Field(Q, 2, 0, SYM_WITH_FLAVOR);
  Field(Q, 1, 2, ASYM_WITH_FLAVOR);
  Field(Q, 3, 1, ASYM_WITH_FLAVOR);
  return exp;
}

}  // namespace sospin
