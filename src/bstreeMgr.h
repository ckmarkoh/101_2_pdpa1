/****************************************************************************
  FileName     [ adtTest.h ]
  PackageName  [ main ]
  Synopsis     [ Define BSTreeMgr class and commands ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2010 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef BSTREE_MGR_H
#define BSTREE_MGR_H

#include <iostream>
#include <string>
#include "bstree.h"
#include "node.h"

using namespace std;


//----------------------------------------------------------------------
//    Classes for ADT test program
//----------------------------------------------------------------------
class BSTreeObj
{
public:
   BSTreeObj(){};
//   BSTreeObj(const float& s)
  // : _id(s){_b}
   BSTreeObj(const float& s,Block* b)
   : _id(s),_b(b){}

   // { if (int(_id.size()) > _idLen) _id.resize(_idLen); }
   BSTreeObj(const BSTreeObj& o) : _id(o._id),_b(o._b) {}
   bool operator < (const BSTreeObj& o) const { return (_id < o._id); }
   bool operator > (const BSTreeObj& o) const { return (_id > o._id); }
   bool operator == (const BSTreeObj& o) const { return (_id == o._id); }
//   static void setLen(int len) { _idLen = len; }
   friend ostream& operator << (ostream& os, const BSTreeObj& o){
	   return (os << "id:"<<o._id<<" name:"<<o._b->get_name() );
   }
   Block* getBlock(){return _b;}
private:
   float      _id;  // _data should alywas be between [0, _dataRange - 1]
   Block* 	  _b;
  // static int  _idLen;
};
/*
ostream& operator << (ostream& os, const BSTreeObj& o)
{
}
*/
class BSTreeMgr
{
public:
	BSTreeMgr(){}

	  void reset() { deleteAll();}// BSTreeObj::setLen(len); }

//   bool add() { return insert(BSTreeObj()); }  // insert random number

   void deleteAll() { _container.clear(); }
/*   bool deleteObj(const BSTreeObj& o) { return _container.erase(o); }*/
   bool deleteObj(const size_t o) { return _container.erase(getPos(o)); }
   bool insert(BSTreeObj& o) { return _container.insert(o); }
/*   void deleteFront(size_t repeat = 1) {
      for (size_t i = 0; i < repeat; ++i) _container.pop_front(); 
	  }
   void deleteBack(size_t repeat = 1) {
      for (size_t i = 0; i < repeat; ++i) _container.pop_back(); }*/
/*	void deleteRandom(size_t repeat = 1) {
		size_t s = _container.size();
		for (size_t i = 0; i < repeat; ++i) {
			 size_t pos = rnGen(s);
			 if (_container.erase(getPos(pos))) --s;
		}
	}*/

   void print(bool reverse = false, bool verbose = false) {
      if (verbose)
         _container.print();  // for BST only
      cout << "=== ADT  ===" << endl;
      if (reverse) printBackward();
      else printForward();
      cout << endl;
   }

   void rotate(size_t id=0,bool right=false){
   		cout<<"rotate"<<endl;
         _container.rotate(id,right);  // for BST only
   }

   BSTree<BSTreeObj>::iterator getPos(size_t pos) {
         size_t i = 0;
         BSTree<BSTreeObj>::iterator li = _container.begin();
         BSTree<BSTreeObj>::iterator lj = _container.end();
         while ((li != lj) && (i++ != pos)) ++li;
         return li;
   }
 
private:
   BSTree<BSTreeObj>   _container;

   // private functions
   // return end() if 'pos' passes the end
  void printForward() {
      size_t idx = 0;
      BSTree<BSTreeObj>::iterator li = _container.begin();
      for (; li != _container.end(); ++li)
         printData(idx++, li, 4);
   }
   void printBackward() {
      if (_container.empty()) return;
      size_t idx = _container.size() - 1;
      size_t r = (idx + 1) % 5;
      BSTree<BSTreeObj>::iterator li = _container.end(); --li;
            do {
            printData(idx, li, r);
            --idx;
         } while (li-- != _container.begin());
   }
   void printData(size_t idx, BSTree<BSTreeObj>::iterator li, size_t r) {
      cout << "[" << setw(3) << right << idx << "] = "
           << setw(3) << right << *li << "   ";
      if (idx % 5 == r) cout << endl;
   }
};

#endif // ADT_TEST_H
