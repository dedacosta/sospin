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

//       dllist.h created on 27/02/2015
//
//      This file contains the functions necessary to do things
//   in the SOSpin Library.
//
//      Revision 1.1 28/02/2015 23:19:29 david
//      Revision 1.2 29/04/2015 17:27:00 nunogon
//      Revision 1.3 26/05/2015 00:04:00 nunogon
//      License updated
//

/*!
  \file 
  \brief Defintions for all general (initialisation etc.) routines of class DList.
*/

#ifndef CLASS_DList_H
#define CLASS_DList_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>



using namespace std;


namespace sospin {

    /*!
      \enum Elem enumerator for Node symbol
      \brief Enumerator for Node symbol
     */
    enum Elem {
        b = 0, ///< b element
        bt = 1, ///< b^\\dagger element
        delta = 2, ///< \\delta element
        ct = 3 ///< constant element
    };

    /**
     * \struct elemtype
     *
     * \brief struct to store information about one DList element
     *
     * Symbol types:
     *
     * Definition for b:
     * - data.type = 0	:	b
     *     - .id.x 	->	: 	b index
     *
     * Definition for b^\\dagger:
     *
     * - data.type = 1	:	b^\\dagger
     *     - .id.x 	->	:	b^\\dagger index
     *
     * Definition for delta:
     *
     * - data.type = 2	:	delta
     *     - .id.x 	->	:	first delta index
     *     - .id.y 	->	:	second delta index
     *
     * Definition for constant:
     * - data.type = 3	:	1, identity
     */
    struct elemType {
        //Type - 3 bits
        //Sign - 1 bit
        //id.x - 10 bits
        //id.y - 10 bits
        //Free bits - 8 bits
        //Total - 32 bits
        unsigned int dataField;

        /*! \brief Returns the type of the element. Ex.: $b$ - type=0; $b^{\dagger}$ - type=1; $\delta$ - type=2; constant - type=3.*/
        unsigned int getType() {
            unsigned int type_out;
            type_out = dataField >> 29;
            return type_out;
        }

        /*! \brief Returns the sign of the element (not used in current version).*/
        bool getSign() {
            unsigned int bool_out;
            bool_out = dataField & 0x10000000;
            bool_out = bool_out >> 28;
            return bool_out;
        }

        /*! \brief Returns the first data field of the element (id.x).*/
        unsigned int getIdx1() {
            unsigned int idx1_out;
            idx1_out = dataField & 0x0FFC0000;
            idx1_out = idx1_out >> 18;
            return idx1_out;
        }

        /*! \brief Returns the second data field of the element (id.y).*/
        unsigned int getIdx2() {
            unsigned int idx2_out;
            idx2_out = dataField & 0x0003FF00;
            idx2_out = idx2_out >> 8;
            return idx2_out;
        }

        /*! \brief Creates and return an element of type "type" and one data field "data". Second data field is set to zero.*/
        static elemType make_elem(int type, int data) {
            if (type == 2) {
                cout << "Cannot make a delta elemType with only one index" << endl;
                exit(0);
            } // returns error if data.type = 2 (delta)
            elemType elem;
            elem.setType(type);
            elem.setIdx1(data);
            elem.setIdx2(0);
            return elem;
        }

        /*! \brief Creates and return an element of type "type" and data fields "data1" and "data2".*/
        static elemType make_elem(int type, int data1, int data2) {
            elemType elem;
            elem.setType(type);
            elem.setIdx1(data1);
            elem.setIdx2(data2);
            return elem;
        }

        /*! \brief Creates and return $\delta$ element using first data field of elements "a" and "b".*/
        static elemType make_delta(elemType data1, elemType data2) {
            elemType elem;
            elem.setType(2);
            elem.setIdx1(data1.getIdx1());
            elem.setIdx2(data2.getIdx1());
            return elem;
        }

        /*! \brief Sets the type of the element.*/
        void setType(unsigned int typ) {

            //Clean 3-bits of type
            dataField = dataField & 0x1FFFFFFF;

            //Set type
            //b
            if (typ == 0) dataField = dataField | 0x00000000;
            //b^\dagger
            if (typ == 1) dataField = dataField | 0x20000000;
            //delta
            if (typ == 2) dataField = dataField | 0x40000000;
            //constant
            if (typ == 3) dataField = dataField | 0x60000000;
            // For all other types (not used)
            if (typ > 3) dataField = dataField | 0x80000000;

        }

        /*! \brief Sets sign field of the element (not used in current version).*/
        void setSign(bool sign) {
            //Clean bit of sign
            dataField = dataField & 0xEFFFFFFF;

            //Set sign (only if sign is true)
            if (sign == 1) dataField = dataField | 0x10000000;

        }

        /*! \brief Sets first data field of the element (idx1).*/
        void setIdx1(unsigned int idx) {
            unsigned int in;

            //Clean bits of data1 field
            dataField = dataField & 0xF003FFFF;

            //Format in to accommodate 10 bits from the input
            in = idx & 0x000003FF;

            //Shift to match filled bits
            in = in << 18;

            //Set data1 field
            dataField = dataField | in;
        }

        /*! \brief Sets second data field of the element (idx2).*/
        void setIdx2(unsigned int idx) {
            unsigned int in;

            //Clean bits of data2 field
            dataField = dataField & 0xFFFC00FF;

            //Format in to accommodate 10 bits from the input
            in = idx & 0x000003FF;

            //Shift to match filled bits
            in = in << 8;

            //Set data2 field
            dataField = dataField | in;
        }

        /*! \brief Makes a copy of an element.*/
        elemType& operator=(const elemType &elem) {
            elemType aux=elem;
            setType(aux.getType());
            setIdx1(aux.getIdx1());
            setIdx2(aux.getIdx2());
            return *this;
        }

    };

    /*!
      \struct noList
      \brief struct for the node of DList
     */
    struct noList {
        /*! \brief Store symbol type.*/
        elemType data;
        /*! \brief Pointer to the previous (@a prv) node.*/
        noList *prv;
        /*! \brief Pointer to the next (@a nxt) node.*/
        noList *nxt;
    };

    /*!
      \class DList Class
      \brief DList with nodes
     */
    class DList {
        /*! \brief Pointer to the first node.*/
        noList *begin;
        /*! \brief Pointer to the last node.*/
        noList *end;
        /*! \brief Pointer to the actual node.*/
        noList *actual;
        /*! \brief Store the sign of the monomial.*/
        int sign;


    public:
        //Constructors and destructor

        /*! \brief Default constructor*/
        DList(void);

        /*! \brief Constructor - node of element of type "tp" and first data field "i". Pointer are initialized with NULL.*/
        DList(int tp, int i);

        /*! \brief Constructor - node of element of type "tp", first data field "i" and second data field "j". Pointer are initialized with NULL.*/
        DList(int tp, int i, int j);

        /*! \brief Constructor by copy.*/
        DList(const DList &L);

        /*! \brief Destructor.*/
        ~DList(void);


        //Changing, writing and updating

        /*! \brief Deletes all nodes from DList.*/
        void clear();

        /*! \brief Changes the sign of DList.*/
        void negate() {
            sign *= -1;
        }


        /*! \brief Adds one node at the end of DList (scans the list). Updates actual pointer to be the last node.*/
        void add(elemType);

        /*! \brief Adds one node in the beginning of DList. Updates actual pointer to be the new first node.*/
        void add_begin(elemType);

        /*! \brief Adds one node in the end of DList. Updates actual pointer to be the last node.*/
        void add_end(elemType);


        /*! \brief Sets data (elemtype) of the node being pointed by actual pointer.*/
        void set(elemType i) {
            actual->data = i;
        }

        /*! \brief Changes actual pointer to point at the first element of DList (beg pointer).*/
        void set_begin() {
            actual = begin;
        }

        /*! \brief Changes actual pointer to point at the last element of DList (end pointer).*/
        void set_end() {
            actual = end;
        }

        /*! \brief Sets the sign of DList.*/
        void set_sign(int ii) {
            sign = ii;
        }


        /*! \brief Joins a DList to the end of the current DList (this). Updates "actual" pointer to be the end of the final DList.*/
        void join(DList& L);

        /*! \brief Shifts actual pointer to next node. If actual node is the end node, shift to beg node.*/
        void loop_right() {
            if (actual == 0 || actual->nxt == 0) actual = begin;
            else actual = actual->nxt;
        }

        /*! \brief Shifts actual pointer to previous node. If actual node is the beg node, shift to end node.*/
        void loop_left() {
            actual = actual -> prv;
            if (actual == 0) actual = end;
        }

        /*! \brief Creates and returns a new DList by copying nodes in DList ordered by type. The nodes that first appear in the new ordered DList are $\delta$'s (type=2) and then all other elements: $b$ (type=0) and $b^\dagger$ (type=1) unordered. Constant elements are removed.*/
        DList rearrange();

        /*! \brief Removes the first element with "data.get\_type()==type" found in DList. Updates actual pointer to be the first node.*/
        void remove(unsigned int type);

        /*! \brief Removes the element for which the actual pointer, "actual", is pointing at in DList.*/
        void remove_actual();

        /*! \brief Shifts actual pointer to next node. If actual node is the end node, stops.*/
        void shift_right() {
            if (actual == 0 || actual->nxt == 0) actual = end;
            else actual = actual->nxt;
        }

        /*! \brief Shifts actual pointer to previous node. If actual node if first node (begin), stops.*/
        void shift_left() {
            actual = actual -> prv;
            if (actual == 0) actual = begin;
        }

        /*! \brief Swaps the actual node with the next node of DList.*/
        void swap_next();


        //Reading and accessing data

        /*! \brief Returns elemtype of the node being pointed by actual (current element).*/
        elemType get() {
            return actual->data;
        }

        /*! \brief Returns the sign of DList.*/
        int getSign() {
            return sign;
        }

        /*! \brief Creates and returns an integer vector sequence container with the ids (data fields) of $b$'s and $b^\dagger$'s elements.*/
        vector<int> getIds();

        /*! \brief Updates integer vector sequence containers "id0" and "id1" with ids (data fields) of $b$'s and $b^\dagger$'s elements, respectively. "sign" is updated with the sign of DList. "BandBdagger" is a boolean which is true if DList contains at least one $b$ or $b^\dagger$, and false otherwise.*/
        void getBandBdaggerIds(bool &BandBdagger, vector<string> &id0, vector<string> &id1, int &sign);

        /*! \brief Updates integer vector sequence containers "id0" and "id1" with first and second ids (data fields) of $\delta$ elements, respectively. "sign" is updated with the sign of DList. "AllDeltas" is a boolean which is true if all elements in DList are of $\delta$ type, and false otherwise.*/
        void getDeltaIds(bool &AllDeltas, vector<string> &id0, vector<string> &id1, int &sign);

        /*! \brief Updates integer vector sequence containers "id0" and "id1" with ids (data fields) of $b$'s and $b^\dagger$'s elements, respectively, and "id2" and "id3" integer vector sequence containers with first and second data fields of $\delta$'s elements, respectively. "sign" is updated with the sign of DList.*/
        void getBandBdaggerAndDeltasIds(vector<string> &id0, vector<string> &id1, vector<string> &id2, vector<string> &id3, int &sign);

        /*! \brief Returns the number of elements of type $\delta$ (type=2).*/
        int numDeltas();

        /*! \brief Returns the number of elements of type b (type=0).*/
        int numBs();


        /*! \brief Search the last element with "data.get\_type()==type1" found in DList. Returns true a node was found.*/
        bool search_last(unsigned int type1);

        /*! \brief Search the first element with "data.get\_type()==type" found in DList. Returns true if the symbol is not the first, and false otherwise.*/
        bool search_first(unsigned int type1);

        /*! \brief Checks for the order of appearance in DList of types "type0" and "type1". Returns true if order of appearance is the same as the parameter's order and false otherwise.*/
        bool search_first(unsigned int type0, unsigned int type1);

        /*! \brief Searches for the element with "data.get\_type()==type" found in DList. Returns true if the element is found, false otherwise.*/
        bool search_elem(unsigned int type1);


        //Querying and booleans

        /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s matches and if each one is less or equal than N of SO(2N).*/
        bool check();

        /*! \brief Checks the indexes of $\delta$ elements. They must be less or equal to the n of SO(2n). Checks also if the the indexes of a delta are equal. Returns true if each $\delta$ is not zero, false otherwise.*/
        bool checkDeltaIndex();

        /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s is less or equal than N of SO(2N). Returns true if so, false otherwise.*/
        bool check_num();

        /*! \brief Verifies if the number of $b$'s and $b^\dagger$'s match. Returns true if they match, false otherwise.*/
        bool check_same_num();

        /*! \brief Returns true if actual pointer is pointing to the last (end) node of DList.*/
        bool isActualLast() {
            return (actual == end) ? true : false;
        }

        /*! \brief Returns true if DList has no nodes.*/
        bool isEmpty() {
            bool epty = true;
            if (begin != 0) epty = false;
            return epty;
        }

        /*! \brief Returns true if there is no elements of type $\delta$ in DList.*/
        bool hasNoDeltas();

        /*! \brief Returns true if all nodes in DList are of $\delta$ type.*/
        bool hasOnlyDeltas();

        /*! \brief Returns true if there is elements with the same id (data fields) in the DList (repeated ids).*/
        bool hasRepeatedIndex();


        //Operators

        /*! \brief Copies a DList.*/
        DList& operator=(const DList& L);

        /*! \brief Negates operator, change sign of DList.*/
        const DList operator-()const;


        //Friends

        /*! \brief Creates and returns a pointer to a new copy of a DList.*/
        friend DList* copy(DList *L);

        /*! \brief Applies the following identity:
          \f{eqnarray*}{
          b_i * b^\dagger_j = \delta_{i,j} - b^\dagger_j * b_i
          \f}
          input DList L keeps delta term and function returns the swapped term.
          @param[in,out] L, DList term to be processed
          @para[in] braketmode, if true if last element in DList is a b, then the L is cleared
          @return returns expression with b_i * b^\dagger_j swapped or empty expression if b is the last term in L
        */
        friend DList contract_deltas(DList &L, bool braketmode);

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
        friend DList ordering(DList &L, bool braketmode);


        /*! \brief Creates and returns a string with the deltas and constants of a DList.*/
        friend string printDeltas(DList &L);


        /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
        friend DList& operator*(DList& L, elemType j);

        /*! \brief Creates and returns new DList that joins two DLists by order of parameters.*/
        friend DList operator*(const DList& L, const DList &M);

        /*! \brief Negates the sign of a DList and add the elemtype "j" at end of it.*/
        friend DList& operator-(DList& L, elemType j);

        /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
        friend DList& operator,(DList& L, elemType j);

        /*! \brief Sends to output stream ostream a string with the corresponding expression of the DList.*/
        friend ostream& operator<<(ostream& out, DList &L);

        /*! \brief Sends to output stream ostream a string with the corresponding expression of the DList.*/
        friend ostream& operator<<(ostream& out, DList *L);

        //same as operator* and operator,
        /*! \brief Adds element "j" to the end of DList. Returns pointer to DList.*/
        friend DList& operator<<(DList &L, elemType j);

        /*! \brief Copies DList. Creates and returns a new DList with nodes of both DLists. Sign is the product of both products.*/
        friend DList& operator<<(DList &L, DList &M);

        /*! \brief Returns true if two DLists are equal.*/
        friend bool operator==(DList &L, DList &M);

    };

}

#endif
