// example for SO(4) written in the manuscript 
// updated on 9 July 2015


#include <son.h>

using namespace sospin;


Braket G(bool even, string startid){
	if(even){
	  Braket gamma_par = bb(startid +"1");
	  gamma_par += bbt(startid +"1");
	  return gamma_par;
	}
	Braket gamma_impar = bb(startid +"1");
	gamma_impar -= bbt(startid +"1");
	string constpart = "-i_";
	gamma_impar = gamma_impar * constpart;
	return gamma_impar;

}


int main(int argc, char *argv[]){

    Timer alltime;
    alltime.start();
    cout << "################################################################" << endl;
	setDim(4);

	Braket L1, R1, L2, R2;
	Braket in1E, in1O, in2E, in2O, res;

	L1 = bra(0,M(a),identity);
	L1+= bra(0,Mb(a)*e_(i,j)/2,b(j)*b(i));
	R1 = ket(0,N10(b,k),bt(k));

	L2 = bra(0,M(c),identity);
	L2+= bra(0,Mb(c)*e_(l,m)/2,b(m)*b(l));
	R2 = ket(0,N10(d,o),bt(o));

	Field(M,  0, 0, ASYM_WITH_FLAVOR);
	Field(Mb, 0, 0, ASYM_WITH_FLAVOR);
	Field(N,  1, 0, ASYM_WITH_FLAVOR);

	newId("a");  newId("b");
	newId("c");  newId("d");

	in1E = L1 * Bop("i") * G(true, "j") * R1;
	in2E = L2 * Bop("k") * G(true, "j") * R2;
	in1O = L1 * Bop("i") * G(false,"j") * R1;
	in2O = L2 * Bop("k") * G(false,"j") * R2;

	in1E.evaluate();
	in2E.evaluate();
	in1O.evaluate();
	in2O.evaluate();

	res = in1E * in2E + in1O * in2O ;

	unsetFormIndexSum();
	CallForm(res,false, true, "i");

	res.setON();
    cout << "Result: \n" << res << endl;
    print_process_mem_usage();
    cout << "################################################################" << endl; 
    cout << "Total time: " << alltime.getElapsedTimeInMicroSec()  << " us\t" << alltime.getElapsedTimeInSec() << " s"  << endl; 
    cout << "################################################################" << endl; 
    CleanGlobalDecl();
    exit(0);
}


