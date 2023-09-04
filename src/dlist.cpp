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

//       dllist.cpp created on 27/02/2015
//
//      This file contains the functions necessary to do things
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      Revision 1.2 26/05/2015 09:02:00 nunogon
//      License updated
//

/*!
  \file 
  \brief Definitions for all general (initialisation etc.) routines of class DList.
*/


#include <sospin/dlist.h>
#include "son.h"
#include "index.h"

namespace sospin {

    /*! \brief Default constructor*/
	DList::DList(void){
			begin = 0;
			end = 0;
			actual = 0;
			sign=1;
	}

    /*!
    \brief Constructor - node of element of type "tp" and first data field "i". Pointer are initialized with NULL.
	\param tp symbol type
	\param i index symbol
	*/
	DList::DList(int tp, int i){
		begin=new noList();
		begin->data=elemType::make_elem(tp, i);
		begin->prv=0;
		begin->nxt=0;
		actual = begin;
		end = begin;
		sign=1;
	}

    /*! \brief Constructor - node of element of type "tp", first data field "i" and second data field "j". Pointer are initialized with NULL.
	\param tp symbol type
	\param i first index symbol
	\param j second index symbol
	*/
	DList::DList(int tp, int i, int j){
		begin=new noList();
		begin->data=elemType::make_elem(tp, i, j);
		begin->prv=0;
		begin->nxt=0;
		actual = begin;
		end = begin;
		sign=1;
	}

    /*! \brief Constructor by copy.*/
    DList::DList(const DList &L) {
		begin = 0;
		end = 0;
		actual = 0;
		sign=1;
    	if(!L.begin) return;
        this->sign = L.sign;
        noList *q, *p, *k;
        q = L.begin;
        if (q != 0) {
            p = new noList();
            p->data = (q->data);
            p->prv = 0;
            p->nxt = 0;
            this->begin = p;
            this->end = p;
            k = begin;
            q = q->nxt;
            while (q != 0) {
                p = new noList();
                p->data = (q->data);
                p->prv = k;
                p->nxt = 0;
                k->nxt = p;
                this->end = p;
                q = q->nxt;
                k = k->nxt;
            }
            this->actual = p;
        }
    }

	/*!\brief Destructor*/
	DList::~DList(void){
		clear();
	}


    //Changing, writing and updating

	/*!\brief Delete all nodes from DList*/
	void DList::clear(){
		if(begin){
			noList *seg;
			actual = begin;
			seg = actual->nxt;
			while(seg !=0){
				delete(actual);
				actual = seg;
				seg = seg->nxt;
			}
			delete(actual);
		}
		actual=0;
		begin=0;
		end=0;
		sign=1;
	}


    /*!
    \brief Adds one node at the end of DList (scans the list). Updates actual pointer to be the last node.
	\param elem symbol to be added
	*/
	void DList::add(elemType elem){
		noList *q,*p;
		if(!begin){
			begin=new noList();
			begin->data = elem;
			begin->prv=0;
			begin->nxt=0;
			actual = begin;
			end = begin;
		}
		else{
			q=begin;
			while(q->nxt!=0) q=q->nxt;
			p=new noList();
			p->data = elem;
			p->prv=q;
			p->nxt=0;
			q->nxt=p;
			actual = p;
			end = p;
		}
	}

    /*!
    \brief Adds one node in the beginning of DList. Updates actual pointer to be the new first node.
	\param elem symbol to be added
	*/
	void DList::add_begin(elemType elem){
		noList *q,*p;
		if(begin == 0){
			begin=new noList();
			begin->data=elem;
			begin->prv=0;
			begin->nxt=0;
			actual = begin;
			end = begin;
		}
		else{
			p=new noList();
			p->data=elem;
			p->prv=0;
			p->nxt=begin;
			begin->prv = p;
			begin = p;
			actual = p;
		}
	}

    /*!
    \brief Adds one node in the end of DList. Updates actual pointer to be the last node.
	\param elem symbol to be added
	*/
	void DList::add_end(elemType elem){
		noList *q,*p;
		if(!begin){
			begin=new noList();
			begin->data=elem;
			begin->prv=0;
			begin->nxt=0;
			actual = begin;
			end = begin;
		}
		else{
			p=new noList();
			p->data=elem;
			p->prv=end;
			p->nxt=0;
			end->nxt=p;
			end = p;
			actual = p;
		}
	}


    /*! \brief Joins a DList to the end of the current DList (this). Updates "actual" pointer to be the end of the final DList.

	k.join(q) = k q
	*/
	void DList::join(DList& L){

		noList *k,*p,*q;
		q=L.begin;
		k=begin;
		if(!begin){
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			begin=p;
			end = k;
			k=begin;
			q = q->nxt;
		}
		else while(k->nxt!=0) k = k->nxt;
		while(q!=0){
			p=new noList();
			p->data=(q->data);
			p->prv=k;
			p->nxt=0;
			k->nxt=p;
			end = k;
			q = q->nxt;
			k = k->nxt;
		}
		actual = end;
	}


    /*! \brief Creates and returns a new DList by copying nodes in DList ordered by type. The nodes that first appear in the new ordered DList are $\delta$'s (type=2) and then all other elements: $b$ (type=0) and $b^\dagger$ (type=1) unordered. Constant elements are removed.*/
	DList DList::rearrange(){
		DList M;
		M.sign = sign;
		noList *q;
		q=begin;
		if(q!=0){
			if(q->nxt==0) M.add_end(q->data);
			else{
				while(q!=0){
					if(q->data.getType()==2) M.add_end(q->data);
					q=q->nxt;
				}
				q=begin;
				while(q!=0){
					if(q->data.getType()==0 || q->data.getType()==1 ) M.add_end(q->data);
					q=q->nxt;
				}
			}
		}
		return M;
	}

    /*! \brief Removes the first element with "data.get\_type()==type" found in DList. Updates actual pointer to be the first node.*/
	void DList::remove(unsigned int type){
		actual = begin;
		noList *next;
		noList *prv;
		if(begin){
			prv=0;
			while(actual!=0){
				if(actual->data.getType()==type){
					if(prv==0)  begin=actual->nxt;
					else prv->nxt=actual->nxt;
					if(actual->nxt == 0) end = prv;
					else{
						next = actual->nxt;
						next-> prv = actual->prv;
					}
					delete(actual);
					actual = begin;
					return;
				}
				prv=actual;
				actual=actual->nxt;
			}
		}
		actual=begin;
	}

    /*! \brief Removes the element for which the actual pointer, "actual", is pointing at in DList.*/
	void DList::remove_actual(){
		noList *next;
		noList *prv;
		if(begin)
			if(actual!=0){
				prv=0;
				if(actual->prv==0) begin=actual->nxt;
				else{
					prv = actual -> prv;
					prv->nxt=actual->nxt;
				}
				if(actual->nxt == 0) end = prv;
				else{
					next = actual->nxt;
					next-> prv = actual->prv;
				}
				delete(actual);
				//length--;
				//if(beg==end) empty = true;
				actual = begin;
				return;
			}
	}

    /*! \brief Swaps the actual node with the next node of DList.*/
	void DList::swap_next(){
		if(!actual || (actual->nxt) == 0) cout << "swap empty list or end of list" << endl;
		else{
			noList *before, *after, *after2;
			after2=0;
			before = actual-> prv;
			after = actual-> nxt;
			if(after->nxt != 0) after2 = after->nxt;
			else  end = actual;
			if(before!=0) before->nxt = after;
			else begin=after;
			actual -> nxt = after2;
			if(after2!=0) after2 -> prv = actual;
			after-> prv = before;
			actual-> prv = after;
			after -> nxt = actual;
		}
	}


    //Reading and accessing data

    /*! \brief Creates and returns an integer vector sequence container with the ids (data fields) of $b$'s and $b^\dagger$'s elements.*/
    vector<int> DList::getIds(){
		vector<int> ids;
		if(begin!=0){
			noList *q;
			q=begin;
			while(q!=0) {
				switch(q->data.getType()){
				case 0:
					ids.push_back(0);
					break;
				case 1:
					ids.push_back(1);
					break;
				}
				q=q->nxt;
			}
		}
		return ids;
	}

    /*! \brief Updates integer vector sequence containers "id0" and "id1" with ids (data fields) of $b$'s and $b^\dagger$'s elements, respectively. "sign" is updated with the sign of DList. "BandBdagger" is a boolean which is true if DList contains at least one $b$ or $b^\dagger$, and false otherwise.*/
	void DList::getBandBdaggerIds(bool &BandBdagger, vector<string> &id0, vector<string> &id1, int &sign){
		BandBdagger = false;
		if(begin!=0){
			noList *q;
			q=begin;
			sign = getSign();
			while(q!=0) {
				switch(q->data.getType()){
				case 0:
					id0.push_back(getIdx(q->data.getIdx1()));
					BandBdagger = true;
					break;
				case 1:
					id1.push_back(getIdx(q->data.getIdx1()));
					BandBdagger = true;
					break;
				}
				q=q->nxt;
			}
		}
	}

    /*! \brief Updates integer vector sequence containers "id0" and "id1" with first and second ids (data fields) of $\delta$ elements, respectively. "sign" is updated with the sign of DList. "AllDeltas" is a boolean which is true if all elements in DList are of $\delta$ type, and false otherwise.*/
	void DList::getDeltaIds(bool &AllDeltas, vector<string> &id0, vector<string> &id1, int &sign){
		bool expwithAllDelta = false;
		if(begin!=0){
			noList *q;
			q=begin;
			sign = getSign();
			bool alldeltas = true;
			while(q!=0) {
				switch(q->data.getType()){
				case 0:
					alldeltas = false;
					break;
				case 1:
					alldeltas = false;
					break;
				case 2:
					id0.push_back(getIdx(q->data.getIdx1()));
					id1.push_back(getIdx(q->data.getIdx2()));
					break;
				case 3:
					alldeltas = false;
					break;
				}
				if(alldeltas == false) break;
				q=q->nxt;
			}
			if(alldeltas) expwithAllDelta = true;
		}
		AllDeltas = expwithAllDelta;
	}

    /*! \brief Updates integer vector sequence containers "id0" and "id1" with ids (data fields) of $b$'s and $b^\dagger$'s elements, respectively, and "id2" and "id3" integer vector sequence containers with first and second data fields of $\delta$'s elements, respectively. "sign" is updated with the sign of DList.*/
	void DList::getBandBdaggerAndDeltasIds(vector<string> &id0, vector<string> &id1, \
		vector<string> &id2, vector<string> &id3,int &sign){
			if(begin!=0){
				noList *q;
				q=begin;
				sign = getSign();
				while(q!=0) {
					switch(q->data.getType()){
					case 0:
						id0.push_back(getIdx(q->data.getIdx1()));
						break;
					case 1:
						id1.push_back(getIdx(q->data.getIdx1()));
						break;
					case 2:
						id2.push_back(getIdx(q->data.getIdx1()));
						id3.push_back(getIdx(q->data.getIdx2()));
						break;
					}
					q=q->nxt;
				}
			}
	}

    /*! \brief Returns the number of elements of type $\delta$ (type=2).*/
	int DList::numDeltas(){
		if(begin==0) return 0;
		else{
			noList *q;
			q=begin;
			int alldeltas = 0;
			while(q!=0) {
				if(q->data.getType() == 2){
					alldeltas++;
				}
				q=q->nxt;
			}
			return alldeltas;
		}
	}

    /*! \brief Returns the number of elements of type b (type=0).*/
	int DList::numBs(){
		if(begin==0) return 0;
		else{
			noList *q;
			q=begin;
			int numbs = 0;
			while(q!=0) {
				if(q->data.getType() == 0){
					numbs++;
				}
				q=q->nxt;
			}
			return numbs;
		}
	}

    /*! \brief Search the last element with "data.get\_type()==type1" found in DList. Returns true a node was found.
	\param type symbol to search
	\return @a TRUE if the symbol is not the last, @a FALSE otherwise
	*/
	bool DList::search_last(unsigned int type){
		if(!begin) return false;
		actual=end;
		while(actual!=0) {
			if(actual->data.getType()==type) break;
			actual=actual->prv;
		}
		if(actual == end) return false;
		return true;
	}

	/*!
	\brief Search the first element with "data.get_type()==type1" found in DList
	\param type1 symbol to search
	\return @a TRUE if the symbol is not the first, @a FALSE otherwise
	*/
	bool DList::search_first(unsigned int type1){
		if(!begin) return false;
		actual=begin;
		while(actual!=0) {
			if(actual->data.getType()==type1) break;
			actual=actual->nxt;
		}
		if(actual == begin) return false;
		return true;
	}

    /*! \brief Checks for the order of appearance in DList of types "type0" and "type1". Returns true if order of appearance is the same as the parameter's order and false otherwise.
	\param type0 first symbol
	\param type1 second symbol
	\return @a TRUE if @a type1 is first than @a type0, @a FALSE otherwise
	*/
	//NG: devia alterar-se o nome da funcao.
	bool DList::search_first(unsigned int type0, unsigned int type1){
		if(!begin) return false;
		actual=begin;
		bool opb = false;
		bool elem = true;
		while(actual!=0) {
			if(actual->data.getType()==type0){
				elem = false;
				break;
			}
			else if(actual->data.getType()==type1) opb = true;
			actual=actual->nxt;
		}
		if(opb) elem = true;
		return elem;
	}

    /*! \brief Search the first element with "data.get\_type()==type1" found in DList. Returns true if the symbol is not the first, and false otherwise.
	\param type1 symbol to search
	\return @a TRUE if the element is found
	*/
	bool DList::search_elem(unsigned int type1){
		if(!begin) return false;
		actual=begin;
		while(actual!=0) {
			if(actual->data.getType()==type1) break;
			actual=actual->nxt;
		}
		if(actual == 0) return false;
		return true;
	}


    //Querying and booleans

    /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s matches and if each one is less or equal than N of SO(2N).
	\return @a TRUE if number of b's and b^\\dagger's are equal and they are all within bounds, @a FALSE otherwise.
	*/
	bool DList::check(){
		if(!begin) return false;
		else{
			actual=begin;
			int zero = 0;
			int um = 0;
			while(actual!=0) {
				if(actual->data.getType()==0) zero++;
				if(actual->data.getType()==1) um++;
				actual=actual->nxt;
			}
			if(um == zero && um <=getDim() / 2 && zero <= getDim() / 2) return true;
			return false;
		}
	}

    /*! \brief Checks the indexes of $\delta$ elements. They must be less or equal to the n of SO(2n). Checks also if the the indexes of a delta are equal. Returns true if each $\delta$ is not zero, false otherwise.
	\return @c TRUE if each delta is not zero, @c FALSE otherwise
	*/
	//NG: rever esta função. Parece-me que pode estar errada.
	bool DList::checkDeltaIndex(){
		if(!begin) return false;
		actual=begin;
		bool elem = true;
		int nson = getDim() / 2;
		while(actual!=0) {
			if(actual->data.getType()==2){
				string id0 = getIdx(actual->data.getIdx1());
				string id1 = getIdx(actual->data.getIdx2());
				if( id0 == id1){
					if(atoi(id0.c_str()) <= nson )
						if(atoi(id0.c_str()) > 0 )
							if(atoi(id1.c_str()) <= nson )
								if(atoi(id1.c_str()) > 0 )
									if(atoi(id0.c_str()) != atoi(id1.c_str())){
										break;
									}
				}
				else{
					if(atoi(id0.c_str()) <= nson )
						if(atoi(id0.c_str()) > 0 )
							if(atoi(id1.c_str()) <= nson )
								if(atoi(id1.c_str()) > 0 )
									if(atoi(id0.c_str()) != atoi(id1.c_str())){
										elem = false;
										break;
									}
				}
				if(atoi(id0.c_str()) > nson || atoi(id1.c_str()) > nson ){
					elem = false;
					break;
				}
			}
			actual=actual->nxt;
		}

		return elem;
	}


    /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s is less or equal than N of SO(2N). Returns true if so, false otherwise.*/
	bool DList::check_num(){
		if(!begin) return false;
		else{
			actual=begin;
			int zero = 0;
			int um = 0;
			while(actual!=0) {
				if(actual->data.getType()==0) zero++;
				if(actual->data.getType()==1) um++;
				actual=actual->nxt;
			}
			if(um <=getDim() / 2 && zero <= getDim() / 2) return true;
			return false;
		}
	}

    /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s match. Returns true if they match, false otherwise.*/
	bool DList::check_same_num(){
		if(!begin) return false;
		else{
			actual=begin;
			int zero = 0;
			int um = 0;
			while(actual!=0) {
				if(actual->data.getType()==0) zero++;
				if(actual->data.getType()==1) um++;
				actual=actual->nxt;
			}
			if(um == zero ) return true;
			return false;
		}
	}


    /*! \brief Returns true if there is no elements of type $\delta$ in DList.*/
	bool DList::hasNoDeltas(){
		if(begin==0) return true;
		else{
			noList *q;
			q=begin;
			bool nodeltas = true;
			while(q!=0) {
				if(q->data.getType() == 2){
					nodeltas = false;
					break;
				}
				if(nodeltas == false) break;
				q=q->nxt;
			}
			return nodeltas;
		}
	}

    /*! \brief Returns true if all nodes in DList are of $\delta$ type.*/
    bool DList::hasOnlyDeltas(){
		if(begin==0) return false;
		else{
			noList *q;
			q=begin;
			bool alldeltas = true;
			while(q!=0) {
				if(q->data.getType() != 2){
					alldeltas = false;
					break;
				}
				q=q->nxt;
			}
			return alldeltas;
		}
	}

    /*! \brief Returns true if there is elements with the same id (data fields) in the DList (repeated ids).*/
	bool DList::hasRepeatedIndex(){
		vector<string> id0;
		bool repid = false;
		if(begin!=0){
			noList *q;
			q=begin;
			while(q!=0) {
				switch(q->data.getType()){
				case 0:
					id0.push_back(getIdx(q->data.getIdx1()));
					break;
				case 1:
					id0.push_back(getIdx(q->data.getIdx1()));
					break;
				case 2:
					id0.push_back(getIdx(q->data.getIdx1()));
					id0.push_back(getIdx(q->data.getIdx2()));
					break;
				}
				q=q->nxt;
			}
			int size = id0.size();
			sort (id0.begin(), id0.end());
			vector<string>::iterator it;
			it = unique (id0.begin(), id0.end());
			id0.resize( it - id0.begin() );
			if(size!=id0.size())
				repid = true;
		}
		return repid;
	}



    //Operators

    /*! \brief Copies a DList.*/
	DList& DList::operator=(const DList &L){
     	if(!L.begin) return *this;
		sign = L.sign;
		noList *q,*p, *k;
		q=L.begin;
		if(q!=0){
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			begin=p;
			end = p;
			k=begin;
			q = q->nxt;
			while(q!=0){
				p=new noList();
				p->data=(q->data);
				p->prv=k;
				p->nxt=0;
				k->nxt=p;
				end = p;
				q = q->nxt;
				k = k->nxt;
			}
			actual = p;
		}
		return *this;
	}


    /*! \brief Negates operator, change sign of DList.*/
	const DList DList::operator-()const{
		DList L;
		L.sign = -1 * sign;
		noList *q,*p, *k;
		q=begin;
		k=L.begin;
		if(q!=0){
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			L.begin=p;
			L.end = p;
			k=L.begin;
			q = q->nxt;
			while(q!=0){
				p=new noList();
				p->data=(q->data);
				p->prv=k;
				p->nxt=0;
				k->nxt=p;
				L.end = p;
				q = q->nxt;
				k = k->nxt;
			}
			L.actual = L.end;
		}
		return L;
	}



    //Friends

    /*! \brief Creates and returns a pointer to a new copy of a DList.*/
	DList* copy( DList *L){
		DList *M = 0;
		noList *q,*p, *k;
		q=L->begin;
		if(q!=0){
			M =new DList();
			M->sign = L->sign;
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			M->begin=p;
			M->end = p;
			k=M->begin;
			q = q->nxt;
			while(q!=0){
				p=new noList();
				p->data=(q->data);
				p->prv=k;
				p->nxt=0;
				k->nxt=p;
				M->end = p;
				q = q->nxt;
				k = k->nxt;
			}
			M->actual = p;
		}
		return M;
	}

    /*! \brief Applies the following identity:
      \f{eqnarray*}{
      b_i * b^\dagger_j = \delta_{i,j} - b^\dagger_j * b_i
      \f}
      input DList L keeps delta term and function returns the swapped term.
      @param[in,out] L, DList term to be processed
      @para[in] braketmode, if true if last element in DList is a b, then the L is cleared
      @return returns expression with b_i * b^\dagger_j swapped or empty expression if b is the last term in L
    */
	DList contract_deltas(DList &L, bool braketmode){
		DList M;

		if(L.isEmpty()) return M;
		noList *k,*p,*q;
		q=L.begin;
		elemType bb;
		elemType bdag;

		if(L.begin==0) return M;

		L.search_last(0);
		if(L.actual == L.end){
			if(braketmode) L.clear();
			return M;
		}
		if(L.actual == 0) return M;
		M << L;
		M.set_sign(-1*L.getSign());
		M.search_last(0);
		noList *elem = M.actual;
		bb=elem->data;
		bdag=elem->nxt->data;
		if(bb.getType() != 0 || bdag.getType() !=1){
			DList A;
			return A;
		}
		elemType delta;
		delta.setType(2);
		delta.setIdx1(bb.getIdx1());
		delta.setIdx2(bdag.getIdx1());
		L.add_begin(delta);
		L.search_last(0);

		noList *elem1 = L.actual;
		noList *before, *after, *after2;
		after2=0;
		before=elem1->prv;
		L.actual = L.actual->prv;
		after=elem1->nxt;
		L.actual = after;
		if(after!=0) after2 = after->nxt;
		L.actual = after2;
		if(before!=0) before->nxt = after2;
		else L.begin = 0;
		L.actual = L.begin;
		if(after2!=0) after2->prv = before;
		if(after2==0) L.end = before;
		delete elem1;
		if(after!=0) delete after;

		M.search_last(0);
		M.swap_next();
		return M;
	}

    /*! \brief Order only the b's (to the left hand side) and b\dagger's (to the right hand side) terms.
	  Applies the following identity:
      \f{eqnarray*}{
      b^\dagger_j * b_i = \delta_{i,j} - b_i * b^\dagger_j
      \f}
      input DList L keeps delta term and function returns the swapped term.
      @param[in,out] L, DList term to be processed
      @para[in] braketmode, if true if last element in DList is a b, then the L is cleared
      @return returns expression with b^\dagger_j * b_i swapped or empty expression if b is the last term in L
    */
	DList ordering(DList &L, bool braketmode){
		DList M;

		if(L.isEmpty()) return M;
		noList *k,*p,*q;
		q=L.begin;
		elemType bb;
		elemType bdag;

		if(L.begin==0) return M;

		L.search_first(1);
		if(L.actual == L.begin){
			if(braketmode) L.clear();
			return M;
		}
		if(L.actual == 0) return M;
		M << L;
		M.set_sign(-1*L.getSign());
		M.search_first(1);
		L.search_first(1);
		noList *elemM = M.actual;
		noList *elemL = L.actual;
		bdag=elemM->data;
		bb =elemM->nxt->data;
		while(true){
			if(bb.getType() == 0 && bdag.getType() ==1) break;
			elemM = elemM->nxt;
			elemL = elemL->nxt;
			bdag=elemM->data;
			bb =elemM->nxt->data;
		}
		M.actual = elemM;
		L.actual = elemL;
		elemType delta;
		delta.setType(2);
		delta.setIdx1(bb.getIdx1());
		delta.setIdx2(bdag.getIdx1());


		noList *elem1 = L.actual;
		noList *before, *after, *after2;
		after2=0;
		before=elem1->prv;
		L.actual = L.actual->prv;
		after=elem1->nxt;
		L.actual = after;
		if(after!=0) after2 = after->nxt;
		L.actual = after2;
		if(before!=0) before->nxt = after2;
		else L.begin = 0;
		L.actual = L.begin;
		if(after2!=0) after2->prv = before;
		if(after2==0) L.end = before;
		delete elem1;
		if(after!=0) delete after;
		L.add_begin(delta);

		M.swap_next();
		return M;
	}

    //NG: o "*" deveria ser colocado tb para type=3, não?
    /*! \brief Creates and returns a string with the deltas and constants of a DList.*/
	string printDeltas(DList &L){
		string deltas = "";
		if(!L.begin) return deltas;
		noList *q;
		q=L.begin;

		while(q!=0) {
			if(q->data.getType() == 2)
				deltas += "d_(" + getIdx(q->data.getIdx1()) + "," + getIdx(q->data.getIdx2()) + ")";
			if(q->data.getType() == 3)
				deltas += "1";
			q=q->nxt;
			if(q!=0) if(q->data.getType() == 2 ) deltas += "*";
		}
		return deltas;
	}


	// Friends - Operators

    /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
	DList& operator*(DList& L, elemType j){
		L.add_end(j);
		return L;
	}

    /*! \brief Creates and returns new DList that joins two DLists by order of parameters.*/
	DList operator*(const DList &O, const DList &P){
		DList L;
		L.sign = O.sign * P.sign;
		noList *q,*p, *k;
		q=O.begin;
		k=L.begin;
		if(q!=0){
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			L.begin=p;
			k=L.begin;
			L.end = p;
			q = q->nxt;
			while(q!=0){
				p=new noList();
				p->data=(q->data);
				p->prv=k;
				p->nxt=0;
				k->nxt=p;
				L.end = p;
				q = q->nxt;
				k = k->nxt;
			}
		}
		q=P.begin;
  		while(q!=0 ){
			if( (O.begin != 0 || q->nxt != 0) && q->data.getType() == 3){
				q = q->nxt;
				continue;
			}
			p=new noList();
			p->data=(q->data);
			p->prv=k;
			p->nxt=0;
			k->nxt=p;
			L.end = p;
			q = q->nxt;
			k = k->nxt;
		}
		L.actual = L.end;
		return L;
	}

    /*! \brief Negates the sign of a DList and add the elemtype "j" at end of it.*/
	DList& operator-(DList& L, elemType j){
		L.set_sign(-1 * L.getSign());
		L.add_end(j);
		return L;
	}

    /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
	DList& operator,(DList& L, elemType j){
		L.add_end(j);
		return L;
	}

    /*! \brief Sends to output stream ostream a string with the corresponding expression of the DList.
	\param out ostream
	\param L DList
	\return ostream

	\code
	cout << L << endl;
	\endcode
	*/
	ostream& operator<<(ostream& out, DList &L){
		if(!L.begin) return out << " ";
		noList *q;
		q=L.begin;
		if(q!=0){
			out << "\t";
			if(L.getSign() == -1) out << " - ";
			if(L.getSign() == 1) out << " + ";
		}
		while(q!=0) {
			if(q->data.getType() == 2)
				out << "d(" << getIdx(q->data.getIdx1()) << "," << getIdx(q->data.getIdx2()) << ")";
			if(q->data.getType() == 0)
				out << "b(" << getIdx(q->data.getIdx1()) << ")";
			if(q->data.getType() == 1)
				out << "bt(" << getIdx(q->data.getIdx1()) << ")";
			if(q->data.getType() == 3)
				out << "1";
			if( q == L.actual) out << "@";
			if(q->nxt!=0) out << " * ";
			q=q->nxt;
		}
		return out << " ";
	}

    /*! \brief Sends to output stream ostream a string with the corresponding expression of the DList.*/
	ostream& operator<<(ostream& out, DList *L){
		if(!L) return out << " ";
		if(!L->begin) return out << " ";
		noList *q;
		q=L->begin;
		if(q!=0){
			out << "\t";
			if(L->getSign() == -1) out << " - ";
			if(L->getSign() == 1) out << " + ";
		}
		while(q!=0) {
			if(q->data.getType() == 2)
				out << "d(" << getIdx(q->data.getIdx1()) << "," << getIdx(q->data.getIdx2()) << ")";
			if(q->data.getType() == 0)
				out << "b(" << getIdx(q->data.getIdx1()) << ")";
			if(q->data.getType() == 1)
				out << "bt(" << getIdx(q->data.getIdx1()) << ")";
			if(q->data.getType() == 3)
				out << "1";
			if( q == L->actual) out << "@";
			if(q->nxt!=0) out << " * ";
			q=q->nxt;
		}
		return out << " ";
	}

    //same as operator* and operator,
    /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
	DList& operator<<(DList& L, elemType j){
		L.add_end(j);
		return L;
	}

    /*! \brief Copies DList. Creates and returns a new DList with nodes of both DLists. Sign is the product of both products.
	\param M DList to copy
	\param[out] L DList with content of M added

	\code
	L << M;
	//or with more DList's
	L << M << N << O << P;
	\endcode
	*/
	DList& operator<<(DList &L, DList &M){
		if(!M.begin) return L;
		L.set_sign(L.getSign()*M.getSign());
		noList *q,*p, *k;
		q=M.begin;
		k=L.begin;
		if(!L.begin){
			p=new noList();
			p->data=(q->data);
			p->prv=0;
			p->nxt=0;
			L.begin=p;
			k=L.begin;
			q = q->nxt;
			L.end = p;
		}
		else while(k->nxt!=0) k = k->nxt;
		while(q!=0){
			p=new noList();
			p->data=(q->data);
			p->prv=k;
			p->nxt=0;
			k->nxt=p;
			L.end = p;
			q = q->nxt;
			k = k->nxt;
		}
		L.actual = L.end;
		return L;
	}

    /*! \brief Returns true if two DLists are equal.*/
	bool operator==(DList &L, DList &M){
		if(!M.begin && !L.begin) return true;
		if(L.getSign() != M.getSign()) return false;

		noList *q,*p, *k;
		elemType data0, data1;
		q=M.begin;
		k=L.begin;
		while(true){
			data0 = q->data;
			data1 = k->data;
			if(data0.getType() != data1.getType()){
				return false;
			}
			if(getIdx(data0.getIdx1()) != getIdx(data1.getIdx1())){
				return false;
			}
			if(getIdx(data0.getIdx2()) != getIdx(data1.getIdx2())){
				return false;
			}
			if(k->nxt !=0 && q->nxt !=0){
				k=k->nxt;
				q=q->nxt;
			}
			else{
				if((k->nxt !=0) != (q->nxt !=0)){
					return false;
				}
				break;
			}
		}
		return true;
	}

}
