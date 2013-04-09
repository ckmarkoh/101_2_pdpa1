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
		_backup_container= new BSTree<BSTreeObj>();
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
		size_t s = _container->size();
		assert(s>1);
		size_t pos = _rnGen(unsigned(s-1));
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

   bool rotate(size_t id=0,bool right=false){
   		//cout<<"rotate"<<endl;
        return  _container->rotate(id,right);  // for BST only
   }

   void random_rotate(){
   	//	cout<<"print0"<<endl;
   	//	print(0,1);
   		int i=0;
		while((! _container->rotate(_rnGen(unsigned(_container->size()-1)),bool(_rnGen(unsigned(2))) ) )&&(i++<10));
   	//	cout<<"print1"<<endl;
	//	print(0,1);
   }
	
   void random_neighbor(){//BUG
	   /*	if(_setted_size!=getContainerSize()){
			cout<<"print3"<<endl;
			print(0,1);
			_container->_backup_container->
			cout<<"print4"<<endl;
			print(0,1);
			assert(0);
		}*/
		//container_backup();
		//_backup_container->_container->
		//assert(_setted_size==getContainerSize());
		if(bool(_rnGen(unsigned(2)))){
			//		cout<<"random_rotate"<<endl;
			random_rotate();
		}
		else{
			//		cout<<"random_exchange"<<endl;
			random_exchange();
		//	random_rotate();
		}
			//cout<<"print2"<<endl;
			//print(0,1);
		//assert(_setted_size==getContainerSize());
   }//BUG



/*
	void restore_backup(){//TODO
		//_container->clear();
		cout<<"restore backup 1"<<endl;
		cout<<"*******************container****************"<<endl;
		_container->print();
		cout<<"*******************backup*******************"<<endl;
		_backup_container->print();
		
		_container=newTree(_backup_container);
		cout<<"restore backup 2"<<endl;

		cout<<"*******************container****************"<<endl;
		_container->print();
		cout<<"*******************backup*******************"<<endl;
		_backup_container->print();

	}
	void container_backup(){//TODO
		//_backup_container->clear();
		cout<<"container backup 1"<<endl;
		cout<<"*******************container****************"<<endl;
		_container->print();
		cout<<"*******************backup*******************"<<endl;
		_backup_container->print();

		_backup_container=newTree(_container);
		cout<<"container backup 2"<<endl;
		cout<<"*******************container****************"<<endl;
		_container->print();
		cout<<"*******************backup*******************"<<endl;
		_backup_container->print();
	}


  	void backup()//TODO 
	{
		cout<<"overloaded assign"<<endl;
	//	queue< BSTreeNode<T>* > q;
		BSTree<BSTreeObj>* newtree= new BSTree<BSTreeObj>();
//		BSTreeNode<T>* it0=t->_root;
		BSTree<BSTreeObj>::iterator it0=t->root();
		//BSTree<BSTreeObj>::iterator it0 =t->root();
		queue< BSTree<BSTreeObj>::iterator > q;
		q.push( it0 );
	//	int i=0;
		while(q.size()>0){
			//	BSTreeNode<T>* it=q.front();
				BSTree<BSTreeObj>::iterator it=q.front();
				q.pop();
				if((it!=t->end())&&((*it).getId()!=-1)){
				//	if(it!=t->root()){
				//		cout<<"insert to tree parent:"<<it->_pare->_data<<endl;
				//	}
					//cout<<"insert to tree:"<<it->_data<<endl;
					cout<<"insert to tree:"<<*it<<endl;
					newtree->insert(*it);
					BSTree<BSTreeObj>::iterator it1=it;
					BSTree<BSTreeObj>::iterator it2=it;
					
					if(it1.to_left_child()){
					//	cout<<"push to queue:"<<it->_left->_data<<endl;
		//				cout<<"push to queue:"<<*it1<<endl;
						q.push(it1);
					}
					if(it2.to_right_child() && ((it!=t->end())&&((*it).getId()!=-1))   ){
		//				cout<<it->_right<<endl;
		//				cout<<t->_eNode<<endl;
		//				cout<<"push to queue:"<<it->_right->_data<<endl;
		//				cout<<"push to queue:"<<*it2<<endl;
						q.push(it2);
					}
				}
				//if(i++>100){break;}
		}
		cout<<"complete overloaded assign"<<endl;
	//_node = i._node;
	 return newtree; 
	}*/

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
		
		_container->clear();	
		for(size_t i=0;i<_backup_vec.size();i++){
			insert(_backup_vec[i].getId(),_backup_vec[i].getBlock(),0);
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
	void setSize(size_t s){
		_setted_size=s;
	}
private:
   BSTree<BSTreeObj>*   _container;
   BSTree<BSTreeObj>*  _backup_container;
   vector<BSTreeObj> _backup_vec;
	float _cost;
	size_t _setted_size;
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
	  cout<<*li<<endl;
      //if (idx % 5 == r) cout << endl;
   }
};

#endif // ADT_TEST_H
