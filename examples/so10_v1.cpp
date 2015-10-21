// example for SO(10) written in the manuscript 
// updated on 9 July 2015

#include <son.h>

using namespace sospin;

int main(int argc, char *argv[]){
    Timer alltime;
    alltime.start();
    cout << "################################################################" << endl;

	setDim(10);

	Braket psipbra, psipket, gamma, exp;

	psipbra = bra(0, M(a), identity);
	psipbra += bra(2, 1/2*M20(a,o,p),-b(o)*b(p));
	psipbra += bra(4,1/24*e_(o,p,q,r,s)*Mb01(a,o),b(p)*b(q)*b(r)*b(s));    
	newId("a"); 

	psipket = ket(0,M(b), identity);
	psipket += ket(2,1/2 * M20(b,j,k), bt(j) * bt(k));
	psipket += ket(4, 1/24*e_(j,k,l,m,n)*Mb01(b,j), bt(k)*bt(l)*bt(m)*bt(n));  
	newId("b"); 

	Field(M, 0, 0, ASYM_WITH_FLAVOR); 
	Field(M, 2, 0, ASYM_WITH_FLAVOR);
	Field(Mb, 0, 1, ASYM_WITH_FLAVOR);

	gamma = free(-3,1/6*(e_(r1,r2,r3,r4,r5)*H20(r4,r5)/sqrt(3)),b(r1)*b(r2)*b(r3));
	gamma += free(3,1/6*(e_(r1,r2,r3,r4,r5)*H02(r4,r5)/sqrt(3)),bt(r1)*bt(r2)*bt(r3));
	gamma += free(-1,(2*H12(r1,r2,r3)+d_(r1,r2)*H01(r3)-d_(r1,r3)*H01(r2))/(2*sqrt(3)), bt(r1)*b(r2)*b(r3));
	gamma += free(1,(2*H21(r1,r2,r3)+d_(r1,r3)*H10(r2)-d_(r2,r3)*H10(r1))/(2*sqrt(3)), bt(r1)*bt(r2)*b(r3));
	gamma += free(-1,2*H01(r1)/sqrt(3),-b(r1));
	gamma += free(1,2*H10(r1)/sqrt(3), bt(r1));
	newId("r4");     newId("r5");   

	Field(H, 1, 0, ASYM);     Field(H, 0, 1, ASYM);
	Field(H, 0, 2, ASYM);     Field(H, 2, 0, ASYM);
	Field(H, 2, 1, ASYM);     Field(H, 1, 2, ASYM);

	exp = psipbra * Bop() * gamma * psipket;
	exp.evaluate(false); 

    CallForm(exp,true, true, "i"); 
    setFormRenumber();
    CallForm(exp,true, true, "i"); 
    cout << "Result: \n" << exp << endl;
    print_process_mem_usage();
    cout << "################################################################" << endl; 
    cout << "Total time: " << alltime.getElapsedTimeInMicroSec()  << " us\t" << alltime.getElapsedTimeInSec() << " s"  << endl; 
    cout << "################################################################" << endl; 
    CleanGlobalDecl();
    exit(0);
}
