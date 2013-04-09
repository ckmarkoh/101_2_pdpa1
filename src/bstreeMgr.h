/****************************************************************************
  FileName     [ adtTest.h ]
  PackageName  [ main ]
  Synopsis     [ Define BSTreeMgr class and commands ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2010 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef BSTREE_MGR_H
#define BSTREE_MGR_H

#include <vector>
#include <iostream>
#include <string>
#include "bstree.h"
#include "node.h"
#include "rnGen.h"
using namespace std;


//----------------------------------------------------------------------
//    Classes for ADT test program
//----------------------------------------------------------------------
class BSTreeObj
{
public:
   BSTreeObj(){ _id=-1;};
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
//	   return (os << "id:"<<o._id<<" name:"<<o._b->get_name() );
	   return (os <<o._b->get_name() );
   }
   Block* getBlock(){return _b;}
   void setID(float i){_id=i;}
	float getId(){return _id;}
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
	BSTreeMgr(){
		_container= new BSTree<BSTreeObj>();
		//_backup_container= new BSTree<BSTreeObj>();
	}

	  void reset() { deleteAll();}// BSTreeObj::setLen(len); }

   void deleteAll() { _container->clear(); }
/*   bool deleteObj(const BSTreeObj& o) { return _container->erase(o); }*/
   bool deleteObj(const size_t o) { return _container->erase(getPos(o)); }
   bool insert(BSTreeObj& o) { return _container->insert(o); }

   bool insert(float f,Block* b,bool random=false) {
   		if(random){
			f=_rnGen(f);
		}
		BSTreeObj o(f,b);
	   return _container->insert(o); 
   }

	void random_exchange() {
		container_backup();
		size_t s = _container->size();
		assert(s>1);
		size_t pos = _rnGen(unsigned(s));
		BSTree<BSTreeObj>::iterator it =getPos(pos);
		Block* b = (*it).getBlock();
		 if (_container->erase(it)){
			while(!insert(s,b,1 )){cout<<"1"<<endl;}
		 }else{
		// 	print();
		//	cout<<"pos:"<<pos<<endl;
			//cout<<"it:"<<*it<<endl;
		 //	_container->print();
		 	assert(0);
		}
	}
   void print(bool reverse = false, bool verbose = false) {
      if (verbose)
         _container->print();  // for BST only
      cout << "=== ADT  ===" << endl;
      if (reverse) printBackward();
      else printForward();
      cout << endl;
   }

   void random_rotate(){
   		//cout<<"rotate"<<endl;
		container_backup();
		size_t z=0;
		while(true){
			size_t id=_rnGen(unsigned(_container->size()));
			BSTree<BSTreeObj>::iterator it =getPos(id);
			bool right=bool(_rnGen(unsigned(2))); 
			cout<<"id:"<<id<<endl;

        	if(_container->rotate(it,right)){
			/*	cout<<"1"<<endl;
				if(right){
					assert(it.to_left_child());
				}
				else{
					assert(it.to_right_child());
				}
					_backup_right=right;
					_backup_it=it;		*/
				break;
				// for BST only
   			}
			if(z++>10){break;}
   		}
   }

   bool rotate(size_t id=0,bool right=false){
   		//cout<<"rotate"<<endl;
		return _container->rotate(id,right);
   }
  
	
   void random_neighbor(){//BUG
		if((_rnGen(unsigned(12)))%2==0){
			cout<<"random_exchange"<<endl;
			_random_state=EXCHANGE;
			random_exchange();
		}
		else{
			cout<<"random_rotate"<<endl;
			_random_state=ROTATE_TREE;
			random_rotate();
		}
   }//BUG


	void container_backup(){
		queue< BSTree<BSTreeObj>::iterator > q;
		_backup_vec.clear();
		BSTree<BSTreeObj>::iterator it0=_container->root();
		q.push( it0 );
		while(q.size()>0){
			BSTree<BSTreeObj>::iterator it=q.front();
			q.pop();
			_backup_vec.push_back(*it);
			if(it!=_container->end()){
				 BSTree<BSTreeObj>::iterator it1 = it;
				 BSTree<BSTreeObj>::iterator it2 = it;
				 if(it1.to_left_child()){
					q.push(it1);
				 }
				 if(it2.to_right_child()){
					q.push(it2);
				 }
			}
		}
	}
	void restore_backup(){
		
		if( (_random_state==EXCHANGE) || (_random_state==ROTATE_TREE)){
			cout<<"restore exchange"<<endl;
			_container->clear();	
			for(size_t i=0;i<_backup_vec.size();i++){
				insert(_backup_vec[i].getId(),_backup_vec[i].getBlock(),0);
			}
		}
		else if(_random_state==ROTATE_BLOCK){

			assert(0);
		}
		else{
			assert(0);
		}
	}

   BSTree<BSTreeObj>::iterator getPos(size_t pos) {
         size_t i = 0;
         BSTree<BSTreeObj>::iterator li = _container->begin();
         BSTree<BSTreeObj>::iterator lj = _container->end();
         while ((li != lj) && (i++ != pos)) ++li;
         return li;
   }

   void traverse_from_root(){
   		_cost=0;
		BSTree<BSTreeObj>::iterator it1=_container->root();
  		recTraverse(it1,1); 
   }
   void recTraverse(BSTree<BSTreeObj>::iterator& it,float level){
		 BSTree<BSTreeObj>::iterator it1 = it;
		 BSTree<BSTreeObj>::iterator it2 = it;
		 _cost+=level*level;
	//	 cout<<setw((int)level)<<level<<":"<<*it<<endl;
		 if(it1.to_left_child()){
			recTraverse(it1,level+1);
		 }
		 if(it2.to_right_child()){
			recTraverse(it2,level+1);
		 }
   }
	
	float getCost(){
		traverse_from_root();
		return _cost;
	}

	float getRandom(float f){
		return _rnGen(f);
	}
/*	void setSize(size_t s){
		_setted_size=s;
	}*/
private:
   BSTree<BSTreeObj>*   _container;
   //BSTree<BSTreeObj>*  _backup_container;

	
	float _cost;
//	size_t _setted_size;


   vector<BSTreeObj> _backup_vec; // EXCHANGE BACKUP

	bool _backup_right; //ROTATE TREE BACKUP
	BSTree<BSTreeObj>::iterator _backup_it; //ROTATE BACKUP 


	enum {
		EXCHANGE=0,
		ROTATE_TREE,
		ROTATE_BLOCK
	}_random_state;

	RandomNumGen _rnGen;
   // private functions
   // return end() if 'pos' passes the end
	
   size_t getContainerSize() {
      size_t idx = 0;
      BSTree<BSTreeObj>::iterator li = _container->begin();
      for (; li != _container->end(); ++li){
         idx++;
		}
		return idx;
   }


  void printForward() {
      size_t idx = 0;
      BSTree<BSTreeObj>::iterator li = _container->begin();
      for (; li != _container->end(); ++li)
         printData(idx++, li, 4);
   }
   void printBackward() {
      if (_container->empty()) return;
      size_t idx = _container->size() - 1;
      size_t r = (idx + 1) % 5;
      BSTree<BSTreeObj>::iterator li = _container->end(); --li;
            do {
            printData(idx, li, r);
            --idx;
         } while (li-- != _container->begin());
   }
   void printData(size_t idx, BSTree<BSTreeObj>::iterator li, size_t r) {
      //cout << "[" << setw(3) << right << idx << "] = "
        //   << setw(3) << right << *li << "   ";
	  //cout<< *li<<endl;
//	  cout<<*li<<endl;
      //if (idx % 5 == r) cout << endl;
   }
};

#endif // ADT_TEST_H
