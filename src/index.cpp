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

//       index.cpp created on 27/02/2015
//
//      This file contains the functions necessary to do things
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//

/*!
  \file
  \brief Functions and cointainer for indexes.
*/


#include "index.h"
#include <iostream>



using namespace std;




namespace sospin {

/*!
\brief Vector container of the indexes
*/
vector<string> tabids;
////////////////////////////////////////////////////

int Idx_size(){
  return tabids.size();
}


string makeId(string a, int id){

  newId(a+ToString<int>(id));
  return a+ToString<int>(id);
}

void printIDX(){
  cout << "================================================================" << endl;
  for(int j=0; j < tabids.size(); j++){
      cout << tabids.at(j);
      if(j < tabids.size()-1) cout << ",";
    }
  cout << "\n================================================================" << endl;
}


/*!
\brief Store new index of type "int"
*/
int newIdx(int i){
  //tabids.push_back( ToString<int>(i) );
  //return tabids.size()-1;
  string addidx = ToString<int>(i);
  int pos=-1;
  for(int j=0; j < tabids.size(); j++){
    if(addidx==tabids.at(j)){
      pos = j;
      break;
    }
  }
  if(pos==-1){
    tabids.push_back( addidx );
    pos = tabids.size()-1;
  }
  return pos;
}
/*!
\brief Store new index of type "string"
*/
int newIdx(string i){
  //tabids.push_back(i);
  //return tabids.size()-1;
  int pos=-1;
  for(int j=0; j < tabids.size(); j++){
    if(i==tabids.at(j)){
      pos = j;
      break;
    }
  }
  if(pos==-1){
    tabids.push_back( i );
    pos = tabids.size()-1;
  }
  return pos;
}
/*!
\brief Store new index of type "string"
*/
void newId(string i){
  //tabids.push_back(i);
  int pos=-1;
  for(int j=0; j < tabids.size(); j++){
    if(i==tabids.at(j)){
      pos = j;
      break;
    }
  }
  if(pos==-1)
    tabids.push_back( i );
}
/*!
\brief Get index
\param i position of the index
\return index in position @a i
*/
string getIdx(int i){
  return tabids.at(i);
}

/*!
\brief Index list
\return index list in string of the form "Indices ?,...,?";
*/
string IndexList(){
  vector<string> indexlist;
  indexlist = tabids;
  vector<string>::iterator it;
  sort (indexlist.begin(), indexlist.end());
  it = unique (indexlist.begin(), indexlist.end());
  indexlist.resize( it - indexlist.begin() );

  //string idx="Indices ";
  string idx="";
  for(int i=0; i<indexlist.size(); i++){
    //check for numeric indexes and remove them...
    std::istringstream iss(indexlist.at(i));
    int num = 0;
    if (!(iss >> num).fail()) continue;
    idx += indexlist.at(i);
    if(i!=indexlist.size()-1)
      idx += ", ";
    else
      idx += ";";
  }
  indexlist.clear();
  return idx;
}

/*!
\brief convert to string
*/
template<class T>
string ToString(T number)
{
  stringstream ss;//create a stringstream
  ss << number;//add number to the stream
  return ss.str();//return a string with the contents of the stream
}

template string ToString<int>(int number);
template string ToString<unsigned int>(unsigned int number);
template string ToString<float>(float number);
template string ToString<double>(double number);

}
