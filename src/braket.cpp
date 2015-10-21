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

//       braket.cpp created on 27/02/2015 
//
//      This file contains the functions necessary to do things 
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated	
//


/*!
  \file 
  \brief Defintions for all general (initialisation etc.) routines of class Braket.
*/


#include "index.h"
#include "dlist.h"
#include "timer.h"
#include "progressStatus.h"
#include "braket.h" 
#include "son.h"



namespace sospin {


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


static bool FlagSimplifyGlobalIndexSum = true;

void setSimplifyIndexSum(){
  FlagSimplifyGlobalIndexSum = true;
}

void unsetSimplifyIndexSum(){
  FlagSimplifyGlobalIndexSum = false;
}



  BraketOneTerm::BraketOneTerm(){
    index = 0;
    constpart = "";
  }
  BraketOneTerm::BraketOneTerm(const DList &d0){
    index = 0;
    constpart = "";
    term.push_back(d0);
  }
  BraketOneTerm::BraketOneTerm(int indexin, string constpartin, const DList &d0){
    index = indexin;
    constpartin.erase(std::remove(constpartin.begin(), constpartin.end(), ' '), constpartin.end());
    constpart = constpartin;
    term.push_back(d0);
  }
  BraketOneTerm::BraketOneTerm(int indexin, string constpartin, list<DList> termin){
    index = indexin;
    constpartin.erase(std::remove(constpartin.begin(), constpartin.end(), ' '), constpartin.end());
    constpart = constpartin;
    term = termin;
  }
  BraketOneTerm::BraketOneTerm(int indexin, string constpartin, BraketOneTerm& termin){
    index = indexin;
    //remove spaces from constant part written in a string
    constpartin.erase(std::remove(constpartin.begin(), constpartin.end(), ' '), constpartin.end());
    constpart = constpartin;
    list<DList>::iterator iter;
    for(iter = termin.term.begin(); iter != termin.term.end(); iter++)
      term.push_back(*iter);
  }
  void BraketOneTerm::expfromForm(string a){
    index = 0;
    constpart = a;
  }
  void BraketOneTerm::clear(){
      index = 0;
      constpart.clear();
      term.clear();
  }
  BraketOneTerm::~BraketOneTerm(){
    clear();
  }
  list<DList>& BraketOneTerm::GetTerm(){ return term; }
  string& BraketOneTerm::GetConst(){ return constpart; }
  int& BraketOneTerm::GetIndex(){ return index; }
  bool BraketOneTerm::isempty(){
    if(constpart.empty() && term.empty()) return true;
    return false;
  }


















  Braket::Braket(void){
    flag=0;
    operation = none;
    evaluated = 0;
  } 
  Braket::Braket(const DList &d0){
    flag=0;
    operation = none;
    evaluated = 0;
    BraketOneTerm tmp(d0);
    expression.push_back(tmp);
  }
  Braket::Braket(BraketOneTerm term){
    flag=0;
    evaluated = 0;
    operation = none;
    expression.push_back(term);

  }
  Braket::Braket(BraketOneTerm term, OPMode op){
    flag=0;
    evaluated = 0;
    operation = op;
    expression.push_back(term);

  }
  Braket::Braket(int id, string a, DList d0){
    flag=0;
    evaluated = 0;
    operation = none;
    BraketOneTerm tmp(d0);
    expression.push_back(tmp);
  }
  Braket::Braket(int id, string a, DList d0, OPMode op){
    flag=0;
    evaluated = 0;
    operation = op;
    BraketOneTerm tmp(id, a, d0);
    expression.push_back(tmp);
  }
  Braket::Braket(const Braket &L){
    flag=L.flag;
    expression = L.expression;
    operation = L.operation;
    evaluated = L.evaluated;
  }

  Braket::Braket(int id, string a, const Braket &L, OPMode op){
    flag=0;
    vector< BraketOneTerm >::const_iterator iter;
    for(iter = L.expression.begin(); iter != L.expression.end(); iter++){
      BraketOneTerm tmp0 = (*iter);
      BraketOneTerm tmp(id, a, tmp0);
      expression.push_back(tmp);
    }
    operation = op;
    evaluated = L.evaluated;
  }


  void Braket::expfromForm(vector<string> a){
    flag=0;
    BraketOneTerm tmp;
    for(int i=0; i<a.size();i++){
      tmp.expfromForm(a.at(i));
      expression.push_back(tmp);
    }
    operation = braket;
    evaluated = 2;
  }


  void Braket::clear(){
    expression.clear();
    operation = none;  
    flag = 0;
    evaluated = 0;

  }
  /*!\brief destructor*/
  Braket::~Braket(){
    clear();
  };  


void Braket::setON(){
  flag=1;
}

void Braket::setOFF(){
  flag=0;
}




  /*!\brief Return number of terms in current expression*/
  int Braket::size(){ return expression.size();}

  /*!\brief Return expression term at position given by pos*/
  BraketOneTerm& Braket::Get(int pos){
    if(pos < 0 || pos >= expression.size()){
      cout << "Outside range..." << endl;
      exit(1);
    }
    return expression.at(pos);
  }
  /* \brief Return/set the index sum of the term given by pos */
  int& Braket::GetIndex(int pos){ 
    if(pos < 0 || pos >= expression.size()){
      cout << "Outside range..." << endl;
      exit(1);
    }
    return expression.at(pos).GetIndex();
  }

  OPMode& Braket::Type(){
    return operation;
  }


/*!
  \brief Get the mode of the expression
  \param a mode of the current expression 
  \return the mode in ostream.
*/
ostream& operator<<(ostream& out,const OPMode &a){
  switch( a ) {
  case none: 
    out<<"none";
    break;
  case bra:
    out<<"bra";
    break;		
  case ket:
    out<<"ket";
    break;		
  case braket:
    out<<"braket";
    break;	
  }
  return out;
}


/*!
  \brief calculate the mode for the subtraction
  \param a mode of the left operand
  \param b mode of the right operand
  \return mode of the subtraction, if this results in an invalid operation the the program exit.
*/
OPMode operator-(const OPMode a, const OPMode b){
  if(a!=b){
    cout << "Invalid Operation: " << a << " - " << b << endl;
    exit(1);
  }
  return a;
}
/*!
  \brief calculate the mode for the sum
  \param a mode of the left operand
  \param b mode of the right operand
  \return mode of the sum, if this results in an invalid operation the the program exit.
*/
OPMode operator+(const OPMode a, const OPMode b){ 
  if(a!=b){
    cout << "Invalid Operation: " << a << " + " << b << endl;
    exit(1);
  }
  return a;
}
/*!
  \brief calculate the mode for the multiplication
  \param a mode of the left operand
  \param b mode of the right operand
  \return mode of the multiplication, if this results in an invalid operation the the program exit.
*/
OPMode operator*(const OPMode a, const OPMode b){
  if(a==bra && b==ket) return braket;
  if(a==bra && b==none) return bra;
  if(a==none && b==ket) return ket;
  if(a==none && b==none) return none;
  if(a==braket && b==braket){
    return braket; //must check if expression was evaluated!!!!
  }
  cout << "Operation not permited: " << a << " * " << b << endl;
  exit(1);
}
////////////////////////////////////////////////////
/* \brief Print the Braket expression mode, ie, the type of Braket: bra/ket/braket or none*/
void Braket::mode(){
  cout << "Expression mode: " << operation << endl;
}







int expevaluationtype(int eval0, int eval1){
  if( (eval0 == 0 && eval1 > 0 ) || (eval0 > 0 && eval1 == 0) ){
    cout << "Cannot perform this operation, not all expression were evaluate...\n Exiting..." << endl;
    exit(1);
  }
  else return MAX(eval0, eval1); ///?????????????????????????????????
}





////////////////////////////////////////////////////
Braket Braket::operator=(const Braket &L){ 
  expression=L.expression;
  operation = L.operation; 
  evaluated = L.evaluated;
  return *this;
}




///////////////////////////////////////////////////////////////////////////////////
// OPERATION: negate
BraketOneTerm operator-(const BraketOneTerm &L){
  BraketOneTerm tmp = L;
  if(tmp.term.empty()) tmp.constpart = "-1*"+tmp.constpart;
  else{
    list<DList>::iterator iter;
    for(iter = tmp.term.begin(); iter != tmp.term.end(); iter++)
      (*iter).negate();
  }
  return tmp;
}
void BraketOneTerm::neg(){
  if(term.empty()) constpart = "-1*"+constpart;
  else{
    list<DList>::iterator iter;
    for(iter = term.begin(); iter != term.end(); iter++)
      (*iter).negate();
  }
}

Braket operator-(const Braket &L){
  Braket tmp = L;
  vector< BraketOneTerm >::iterator iter;
  for(iter = tmp.expression.begin(); iter != tmp.expression.end(); iter++)
    (*iter).neg();
  return tmp;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: -= 
Braket Braket::operator-=(const Braket &L){
  operation = operation - L.operation;
  evaluated = expevaluationtype(evaluated, L.evaluated);
  vector< BraketOneTerm >::const_iterator iter;
  for(iter = L.expression.begin(); iter != L.expression.end(); iter++){
    expression.push_back(-(*iter));
  }
  rearrange();
  simplify();
  return *this;

}
Braket Braket::operator-(const Braket &L){
  Braket tmp;
  tmp.operation = operation - L.operation;
  tmp.expression=expression;
  tmp.evaluated = expevaluationtype(evaluated, L.evaluated);

  vector< BraketOneTerm >::const_iterator iter;
  for(iter = L.expression.begin(); iter != L.expression.end(); iter++)\
    tmp.expression.push_back(-(*iter));
  tmp.rearrange();
  tmp.simplify();
  return tmp;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: += 
Braket Braket::operator+=(const Braket &L){
  operation = operation + L.operation;
  evaluated = expevaluationtype(evaluated, L.evaluated);
  vector< BraketOneTerm >::const_iterator iter;
  for(iter = L.expression.begin(); iter != L.expression.end(); iter++)\
    expression.push_back(*iter);
  rearrange();
  simplify();
  return *this;
}
Braket Braket::operator+(const Braket &L){
  Braket tmp;
  tmp.operation = operation + L.operation;
  tmp.expression=expression;
  tmp.evaluated = expevaluationtype(evaluated, L.evaluated);
  vector< BraketOneTerm >::const_iterator iter;
  for(iter = L.expression.begin(); iter != L.expression.end(); iter++)\
    tmp.expression.push_back(*iter);
  tmp.rearrange();
  tmp.simplify();
  return tmp;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: *= string
BraketOneTerm BraketOneTerm::operator*=(const string constval){
  if(constpart.empty()) constpart = constval;
  else constpart += "*" + constval;
  return *this;
} 
Braket Braket::operator*=(const string constval){
  vector< BraketOneTerm >::iterator iter;
  for(iter = expression.begin(); iter != expression.end(); iter++)\
    *iter *= constval;
  return *this;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: * string
BraketOneTerm BraketOneTerm::operator*(const string constval){
  BraketOneTerm tmp;
  tmp.index = index;
  tmp.term = term;
  if(constpart.empty()) tmp.constpart = constval;
  else tmp.constpart = constpart + "*" + constval;
  return tmp;
}
Braket Braket::operator*(const string constval){
  Braket tmp;
  tmp.operation = operation;
  tmp.expression=expression;
  tmp.evaluated = evaluated;
  vector< BraketOneTerm >::iterator iter;
  for(iter = tmp.expression.begin(); iter != tmp.expression.end(); iter++)\
    *iter *= constval;

  return tmp;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: *
BraketOneTerm BraketOneTerm::operator*(const BraketOneTerm &L){
  if( (term.empty() && constpart.empty()) ) return *this;
  if( (L.term.empty() && L.constpart.empty()) ) return L;

  BraketOneTerm tmp;
  tmp.index = index + L.index;
  if(constpart.empty()) tmp.constpart = L.constpart;
  else if(L.constpart.empty()) tmp.constpart = constpart;
  else tmp.constpart = constpart + "*" + L.constpart;

  list<DList>::iterator iter;
  list<DList>::const_iterator liter;    
  if(term.empty()){
    for(liter =L.term.begin(); liter != L.term.end(); liter++)
      tmp.term.push_back((*liter));
  }
  else if(L.term.empty()){
    for(iter = term.begin(); iter != term.end(); iter++)
        tmp.term.push_back((*iter));

  }else{
    for(iter = term.begin(); iter != term.end(); iter++)
      for(liter =L.term.begin(); liter != L.term.end(); liter++)
        tmp.term.push_back((*iter)*(*liter));
  }
  return tmp;
}
Braket Braket::operator*(const Braket &L){
  Braket tmp;
  if(operation==braket && L.operation==braket){
    if(evaluated == 0) {
      cout << operation <<"::::"<< L.operation<<endl;
      cout << "Evaluate both expressions first before doing the multiplication!!!!" << endl;
      cout << "Multiplication between two braket's only allowed after evaluation!!!!" << endl;
      exit(1);
    }
  } 
  tmp.evaluated = expevaluationtype(evaluated, L.evaluated);
  tmp.operation=operation*L.operation;
  vector< BraketOneTerm >::iterator iter;
  vector< BraketOneTerm >::const_iterator liter;
  for(iter = expression.begin(); iter != expression.end(); iter++)
    for(liter =L.expression.begin(); liter != L.expression.end(); liter++)
      tmp.expression.push_back((*iter)*(*liter));
  tmp.rearrange();
  tmp.simplify();
  return tmp;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: *=
Braket& Braket::operator*=(const Braket &L){
  if(operation==braket && L.operation==braket){
    if(evaluated == 0) {
      cout << operation <<"::::"<< L.operation<<endl;
      cout << "Evaluate both expressions first before doing the multiplication!!!!" << endl;
      cout << "Multiplication between two braket's only allowed after evaluation!!!!" << endl;
      exit(1);
    }
  } 
  evaluated = expevaluationtype(evaluated, L.evaluated);
  operation=operation*L.operation;
  vector< BraketOneTerm >::iterator iter;
  vector< BraketOneTerm >::const_iterator liter;
  vector< BraketOneTerm > tmp;
  for(iter = expression.begin(); iter != expression.end(); iter++)
    for(liter =L.expression.begin(); liter != L.expression.end(); liter++)
      tmp.push_back((*iter)*(*liter));
  expression.clear();
  expression = tmp;
  tmp.clear();
  rearrange();
  simplify();
  return *this;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// STREAM OPERATORS
ostream& operator<<(ostream& out, const BraketOneTerm &L){
  if(L.term.empty()) out << L.constpart;
  else{
    if(L.constpart.empty()) out  << "(" << endl;
    else out << "("<<L.constpart<<")" << " * (" << endl;
    list<DList>::const_iterator iter;
    for (iter =L.term.begin(); iter != L.term.end(); iter++){
      out << "\t";
      DList tmp = (*iter);
      tmp.set_begin();
      if(tmp.getSign() == -1) out << " - ";
      if(tmp.getSign() == 1) out << " + ";
      if(tmp.isEmpty()) out << " 0 ";
      else
        while(true) {
          elemType elem = tmp.get();
          if(elem.getType() == 2)
            out << "d_(" << getIdx(elem.getIdx1()) << "," << getIdx(elem.getIdx2())<< ")";
          if(elem.getType() == 0)
            out << "b(" << getIdx(elem.getIdx1()) << ")";
          if(elem.getType() == 1)
            out << "bt(" << getIdx(elem.getIdx1()) << ")";
          if(elem.getType() == 3)
            out << "1";
          if(tmp.isActualLast())
            break;
          else
            out << " * ";
          tmp.shift_right();       
        }
        out << endl;
    }
    out << ")";
  }
  return out;
}

ostream& operator<<(ostream& out, const Braket &L){
  int R=0;
  //static int R=0;
  if(L.expression.size() == 0) out << "Local R" << ++R << " = 0;";
  else 
  for(int i = 0; i < L.expression.size(); i++){
    if(L.flag) out << "Local R" << ++R << " = "; 
    if(L.expression.empty()) out << "0;" << endl;
    else out << L.expression.at(i) << ";" << endl;
  }
  return out;
}


string& operator<<(string& out, const Braket &L){
  return out << L;
}


string& operator+(string& out, const Braket &L){
  return out << L;
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: rearrange()
void BraketOneTerm::rearrange(){
  list<DList>::iterator iter;
  for(iter = term.begin(); iter != term.end(); iter++)
    (*iter) = (*iter).rearrange();
}
void Braket::rearrange(){
  if(evaluated==2) return;
  if(getVerbosity() >= VERBOSE) cout << "Ordering..." << endl;
  int total = expression.size();
  int i = 0;
  DoProgress("Progress: ", 0, total);
  vector< BraketOneTerm >::iterator iter;
  for(iter = expression.begin(); iter != expression.end(); iter++){
    (*iter).rearrange();
    i++;
    DoProgress("Progress: ", i, total);
  }
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: checkindex()
bool BraketOneTerm::checkindex(){ 
  if(index==0 || abs(index)==getDim()/2) return true;
  else return false;
}
void Braket::checkindex(){ 
  if(FlagSimplifyGlobalIndexSum) {
    if(operation == braket){
      if(getVerbosity() >= VERBOSE) cout << "Checking Indices..." << endl;
      int total = expression.size();
      DoProgress("Progress: ", 0, total);
      vector< BraketOneTerm > tmp;
      for (int i = 0; i < expression.size(); i++){
        if(expression.at(i).checkindex()){
          tmp.push_back(expression.at(i));
          expression.at(i).clear();
        } 
        DoProgress("Progress: ", i+1, total);
      }
      expression.clear();
      expression = tmp;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: gindexsetnull()
void Braket::gindexsetnull(){
    if(getVerbosity() >= VERBOSE) cout << "Setting global indice terms to zero..." << endl;
    int total = expression.size();
    DoProgress("Progress: ", 0, total);
    for (int i = 0; i < expression.size(); i++){
      expression.at(i).GetIndex() = 0;
      DoProgress("Progress: ", i+1, total);
    }
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
// OPERATION: Simplify()
bool BraketOneTerm::Simplify(OPMode operation){
  list<DList>::iterator iter = term.begin();
  while(iter != term.end()){
    bool checkop = false;
    switch( operation ) {
    case none:
      if( (*iter).checkDeltaIndex() )
        checkop = true;
      break;
    case bra:
      if( (*iter).search_first(1,0) )
        if( (*iter).checkDeltaIndex() )
          checkop = true;
      break;    
    case ket:
      if( (*iter).search_last(0) )
        if( (*iter).checkDeltaIndex() )
          checkop = true;
      break;    
    case braket:
      if( (*iter).check_same_num() )
        if( (*iter).search_last(0) )
          if( (*iter).search_first(1,0) )
      if( (*iter).checkDeltaIndex() )
        checkop = true;
      break;  
    }
    if(!checkop) {
      (*iter).clear();
      iter = term.erase(iter);
    }
    else{
      ++iter;
    }
  }
  if(term.empty()) {
    clear();
    return true;
  }
  return false;
}
void Braket::simplify(){
  checkindex();
  if(evaluated != 2){
    if(getVerbosity() >= VERBOSE) cout << "Simplifying expression..." << endl;
    int total = expression.size();
    int i = 0;
    DoProgress("Progress: ", i, total);
    vector< BraketOneTerm > tmp;
    for (i = 0; i < expression.size(); i++){
      BraketOneTerm tmp0;
      tmp0 = expression.at(i);
      if(!tmp0.Simplify(operation)) tmp.push_back(tmp0);
      DoProgress("Progress: ", i+1, total);
    }
    expression.clear();
    expression = tmp;
  }
}









string GetLeviCivita(vector < string> id0, vector < string> id1){
  string epsB = "e_(";
  string epsBdagger = "e_(";
  //Number of B's and B\dagger's are the same, every call to simplify removes non-valid/null terms!!!!
  for(int j = 0; j < id0.size(); j++){
    epsB += id0.at(j);              
    epsBdagger += id1.at(id1.size() - 1 - j);
    if(j < getDim() / 2 - 1) {
      epsB += ",";
      epsBdagger += ",";
    }
  }
  int idadd = 1;
  int factor=1;
  if(id0.size() < getDim() / 2){
    int len = getDim() / 2 - id0.size();
    for(int j = 0; j < len; j++){
      string addrem = "t" + ToString<int>(idadd);
      newId(addrem);
      factor *= idadd;
      idadd++;
      epsB += addrem;
      epsBdagger += addrem;
      if(j < len - 1) {
        epsB += ",";
        epsBdagger += ",";
      }
    }
  }
  epsB += ")";
  epsBdagger += ")";
  string levciviexp = epsB + "*" + epsBdagger;
  if(factor > 1)
    levciviexp += "/" + ToString<int>(factor);
  return levciviexp;
}



/*! \brief Convert current expression term to levi-civita
    and writes all in the string/constant part only if expression term is a braket
    \param oper expression type, OPMode
*/
void BraketOneTerm::EvaluateEps_2ndPass(OPMode oper ){
  if(oper != braket) return;
  list<DList>::iterator iter = term.begin();
  string constpartout = "*(\n";
  if(constpart.empty()) constpartout = "(\n";
  while (iter != term.end()){
    if((*iter).isEmpty()==false){
      vector < string> id0;
      vector < string> id1;
      int sign0 = 1; 
      bool bandbdagger = false;
      (*iter).getBandBdaggerIds(bandbdagger, id0, id1, sign0);
      if( sign0 == -1) constpartout+= "-";
      if( sign0 == 1) constpartout+= "+";
      string deltas = printDeltas((*iter));
      constpartout += deltas;
      if(bandbdagger && deltas.empty()==false) constpartout+= "*";
      if(bandbdagger) 
        constpartout += GetLeviCivita(id0, id1);
      constpartout += "\n";
    }
    ++iter;
  }
  constpartout += ")";
  term.clear();
  constpart += constpartout;
  constpartout.clear();
}







/*!
  \brief Evaluate expression in order to left all b's in left side and b^daggers in right side
  \param[in,out] Toeval expression term to evaluate
  \param oper expression type, OPMode
*/
void OrderBandBdaggers(list<DList> &Toeval, OPMode oper){
  list<DList>::iterator iter = Toeval.begin();
  bool braketmode = false;
  if(oper == braket) braketmode = true;
  while (iter != Toeval.end()){
    bool inc_iter = true;
    if((*iter).isEmpty()==false){
      DList LL;
      LL << (*iter);
      vector<int> ids = LL.getIds();
      bool ordered = false;
      vector<int> ids0 = ids;
      sort (ids0.begin(), ids0.end()); 
      if(ids0 == ids) ordered = true;
      if(ordered == false)
      while(true){
        DList L;
        L << (*iter);
        ids = L.getIds();
        ids0 = ids;
        sort (ids0.begin(), ids0.end()); 
        if(ids0 == ids) ordered = true;
        if(ordered) break;
        DList M;
        M = ordering(L, braketmode);
        if(M.isEmpty() == false){
          if(oper == ket || oper == braket ){ 
            M.search_last(0);
            if(M.isActualLast()==false){
              Toeval.push_back(M);
            }
          }
          else Toeval.push_back(M);
        }
        if(L.isEmpty()) {
          (*iter).clear();  
            iter = Toeval.erase(iter);
            inc_iter = false;
          break;
        }
        else if(oper == ket || oper == braket){
          L.search_last(0);
          if(L.isActualLast()) {
            (*iter).clear();    
            iter = Toeval.erase(iter);
            inc_iter = false;
            break;
        }
        }
        (*iter) = L;
      } 
    }
    if(inc_iter) ++iter;
  }
}



/*!
  \brief Evaluate expression in order to have the number of b's plus b^daggers equal to N of SO(N)
  \param[in,out] Toeval expression term to evaluate
  \param oper expression type, OPMode
*/
void ReduceNumberOfBandBdaggers(list<DList> &Toeval, OPMode oper){
  list<DList>::iterator iter = Toeval.begin();
  bool braketmode = false;
  if(oper == braket) braketmode = true;
  while (iter != Toeval.end()){
    bool inc_iter = true;
    if((*iter).isEmpty()==false)
    if((*iter).search_last(0))
      while(true){
        if((*iter).search_elem(0)==false) break;
        if((*iter).numBs()<=getDim()/2) break;
        DList L;
        L << (*iter);
        DList M;
        M = contract_deltas(L, braketmode);
        if(M.isEmpty() == false){
          if(oper == ket || oper == braket ){
            M.search_last(0);
            if(M.isActualLast()==false){
              Toeval.push_back(M);
            }
          }
          else Toeval.push_back(M);
        }
        if(L.isEmpty()) {
          (*iter).clear(); 
            iter = Toeval.erase(iter);
            inc_iter = false;
          break;
        }
        else if(oper == ket || oper == braket){ 
          L.search_last(0);
          if(L.isActualLast()) {
            (*iter).clear();  
            iter = Toeval.erase(iter);
            inc_iter = false;
            break;
        }
        }
        (*iter) = L;
      } 
    if(inc_iter) ++iter;
  }
}



/*! \brief Reduce number of b's plus b\dagger's to 2N of SO(2N), 
    and order all b's at left and all b\dagger's at right 
    \param[in]  oper  OPMode of current expression (none, bra, ket, braket)
    \return true if expression is zero/empty and false otherwise
*/
bool BraketOneTerm::EvaluateEps_1stPass(OPMode oper ){
    //evaluate expression in order to have b's+b^daggers <= N of SO(N)
    ReduceNumberOfBandBdaggers(term, oper); 
    // evaluate expression in order to have all b's at the left side and b^daggers at right side
    OrderBandBdaggers(term, oper); 
    if(term.empty()) return true;
    return false;
}

/*! \brief Evaluate the expression term to levi-civita
  \param[in] oper term mode (bra, braket, ket or none)
  \return true if term is empty or gives zero, otherwise returns false
*/
bool BraketOneTerm::EvaluateToLeviCivita(OPMode oper ){
    EvaluateEps_1stPass(oper);
    if(term.empty()) return true;
    EvaluateEps_2ndPass(oper);
    return false;
}



/*! \brief Evaluate the expression term to deltas
  \param[in] oper term mode (bra, braket, ket or none)
  \return true if term is empty or gives zero, otherwise returns false
*/
bool BraketOneTerm::EvaluateToDeltas(OPMode oper ){
  list<DList>::iterator iter = term.begin();
  bool braketmode = false;
  if(oper == braket) braketmode = true;
  while (iter != term.end()){
    bool inc_iter = true;
    if((*iter).isEmpty()==false)
    if((*iter).search_last(0))
      while(true){
        if((*iter).search_elem(0)==false) break;
        if( oper == none && ((*iter).search_elem(0)==false || (*iter).search_elem(1)==false) ) break; 
        DList L;
        L << (*iter);
        DList M;
        M = contract_deltas(L, braketmode);
        if(M.isEmpty() == false){
          if(oper == ket || oper == braket ){ 
            M.search_last(0);
            if(M.isActualLast()==false){
              term.push_back(M);
            }
          }
          else term.push_back(M);
        }
        if(L.isEmpty()) {
          (*iter).clear(); 
          iter = term.erase(iter);
          inc_iter = false;
          break;
        }
        else if(oper == ket || oper == braket){ 
          L.search_last(0);
          if(L.isActualLast()) {
            (*iter).clear();  
            iter = term.erase(iter);
            inc_iter = false;
            break;
          }
        }
        (*iter) = L;
      } 
    if( inc_iter) ++iter;
  }
  if(term.empty()){
    constpart.clear();
    index = 0;
    return true;
  }
  return false;
}


  /*! \brief Evaluate expression 
      \param[in] onlydeltas if true evaluate expression to deltas, if false evaluate expression to levi-civita
  */
void Braket::evaluate(bool onlydeltas){
  if(getVerbosity() >= VERBOSE) cout << "Evaluating Expression..." << endl;
  if(getVerbosity() == DEBUG_VERBOSE) print_process_mem_usage();
  simplify(); 
  if(evaluated==0){
    if(getVerbosity() == DEBUG_VERBOSE) print_process_mem_usage();
    if(onlydeltas){
      vector< BraketOneTerm >::iterator iter = expression.begin();
      int i = 0;
      int total = expression.size();
      DoProgress("Progress: ", i, total);
      while(iter != expression.end()){
        if((*iter).EvaluateToDeltas(operation)){
          (*iter).clear();
          iter = expression.erase(iter);
        }
        else ++iter;
        i++;
        DoProgress("Progress: ", i, total);
      }
      if(operation == braket)  evaluated = 1;
    }
    else{
      if(operation != braket) return;
      int i = 0;
      int total = expression.size();
      DoProgress("Progress: ", i, total);
      vector< BraketOneTerm >::iterator iter = expression.begin();
      while(iter != expression.end()){
        if((*iter).EvaluateToLeviCivita(operation)){
          (*iter).clear();
          iter = expression.erase(iter);
        }
        else ++iter;
        i++;
        DoProgress("Progress: ", i, total);
      }
      if(operation == braket) evaluated = 2;
    }
    if(getVerbosity() == DEBUG_VERBOSE) print_process_mem_usage();
  }
  if(evaluated>0) gindexsetnull();
}






}
