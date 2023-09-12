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

//       SO10.h created on 24/03/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 24/03/2015 23:19:29 david
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

/*!
  \file
  \brief Specific functions for SO(10) group.
*/

#ifndef SO10_H
#define SO10_H

#include <sospin/braket.h>
#include <sospin/enum.h>

#include <string>

namespace sospin {

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
Braket psi_16p(OPMode mode, string id);

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
Braket psi_16m(OPMode mode, string id);

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
Braket psi_16p(OPMode mode);

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
Braket psi_16m(OPMode mode);

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
Braket psi_144p(OPMode mode);

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
Braket psi_144m(OPMode mode);

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
Braket GammaH(int n);

}  // namespace sospin

#endif /* SO10_H */
