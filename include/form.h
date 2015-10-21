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

//       form.h created on 27/02/2015 
//
//      This file contains the functions necessary to do things 
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated	
//

/*!
  \file 
  \brief Functions and tables to use with FORM program.
*/

#ifndef FORM_H
#define FORM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>

#include "braket.h"
#include "index.h"




namespace sospin {

#define addFunction(a) form.function(#a)
#define addFC(a) form.contractions(a)

using namespace std;





/*! \brief Set "renumber 1;" in FORM input file.
    This option is used to renumber indices in order to allow further simplifications
    However, in big expressions this must be avoid since it increases the computational time in FORM
    The best way to use is simplify the expression with FORM with this option unset, and then send a second time to FORM
    with this option active.

    By default this option is unset.
*/
void setFormRenumber();
/*! \brief Unset "renumber 1;" in FORM input file.

    Default option is unset.
*/
void unsetFormRenumber();

/*! \brief Set the index sum in input FORM file, ie, 
    adds "sum i,j,...;" and "id e_(1,...,N) = 1"
    
    By default this option is activated.
*/
void setFormIndexSum();
/*! \brief Unset the index sum in input FORM file.
*/
void unsetFormIndexSum();



/*! \brief Function to add field name and create field proprieties to FORM input file.
    \param[in] fieldname, name of the field
    \param[in] numUpperIds, number of upper indices
    \param[in] numLowerIds, number of lower indices
    \param[in] funcp, field type. Allowed options are: SYM (symmetric without flavor indice), 
    ASYM (antisymmetric without flavor indice), SYM_WITH_FLAVOR (symmetric with flavor indice) and 
    ASYM_WITH_FLAVOR (antisymmetric with flavor indice)
    \return return the field name in std::string type to show as a field must be declared inside a Braket.
*/
string FormField(const string fieldname, const unsigned int numUpperIds, const unsigned int numLowerIds, \
                const FuncProp funcp);

/*!
\brief Creat the file input for FORM and run the FORM program and return the result to file and/or screen
\param[in,out] exp Braket expression
\param print if @a TRUE prints final result to screen
\param all if @a TRUE write all the expression members separately in ouput FORM file, if @ FALSE only writes the full result together.
*/
void CallForm(Braket &exp, bool print=true, bool all=true, string newidlabel="j");

/*!
  \class ToForm class
  \brief Container for form specifications
*/
class ToForm { 
  /*!
  \brief Function declaration storage
  */
  vector<string> Functions;
  /*!
  \brief Function contractions storage
  */
  vector<string> FormContraction;
  /*!
  \brief Form input/output filename, input(output) filename is given by filename_in(_out).frm
  */
  string filename;
  /*!
  \brief Path to Form file
  */
  string resource_path;
  /*!
  \brief Set(true) or unset(false) "renumber 1;" in FORM
  */
  bool formRenumber;

  /*!
  \brief Set(true) or unset(false) indice sum in FORM, useful when using expressions without fields
  */
  bool indexSum;
  public:
  /*! \brief Constructor */
  ToForm(void);
  /*! \brief Destructor */
  ~ToForm();
  /*! Clear all allocated memory and sets default values */
  void clear();
  /*! Store a field name */
  bool function(string f);
  /*! Store all field contractions */
  void contractions(string f);
  /*!
    \brief Return all type of contractions for the fields
  */
  string getFC();
  /*!
    \brief Returns all the field names
  */
  string getFunction();

  /*!
    \brief Sets the beginning of a input/output FORM file
  */  
  void setFilename(string name);
  /*!
    \brief Returns the beginning of a input/output FORM file
  */  
  string file(){return filename;}
  /*!
    \brief Returns the full path name and form binary file
  */  
  string& rpath(){return resource_path;}
  /*!
    \brief Simplify expression in FORM.
     Create file input for FORM and run the FORM program and return the result to file and/or screen
    \param[in,out] exp Braket expression to be simplified in FORM, the result is written back
    \param[in] print if @a TRUE prints final result to screen
    \param[in] all if @a TRUE write all the expression members separately in ouput FORM file, if @ FALSE only writes the full result together.
    \param[in] new indice label to be used when teh option to sum indices is active 
  */ 
  void run(Braket &exp, bool print, bool all, string newidlabel);
  /*! Returns the state of the indexSum flag  */
  bool getIndexSum();
  /*! Sets the state of the indexSum flag  */
  void setIndexSum(bool flag);

  /*! \brief Set "renumber 1;" in FORM input file.
      This option is used to renumber indices in order to allow further simplifications
      However, in big expressions this must be avoid since it increases the computational time in FORM
      The best way to use is simplify the expression with FORM with this option unset, and then send a second time to FORM
      with this option active.

      By default this option is unset.
  */
  void setRenumber(bool flag=true);
  /*! Returns the state of the formRenumber flag  */
  bool getRenumberOption();


  ToForm& operator<<(const string &func);
  ToForm& operator+(const string &func);
};

extern ToForm form;



}


 
#endif
