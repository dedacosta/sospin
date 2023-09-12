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

//       braket.h created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

/*!
  \file
  \brief Defintions for all general (initialisation etc.) routines of class Braket.
*/

#ifndef BRAKET_H
#define BRAKET_H

#include <sospin/dlist.h>
#include <sospin/enum.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace sospin {

/*! \brief Activate internal simplifications based on the Braket Index sum. This option is activated by default.*/
void setSimplifyIndexSum();

/*! \brief Deactivate internal simplifications based on the Braket Index sum */
void unsetSimplifyIndexSum();

/*!
  \class BraketOneTerm class
  \brief Store each term of the Braket class
*/
class BraketOneTerm {
 private:
  /*! \brief Store the index sum */
  int index;
  /*! \brief Store the constant part */
  string constpart;
  /*! \brief Store the part with b and b\daggers and/or delta or identity */
  list<DList> term;

  /*! \brief Reduce number of b's plus b\dagger's to 2N of SO(2N),
      and order all b's at left and all b\dagger's at right
      \param[in]  oper  OPMode of current expression (none, bra, ket, braket)
      \return true if expression is zero/empty and false otherwise
  */
  bool EvaluateEps_1stPass(OPMode oper);

  /*! \brief Convert current expression term to levi-civita
      and writes all in the string/constant part only if expression term is a braket
      \param oper expression type, OPMode
*/
  void EvaluateEps_2ndPass(OPMode oper);

 public:
  /*! \brief Constructor */
  BraketOneTerm();
  /*! \brief Constructor without constant part and index zero
      \param[in] d0 DList expression
  */
  BraketOneTerm(const DList &d0);
  /*! \brief Constructor
      \param[in] indexin index of the expression
      \param[in] constpartin constant part
      \param[in] d0 DList expression
  */
  BraketOneTerm(int indexin, string constpartin, const DList &d0);
  /*! \brief Constructor
      \param[in] indexin index of the expression
      \param[in] constpartin constant part
      \param[in] termin list<DList> expression
  */
  BraketOneTerm(int indexin, string constpartin, list<DList> termin);
  /*! \brief Constructor
      \param[in] indexin index of the expression
      \param[in] constpartin constant part
      \param[in] termin BraketOneTerm expression
  */
  BraketOneTerm(int indexin, string constpartin, BraketOneTerm &termin);
  /*! \brief Destructor, clear all allocated memory */
  ~BraketOneTerm();
  /*! \brief Clear all allocated memory and sets default parameters */
  void clear();

  /*! \brief Return (and set) the term part*/
  list<DList> &GetTerm();
  /*! \brief Return (and set) the constant part*/
  string &GetConst();
  /*! \brief Return (and set) the index sum part*/
  int &GetIndex();

  /*! \brief Simplify current expression term
    \param[in] oper term mode (bra, braket, ket or none)
    \return true if expression term is empty, false otherwise
  */
  bool Simplify(OPMode operation);
  /*! \brief Check global index in expression term
    \return true if |index| is equal to 0 or N of SO(2N), otherwise returns false
  */
  bool checkindex();

  /*! \brief To pass a expression from form */
  void expfromForm(string a);
  /*! \brief Order nodes of DList in Braket

      First deltas and then b's and b\\dagger's
      and remove the identity node when deltas, b or b^dagger is present
  */
  void rearrange();
  /*! \brief Returns true if expression is empty */
  bool isempty();

  /*! \brief Evaluate the expression term to deltas
    \param[in] oper term mode (bra, braket, ket or none)
    \return true if term is empty or gives zero, otherwise returns false
  */
  bool EvaluateToDeltas(OPMode oper);
  /*! \brief Evaluate the expression term to levi-civita
    \param[in] oper term mode (bra, braket, ket or none)
    \return true if term is empty or gives zero, otherwise returns false
  */
  bool EvaluateToLeviCivita(OPMode oper);

  /*! \brief Negate BraketOneTerm */
  void neg();
  /*! \brief overload operator for BraketOneTerm * constval */
  BraketOneTerm operator*(const string constval);
  /*! \brief overload operator for BraketOneTerm *= constval */
  BraketOneTerm operator*=(const string constval);
  /*! \brief overload operator for BraketOneTerm * L */
  BraketOneTerm operator*(const BraketOneTerm &L);
  /*! \brief overload operator for BraketOneTerm *= L */
  BraketOneTerm operator*=(const BraketOneTerm &L);
  /*! \brief negate operator */
  friend BraketOneTerm operator-(const BraketOneTerm &L);
  /*! \brief stream operator */
  friend ostream &operator<<(ostream &out, const BraketOneTerm &L);
};

/*!
  \class Braket class
  \brief Store expression...
*/
class Braket {
  /*! \brief Store expressions with b's, b^\daggers and delta's*/
  vector<BraketOneTerm> expression;
  /*! \brief Flag to make the term numeration with ostream operator */
  int flag;
  /*! \brief Store type of operation: none, bra, ket or braket*/
  OPMode operation;
  /*! \brief Store the evaluated state of the expression  */
  unsigned int evaluated;
  /*  evaluated = 0 - > not yet evaluated
      evaluated = 1 - > evaluated creating deltas
      evaluated = 2 - > evaluated creating e_(...)... */

 public:
  /*! \brief Constructor, default expression mode is none */
  Braket(void);
  /*! \brief Constructor without constant part and index zero
      \param[in] d0 DList expression
  */
  Braket(const DList &d0);
  /*! \brief Constructor, default expression mode is none
      \param[in] id index of the expression
      \param[in] a constant part
      \param[in] d0 DList expression
  */
  Braket(int id, string a, DList d0);
  /*! \brief Constructor, default expression mode is none
      \param[in] id index of the expression
      \param[in] a constant part
      \param[in] d0 DList expression
      \param[in] op Braket type, i.e., bra/ket/braket/none
  */
  Braket(int id, string a, DList d0, OPMode op);
  /*! \brief Constructor
      \param[in] L Braket expression
  */
  Braket(const Braket &L);
  /*! \brief Constructor
      \param[in] id index of the expression
      \param[in] a constant part
      \param[in] L Braket expression, ignores current constant part of L
      \param[in] op Braket type, i.e., bra/ket/braket/none
  */
  Braket(int id, string a, const Braket &L, OPMode op);
  /*! \brief Constructor, default expression mode is none
      \param[in] term BraketOneTerm expression
  */
  Braket(BraketOneTerm term);
  /*! \brief Constructor
      \param[in] term BraketOneTerm expression
      \param[in] op Braket type, i.e., bra/ket/braket/none
  */
  Braket(BraketOneTerm term, OPMode op);
  /*! \brief Destructor, clear all allocated memory */
  ~Braket();
  /*! \brief Clear all allocated memory and sets default parameters */
  void clear();

  /*! \brief To pass a expression from form */
  void expfromForm(vector<string> a);

  /* \brief Returns the current expression type, it also allows to set new expression type. Expression types: bra/ket/braket or none*/
  OPMode &Type();

  /* \brief Print the Braket expression mode, ie, the type of Braket: bra/ket/braket or none*/
  void mode();

  /*! \brief Evaluate expression
      \param[in] onlydeltas if true evaluate expression to deltas, if false evaluate expression to levi-civita
  */
  void evaluate(bool onlydeltas = true);
  /*! \brief Simplify expression. Apply the following rules:
      \f{eqnarray*}{
     &b_? \left|0\right> = 0 \\
      &\left<0\right| b^\dagger_?  = 0 \\
      &In \left<0\right| ... \left.0\right> \quad the\quad \#b_? = \#b^\dagger_?
      \f}
      Also checks for numeric deltas and evaluates them.
      This function also calls
  */
  void simplify();
  /*! \brief Order nodes of DList in Braket

      First deltas and then b's and b\\dagger's
      and remove the identity node when deltas, b or b^dagger is present
  */
  void rearrange();
  /*! \brief Checks indices in the deltas
   */
  void checkDeltaIndex();
  /*! \brief Sets to zero the indice sum of each expression term
   */
  void gindexsetnull();
  /*! \brief Check global index in expression term if setSimplifyIndexSum()/FlagSimplifyGlobalIndexSum is active
    \return true if |index| is equal to 0 or N of SO(2N), otherwise returns false
  */
  void checkindex();
  /*! \brief Activate expression term numbering for output writing for each term "Local R?="
   */
  void setON();
  /*! \brief Deactivate expression term numbering for output writing for each term "Local R?="
   */
  void setOFF();
  /*! \brief Return number of terms in current expression*/
  int size();
  /*! \brief Return expression term at position given by pos*/
  BraketOneTerm &Get(int pos);
  /*! \brief Return/set the index sum of the term given by pos */
  int &GetIndex(int pos);

  // OPERATORS

  /*! \brief overload operator for Braket = L */
  Braket operator=(const Braket &L);
  /*! \brief overload operator for Braket + L */
  Braket operator+(const Braket &L);
  /*! \brief overload operator for Braket += L */
  Braket operator+=(const Braket &L);
  /*! \brief overload operator for Braket - L */
  Braket operator-(const Braket &L);
  /*! \brief overload operator for Braket -= L */
  Braket operator-=(const Braket &L);
  /*! \brief overload operator for Braket * L */
  Braket operator*(const Braket &L);
  /*! \brief overload operator for Braket *= L */
  Braket &operator*=(const Braket &L);
  /*! \brief overload operator for Braket * constant part */
  Braket operator*(const string constval);
  /*! \brief overload operator for Braket *= constant part */
  Braket operator*=(const string constval);

  /*! \brief overload operator for negate, -L*/
  friend Braket operator-(const Braket &L);

  /*!
  \brief calculate the mode for the multiplication
  \param a mode of the left operand
  \param b mode of the right operand
  \return mode of the multiplication, if this results in an invalid operation the the program exit.
*/
  friend OPMode operator*(const OPMode a, const OPMode b);
  /*!
    \brief calculate the mode for the sum
    \param a mode of the left operand
    \param b mode of the right operand
    \return mode of the sum, if this results in an invalid operation the the program exit.
  */
  friend OPMode operator+(const OPMode a, const OPMode b);
  /*!
    \brief calculate the mode for the subtraction
    \param a mode of the left operand
    \param b mode of the right operand
    \return mode of the subtraction, if this results in an invalid operation the the program exit.
  */
  friend OPMode operator-(const OPMode a, const OPMode b);

  /*! \brief writes expression to ostream */
  friend ostream &operator<<(ostream &out, const Braket &L);
  /*! \brief  writes expression to string */
  friend string &operator<<(string &out, const Braket &L);
  /*! \brief  writes expression to string */
  friend string &operator+(string &out, const Braket &L);
};

/*!
  \brief Get the mode of the expression
  \param a mode of the current expression
  \return the mode in ostream.
*/
ostream &operator<<(ostream &out, const OPMode &a);

}  // namespace sospin

#endif
