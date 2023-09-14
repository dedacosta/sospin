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

//       index.h created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      Revision 1.2 29/04/2015 17:34:00 nunogon
//      License updated
//      Revision 1.3 12/09/2023 16:53:51 david

/*!
  \file
  \brief Functions and cointainer for indices.
*/

#ifndef INDEX_H
#define INDEX_H

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace sospin {

/*! \brief Vector container of the indexes.*/
extern vector<string> tabids;

/*! \brief Store new index of type "int".*/
int newIdx(int i);

/*! \brief Store new index of type "string".*/
int newIdx(string i);

/*! \brief Return index in position @ the position "i".*/
string getIdx(int i);

/*! \brief Return index list in string of the form "Indices ?,...,?".*/
string IndexList();

/*! \brief Store new index of type "string".*/
void newId(string i);

/*! \brief Return index list size.*/
int Idx_size();

/*! \brief return in string format "a+id"*/
string makeId(string a, int id);

/*! \brief print index list.*/
void printIDX();

/*! \brief Convert to string.*/
template <class T>
string ToString(T number);

}  // namespace sospin

#endif
