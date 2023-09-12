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

//       form.cpp created on 27/02/2015
//
//      This file is an integrant part of the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      License updated
//      Revision 1.2 12/09/2023 16:53:51 david

/*!
  \file
  \brief Functions and tables to use with FORM program.
*/

#include <sospin/dlist.h>
#include <sospin/form.h>
#include <sospin/son.h>
#include <sys/stat.h>  // for stat()

using namespace std;

namespace sospin {

ToForm form;

ToForm::ToForm(void) {
  filename = "form";
  formRenumber = false;
  resource_path = "";
  indexSum = true;
}

ToForm::~ToForm() {
  clear();
}

void ToForm::clear() {
  Functions.clear();
  FormContraction.clear();
  resource_path.clear();
  formRenumber = false;
  indexSum = true;
  filename = "form";
}

bool ToForm::getRenumberOption() {
  return formRenumber;
}

bool ToForm::getIndexSum() {
  return indexSum;
}

void ToForm::setIndexSum(bool flag) {
  indexSum = flag;
}

void ToForm::setRenumber(bool flag) {
  formRenumber = flag;
  if (formRenumber)
    cout << "Setting \"renumber 1;\" in FORM" << endl;
  else
    cout << "UnSetting \"renumber 1;\" in FORM" << endl;
}

void ToForm::setFilename(string name) {
  filename = name;
}

/*! \brief Set "renumber 1;" in FORM input file.
    This option is used to renumber indices in order to allow further simplifications
    However, in big expressions this must be avoid since it increases the computational time in FORM
    The best way to use is simplify the expression with FORM with this option unset, and then send a second time to FORM
    with this option active.

    By default this option is unset.
*/
void setFormRenumber() {
  form.setRenumber(true);
}

/*! \brief Unset "renumber 1;" in FORM input file.

    Default option is unset.
*/
void unsetFormRenumber() {
  form.setRenumber(false);
}

/*! \brief Set the index sum in input FORM file, ie,
    adds "sum i,j,...;" and "id e_(1,...,N) = 1"

    By default this option is activated.
*/
void setFormIndexSum() {
  form.setIndexSum(true);
}

/*! \brief Unset the index sum in input FORM file.
 */
void unsetFormIndexSum() {
  form.setIndexSum(false);
}

/*! \brief Function to add field name and create field proprieties to FORM input file.
    \param[in] fieldname, name of the field
    \param[in] numUpperIds, number of upper indices
    \param[in] numLowerIds, number of lower indices
    \param[in] funcp, field type. Allowed options are: SYM (symmetric without flavor indice),
    ASYM (antisymmetric without flavor indice), SYM_WITH_FLAVOR (symmetric with flavor indice) and
    ASYM_WITH_FLAVOR (antisymmetric with flavor indice)
    \return return the field name in std::string type to show as a field must be declared inside a Braket.
*/
string FormField(const string fieldname,
                 const unsigned int numUpperIds, const unsigned int numLowerIds,
                 const FuncProp funcp) {

  bool flavorid = false;
  if (funcp == ASYM_WITH_FLAVOR || funcp == SYM_WITH_FLAVOR) flavorid = true;
  // construct function name to form
  string fname;
  if (funcp == SYM || funcp == SYM_WITH_FLAVOR)
    fname = fieldname + "s";
  else
    fname = fieldname;
  if (numLowerIds > 0 || numUpperIds > 0) {
    fname += ToString<unsigned int>(numUpperIds) + ToString<unsigned int>(numLowerIds);
  }
  string functionheader = fname;
  // when flavor id is present we cannot aggregate symmetric/antisymmetric to the field...
  // if no lower and upper indices, still adds (anti)symmetric...
  if (!flavorid && (numLowerIds == 0 || numUpperIds == 0)) {
    if (funcp == SYM || funcp == SYM_WITH_FLAVOR)
      functionheader += "(symmetric)";
    else
      functionheader += "(antisymmetric)";
  }
  // Store function name to include in form input file header Functions
  // and check if the function/field is already defined...
  bool newfunc = form.function(functionheader);
  // if this function is a new function...
  if (newfunc) {
    //////////////////////////////////////////////////////////
    // field contractions
    bool fieldctr = false;
    // Deal with or without flavor id...
    if (!flavorid && (numLowerIds > 0 && numUpperIds > 0)) fieldctr = true;
    if (flavorid && (numLowerIds > 0 || numUpperIds > 0)) fieldctr = true;
    if (fieldctr) {
      string tmp, idnum;
      int idinc = 0;
      if (flavorid) idinc = 1;
      if (funcp == SYM || funcp == SYM_WITH_FLAVOR)
        tmp = "symmetrize  " + fname + " ";
      else
        tmp = "antisymmetrize  " + fname + " ";
      idnum = "";
      if (numUpperIds > 1) {
        for (unsigned int i = 0; i < numUpperIds; i++) {
          idinc++;
          idnum += ToString<int>(idinc);
          if (i < numUpperIds - 1) idnum += ",";
        }
        idnum += ";";
        idnum = tmp + idnum;
        // add it to form defs
        form + idnum;
        // cout << "defL: " << idnum << endl;
      }
      if (numLowerIds > 1) {
        idnum = "";
        idinc = 0;
        if (flavorid) idinc = 1;
        for (unsigned int i = 0; i < numLowerIds; i++) {
          idinc++;
          idnum += ToString<int>(idinc + numUpperIds);
          if (i < numLowerIds - 1) idnum += ",";
        }
        idnum += ";";
        idnum = tmp + idnum;
        // add it to form defs
        form + idnum;
      }
    }
    // form def for upper indice repeated with a lower indice...
    if (numUpperIds > 0 && numLowerIds > 0) {
      string tmp = "id " + fname + "(";
      if (flavorid) {
        tmp += "i0?,";
        newId("i0");
      }
      newId("x");
      for (unsigned int i = 1; i <= numUpperIds; i++) {
        for (unsigned int j = 1; j <= numLowerIds; j++) {
          string tmp1 = tmp;
          for (unsigned int k = 1; k <= (numUpperIds + numLowerIds); k++) {
            if (k == i || k == (j + numUpperIds))
              tmp1 += "?x";
            else {
              tmp1 += "i" + ToString<int>(k) + "?";
              newId("i" + ToString<int>(k));
            }
            if (k < (numUpperIds + numLowerIds))
              tmp1 += ",";
            else
              tmp1 += ")=0;";
          }
          form + tmp1;
        }
      }
    }
    // lower indices repeated...
    if (numUpperIds > 1 && numLowerIds > 0) {
      string tmp = "id " + fname + "(";
      if (flavorid) {
        tmp += "i0?,";
        newId("i0");
      }
      newId("x");
      for (unsigned int i = 1; i <= numUpperIds; i++) {
        for (unsigned int j = i + 1; j <= numUpperIds; j++) {
          string tmp1 = tmp;
          for (unsigned int k = 1; k <= (numUpperIds + numLowerIds); k++) {
            if (k == i || k == j)
              tmp1 += "?x";
            else {
              tmp1 += "i" + ToString<int>(k) + "?";
              newId("i" + ToString<int>(k));
            }
            if (k < (numUpperIds + numLowerIds))
              tmp1 += ",";
            else
              tmp1 += ")=0;";
          }
          form + tmp1;
          // cout << tmp1 << endl;
        }
      }
    }
    // upper indices repeated...
    if (numUpperIds > 0 && numLowerIds > 1) {
      string tmp = "id " + fname + "(";
      if (flavorid) {
        tmp += "i0?,";
        newId("i0");
      }
      newId("x");
      for (unsigned int i = 1; i <= numLowerIds; i++) {
        for (unsigned int j = i + 1; j <= numLowerIds; j++) {
          string tmp1 = tmp;
          for (unsigned int k = 1; k <= (numUpperIds + numLowerIds); k++) {
            if (k == (i + numUpperIds) || k == (j + numUpperIds))
              tmp1 += "?x";
            else {
              tmp1 += "i" + ToString<int>(k) + "?";
              newId("i" + ToString<int>(k));
            }
            if (k < (numUpperIds + numLowerIds))
              tmp1 += ",";
            else
              tmp1 += ")=0;";
          }
          form + tmp1;
          // cout << tmp1 << endl;
        }
      }
    }
  }
  return fname;
}

/*!
  \brief Store a field, one at each time
  \f$H^{ij}_{klm}\f$
  \par this is declared as
\code
form.function("H23");
\endcode

the first number (2) after the field name corresponds to the number of up indices

and the second (3) for the lower indices

if there are no up or lower indices then the respective position is filled with the zero number, "0".
*/
bool ToForm::function(string func) {
  std::vector<string>::iterator it;
  it = find(Functions.begin(), Functions.end(), func);
  if (it == Functions.end()) {
    Functions.push_back(func);
    return true;
  }
  return false;
}

/*!
  \brief Store a type of contractions for the fields and (anti)symmetric options
  \f$H^{ij}_{klm}\f$
  \par is writted as "H23(i,j,k,l,m)" in bra/ket/braket constant part
\code
form.contractions("antisymmetrize H23 1,2;");
form.contractions("antisymmetrize H23 3,4,5;");
\endcode

The first entry corresponds to the antisymmetrization of the first two indices (upper indices) and the second to the antisymmetrization of the three lower indices

if there is only one or no indice there is no need to declare it.
*/
void ToForm::contractions(string func) {
  std::vector<string>::iterator it;
  it = find(FormContraction.begin(), FormContraction.end(), func);
  if (it != FormContraction.end()) FormContraction.push_back(func);
}

/*!
  \brief Return all type of contractions for the fields
*/
string ToForm::getFC() {
  string func = "";
  for (size_t i = 0; i < FormContraction.size(); i++) {
    func += FormContraction.at(i);
    func += "\n";
  }
  return func;
}

/*!
  \brief Returns all the fields
*/
string ToForm::getFunction() {
  string func = "";
  if (Functions.empty() == false) {
    func = "Functions ";
    for (size_t i = 0; i < Functions.size(); i++) {
      func += Functions.at(i);
      if (i == Functions.size() - 1)
        func += ";\n";
      else
        func += ", ";
    }
  }
  return func;
}

/*!
  \brief Store a field, one at each time
  \f$H^{ij}_{klm}\f$
  \par this is declared as
\code
form << "H23";
\endcode

the first number (2) after the field name corresponds to the number of up indices

and the second (3) for the lower indices

if there are no up or lower indices then the respective position is filled with the zero number, "0".
*/
ToForm& ToForm::operator<<(const string& func) {
  std::vector<string>::iterator it;
  it = find(Functions.begin(), Functions.end(), func);
  if (it == Functions.end()) Functions.push_back(func);
  return *this;
}

/*!
  \brief Store a type of contractions for the fields and (anti)symmetric options
  \f$H^{ij}_{klm}\f$
  \par is writted as "H23(i,j,k,l,m)" in bra/ket/braket constant part
\code
form + "antisymmetrize H23 1,2;" + "antisymmetrize H23 3,4,5;";
\endcode

The first entry corresponds to the antisymmetrization of the first two indices (upper indices) and the second to the antisymmetrization of the three lower indices

if there is only one or no indice there is no need to declare it.
*/
ToForm& ToForm::operator+(const string& func) {
  std::vector<string>::iterator it;
  it = find(FormContraction.begin(), FormContraction.end(), func);
  if (it == FormContraction.end()) FormContraction.push_back(func);
  return *this;
}

#define stringify(x) stringify_literal(x)
#define stringify_literal(x) #x

/*!
  \brief Create file input for FORM and run the FORM program and return the result to file and/or screen
  \param[in,out] exp Braket expression to be simplified in FORM, the result is written back
  \param[in] print if @a TRUE prints final result to screen
  \param[in] all if @a TRUE write all the expression members separately in ouput FORM file, if @ FALSE only writes the full result together.
  \param[in] new indice label to be used when teh option to sum indices is active
*/
void Formrun(Braket& exp, ToForm& formin, bool print, bool all, string newidlabel) {
  //    static bool setformpath = true;
  if (formin.rpath().empty()) {
    const char* path;
    struct stat pstat;
#ifdef FORMDIR
    string pathtmp = stringify(FORMDIR);
    path = pathtmp.c_str();
#else
    struct stat buffer;
    if (stat("form", &buffer) == 0)
      path = (char*)".";
    else
      path = getenv("PATH_TO_FORM");

#endif
    // check path
    if (!path) {
      printf("warning: Environment variable PATH_TO_FORM is not set.\n");
      exit(1);
    } else if (stat(path, &pstat) || !S_ISDIR(pstat.st_mode)) {
#ifdef FORMDIR
      printf("warning: The path \"%s\" does not exist or is not a directory\n.", path);
#else
      printf("warning: The path \"%s\" specified by PATH_TO_FORM does not exist or is not a directory\n.", path);
#endif
      exit(1);
    } else {
      formin.rpath() = path;
    }
    formin.rpath() += "/form";
    // check form program
    if (stat(formin.rpath().c_str(), &pstat) || !S_ISREG(pstat.st_mode)) {
#ifdef FORMDIR
      printf("warning: The FORM program (\"form\") was not found in \"%s\"\n.", path);
#else
      printf("warning: The FORM program (\"form\") was not found in \"%s\"  specified by PATH_TO_FORM.\n.", path);
#endif
      exit(1);
    }
    if (getVerbosity() > SUMMARIZE) cout << "Found form in: " << formin.rpath() << endl;
    //        setformpath = false;
  }
  if (getVerbosity() > SUMMARIZE) cout << "Creating input form file..." << endl;
  string filenamein = formin.file() + "_in.frm";
  ofstream fileout(filenamein.c_str());
  if (fileout.is_open()) {
    fileout << "#-" << endl;
    fileout << "**********************************************************************" << endl;
    fileout << "*                                                                    *" << endl;
    fileout << "*                          Yukawa coupling                           *" << endl;
    fileout << "*                           FORM PROGRAM                             *" << endl;
    fileout << "*                       " << currentDateTime() << "                          *" << endl;
    fileout << "**********************************************************************" << endl;
    fileout << "*" << endl;
    fileout << "*" << endl;
    fileout << "Dimension " + ToString<int>(getDim() / 2) + ";" << endl;
    fileout << "format 255;" << endl;
    fileout << "CFunction sqrt;" << endl;
    fileout << "Symbols y,z;" << endl;
    fileout << formin.getFunction() << "Indices " << IndexList() << endl;
    fileout << "Off statistics;" << endl;
    fileout << "*" << endl;
    exp.setON();
    fileout << exp;
    exp.setOFF();
    fileout << "*" << endl;
    fileout << "Local R =" << endl;
    fileout << "          #do ii = 1, " + ToString<int>(exp.size()) << endl;
    fileout << "                    + R`ii'" << endl;
    fileout << "          #enddo" << endl;
    fileout << ";" << endl;
    fileout << "*" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "contract;" << endl;
    fileout << "*\n"
            << formin.getFC() << endl;
    if (form.getIndexSum()) {
      fileout << "sum " << IndexList() << endl;
      fileout << "id e_(";
      for (int i = 1; i <= getDim() / 2; i++) {
        fileout << i;
        if (i < getDim() / 2) fileout << ",";
      }
      fileout << ")=1;" << endl;
    }
    if (formin.getRenumberOption()) fileout << "renumber 1;" << endl;
    //?????????????????????????????????????????????????????
    // way to deal with 1/sqrt() in middle of expressions
    fileout << "repeat;" << endl;
    fileout << "  id 1/(sqrt(y?)) = sqrt(1/y);" << endl;
    fileout << "  id sqrt(y?)*sqrt(z?) = sqrt(y*z);" << endl;
    fileout << "endrepeat;" << endl;
    //?????????????????????????????????????????????????????
    if (all)
      fileout << "print +s;" << endl;
    else
      fileout << "print R;" << endl;
    fileout << ".end" << endl;
  } else {
    cout << "Cannot create output file: " << filenamein << endl;
    cout << "Exiting..." << endl;
    exit(1);
  }
  fileout.close();
  if (getVerbosity() > SUMMARIZE) cout << "################################################################" << endl;
  string filenameout = formin.file() + "_out.frm";
  if (getVerbosity() > SUMMARIZE) cout << "CALLING FORM..." << endl;
  Timer t1;
  t1.start();
  stringstream torun;
  torun << formin.rpath() << " " << filenamein << " > " << filenameout;

  if (getVerbosity() == DEBUG_VERBOSE) cout << "Running form: " << torun.str().c_str() << endl;
  int out_system = system(torun.str().c_str());
  if (getVerbosity() == DEBUG_VERBOSE && out_system != 0) cout << "System error during form execution: " << out_system << endl;
  if (getVerbosity() == DEBUG_VERBOSE) cout << "Read results form output form file..." << endl;
  // Read results form output file
  string line;
  ifstream myfile(filenameout.c_str());
  stringstream file;
  if (myfile.is_open()) {
    while (myfile.good()) {
      getline(myfile, line);
      file << line << endl;
    }
    myfile.close();
  } else {
    cout << "Error reading output form file: " << filenameout << endl;
    exit(1);
  }
  if (getVerbosity() == DEBUG_VERBOSE) cout << "Replacing form indices by j?..." << endl;
  string filecontent = file.str();
  // replace form indices by j_?
  int i = 1;
  while (true) {
    string ind = "N" + ToString<int>(i) + "_?";
    string idsub = newidlabel + ToString<int>(i);
    if (filecontent.find(ind) == string::npos) break;
    while (filecontent.find(ind) != string::npos) {
      filecontent.replace(filecontent.find(ind), ind.size(), idsub);
      newId(idsub);  // add this id...
    }
    i++;
  }
  if (getVerbosity() == DEBUG_VERBOSE) cout << "Write back to output form file..." << endl;
  ofstream fileout0(filenameout.c_str());
  // write back to form output file with replaced indices
  fileout0 << filecontent;
  fileout0.close();
  if (print) {
    cout << "################################################################" << endl;
    cout << "RESULTS FROM FORM: " << endl;
  }
  if (filecontent.find("R =") == string::npos) {
    cout << "Error, see FORM file for more details, " << filenameout << endl;
    exit(1);
  }
  filecontent.replace(0, filecontent.find("R ="), "");
  filecontent.replace(filecontent.find(";") + 1, filecontent.length(), "");
  // filecontent = "\tR = " +filecontent;
  if (print) cout << filecontent << endl;
  if (getVerbosity() == DEBUG_VERBOSE) cout << "Write the results in current expression..." << endl;
  // NEED TO IMPLEMENT A BETTER WAY TO READ TO FORM AND CONVERT THE RESULT TO BRAKET.....
  filecontent.erase(std::remove(filecontent.begin(), filecontent.end(), ' '), filecontent.end());
  filecontent.erase(std::remove(filecontent.begin(), filecontent.end(), '\n'), filecontent.end());
  filecontent = filecontent.substr(filecontent.find("R=") + 2, filecontent.find(';') - filecontent.find("R=") - 2);
  vector<string> sta;
  std::size_t found = filecontent.find_first_of("-+");
  std::size_t found0 = 0;
  while (found != std::string::npos) {
    found = filecontent.find_first_of("+-", found0 + 1);
    string tmp = filecontent.substr(found0, found - found0);
    found0 = found;
    if (!tmp.empty()) sta.push_back(tmp);
  }
  Braket newexp;
  newexp.expfromForm(sta);
  exp = newexp;
  if (print) cout << "################################################################" << endl;
  if (getVerbosity() > SUMMARIZE) cout << "Time FORM: " << t1.getElapsedTimeInMicroSec() << " us\t" << t1.getElapsedTimeInSec() << " s" << endl;
}

void CallForm(Braket& exp, bool print, bool all, string newidlabel) {
  Formrun(exp, form, print, all, newidlabel);
}

}  // namespace sospin
