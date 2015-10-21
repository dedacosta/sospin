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

//       sospin.cpp created on 27/02/2015 
//
//      This file contains the functions necessary to do things 
//   in the SOSpin Library.
//
//      Revision 1.1 01/07/2015  nuno
//      License updated	
//




#include <son.h>
#include <tools/so10.h>

using namespace std;
using namespace sospin;


int main(int argc, char *argv[]){

    Timer alltime;
    alltime.start();
    cout << "################################################################" << endl;
    setDim(10);
    setVerbosity(SUMMARIZE);
    cout << "Verbosity type: " << getVerbosity() << endl;
    //unsetSimplifyIndexSum();
    Braket exp, exp0, exp1, exp2;
    exp0 = psi_144m(bra) * Bop("j");
    exp1 = GammaH(0) * psi_144p(ket);
    cout << "################################################################" << endl;
    exp = exp0 * exp1; 
    if(1) exp.evaluate(false); // levi-civita
    else exp.evaluate(true); //only deltas
    //unsetFormIndexSum();
    CallForm(exp,false, true, "i"); 
    setFormRenumber();
    CallForm(exp,false, true, "i");  
    //exp.setON();
    cout << "Result: \n" << exp << endl;
    print_process_mem_usage();
    cout << "################################################################" << endl; 
    cout << "Total time: " << alltime.getElapsedTimeInMicroSec()  << " us\t" << alltime.getElapsedTimeInSec() << " s"  << endl; 
    cout << "################################################################" << endl; 
    CleanGlobalDecl();
    exit(0);
}
