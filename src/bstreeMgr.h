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
#include <math.h>
#include "bstree.h"
#include "node.h"
#include "rnGen.h"
#include "yheight.h"
#include <queue>
#define COST_NORMALIZE 600
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
	   return (os << "id:"<<o._id<<" name:"<<o._b->getName()<<" w:"<<o._b->getW()<<" h:"<<o._b->getH() );
	  // return (os <<o._b->getName() );
   }
   Block* getBlock(){return _b;}
   void setID(float i){_id=i;}
	
   void swap_block(BSTreeObj& tobj){
		Block* temp =tobj._b;
		tobj._b=this->_b;
		this->_b=temp;
   }

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
//		_container= new BSTree<BSTreeObj>();
		//_backup_container= new BSTree<BSTreeObj>();
		//_mincost=0;
	}


	  void reset() { deleteAll();}// BSTreeObj::setLen(len); }

   void deleteAll() { _container.clear(); }
/*   bool deleteObj(const BSTreeObj& o) { return _container.erase(o); }*/
   bool deleteObj(const size_t o) { return _container.erase(getPos(o)); }
   bool insert(BSTreeObj& o) { return _container.insert(o); }

   bool insert(float f,Block* b,bool random=false) {
   		if(random){
			f=_rnGen(f);
		}
		BSTreeObj o(f,b);
	   if(_container.insert(o)){
	   	//	_mincost+=float(b->area());
	   		return true;
	   }	
	   else{
			return false;
	   }
   }
	void setMinCost(float b,float n,float p,float bx=10000, float by=10000){
		_min_block_cost=b;
		_min_net_cost=n;
		_min_pos_cost=p;
		_min_box_x=bx;
		_min_box_y=by;

	 block_cost=0;
	 net_cost=0;
	 pos_cost=0;
	 penalty=0;
	 cn=0;


	}
	void random_exchange() {
		//container_backup();
		size_t s = _container.size();
		assert(s>1);
		size_t pos = _rnGen(unsigned(s),1);
		BSTree<BSTreeObj>::iterator it =getPos(pos);
		
		Block* b = (*it).getBlock();
		 if (_container.erase(it)){
			while(!insert(s,b,1 )){}//cout<<"1"<<endl;}
		 }else{
		 	assert(0);
		}
	}
	void random_exchange_block() {
		//container_backup();
		size_t s = _container.size();
		assert(s>1);
		BSTree<BSTreeObj>::iterator it =getPos(_rnGen(unsigned(s),1));
		BSTree<BSTreeObj>::iterator it2 =getPos(_rnGen(unsigned(s)));
		while(! ((it!=_container.end())&&(it2!=_container.end())&&(it!=it2)) ){
			it =getPos(_rnGen(unsigned(s),1));
			it2 =getPos(_rnGen(unsigned(s)));
		}
		//cout<<"swap:"<<*it<<endl;
		//cout<<"swap:"<<*it2<<endl;
		(*it).swap_block(*it2);
	}

	bool smart_exchange_rotate(){
		if(_rnGen(unsigned(8))>1){return false;}
		size_t s = _container.size();
		BSTree<BSTreeObj>::iterator it =getPos(_rnGen(unsigned(s)));
		Block* b=(*it).getBlock();
		assert(it!=_container.end());
		size_t j=0;
		while(true){
			if( !b->inRange(unsigned(_min_box_x),unsigned(_min_box_y)) ){//cout<<"1"<<endl;
				BSTree<BSTreeObj>::iterator it2 =getPos(_rnGen(unsigned(s)));	
				Block* b2=(*it2).getBlock();
				size_t i=0;
				while(! (b2->inRange(unsigned(_min_box_x),unsigned(_min_box_y)) && (  b2->area() <= b->area()   )) ){//cout<<"2"<<endl;

					it2 =getPos(_rnGen(unsigned(s)));
					b2=(*it2).getBlock();
					if(i++>s){
						if(b2->inRange(unsigned(_min_box_x),unsigned(_min_box_y))){
							float id=(*it2).getId();
							 if (_container.erase(it)){
								do{
									if(_rnGen(unsigned(6))%2==0){
										id*=1.01;
									}else{
										id*=0.99;
									}
								}while(!insert(id,b,0 ));//cout<<"1"<<endl;}
							 }else{
								assert(0);
							}
							return true;
						}
						return false;
					}
				}
				if(b->lie_or_stand()!=b2->lie_or_stand()){
					backuped_rotate(b);
					backuped_rotate(b2);
				}
					assert(it!=_container.end());
					//cout<<"swap"<<endl;
					(*it).swap_block(*it2);
				return true;

			}
			if(j++>s){
				return false;
			}
			it=getPos(_rnGen(unsigned(s)));
			b=(*it).getBlock();
		}
		return false;
	}

	void test_unbalanced(){
		vector<unsigned> tv;
		unsigned s=_container.size();
		for(size_t i=0;i<s;i++){
			tv.push_back(0);
		}
		unsigned j=0;
		while(j++<1000){
			unsigned id=_rnGen(s,1);
			tv[id]++;
		}
		for(size_t i=0;i<s;i++){
			cout<<"i:"<<i<<" tv:"<<tv[i]<<endl;
		}
	}

   void print(bool reverse = false, bool verbose = false) {
      if (verbose)
         _container.print();  // for BST only
      cout << "=== ADT  ===" << endl;
      if (reverse) printBackward();
      else printForward();
      cout << endl;
   }
	void random_rotate_block(){
			size_t id=_rnGen(unsigned(_container.size()),1);
			BSTree<BSTreeObj>::iterator it =getPos(id);
			Block* tempb=(*it).getBlock();
			backuped_rotate(tempb);
	}

	void backuped_rotate(Block* tempb){
			tempb->rotate();
			_backup_block.push(tempb);
	}
   void random_rotate(){
   		//cout<<"rotate"<<endl;
		//container_backup();
		size_t z=0;
		while(true){
			size_t id=_rnGen(unsigned(_container.size()),1);
			BSTree<BSTreeObj>::iterator it =getPos(id);
			bool right=bool(_rnGen(unsigned(2))); 
			//cout<<"id:"<<id<<endl;

        	if(_container.rotate(it,right)){
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
		return _container.rotate(id,right);
   }
   
	
   void random_neighbor(){//BUG
		container_backup();

/*		for(size_t i=0;i<10;i++){
			smart_exchange_rotate();
		}*/
		if(!smart_exchange_rotate()){
			unsigned hasdo=0;
		
			while(hasdo<=0){
				if((_rnGen(unsigned(12)))%4  == 0){
			//		cout<<"random_exchange"<<endl;
					_random_state=EXCHANGE_TREE;
					random_exchange();
					hasdo++;
				}
				if((_rnGen(unsigned(12)))%4==1){
			//		cout<<"random_rotate"<<endl;
					_random_state=ROTATE_TREE;
					random_rotate();
					hasdo++;
				}
				if((_rnGen(unsigned(12)))%4==2){
			//		cout<<"random_exchange_block"<<endl;
					_random_state=EXCHANGE_BLOCK;
					random_exchange_block();
					hasdo++;
				}
				if((_rnGen(unsigned(12)))%4== 3){
			//		cout<<"random_rotate_block"<<endl;
						_random_state=ROTATE_BLOCK;
						random_rotate_block();	
				}
			}
		}
   }//BUG


	void container_backup(){
		queue< BSTree<BSTreeObj>::iterator > q;
		_backup_vec.clear();
		BSTree<BSTreeObj>::iterator it0=_container.root();
		q.push( it0 );
		while(q.size()>0){
			BSTree<BSTreeObj>::iterator it=q.front();
			q.pop();
			_backup_vec.push_back(*it);
			if(it!=_container.end()){
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
		restore_container();
		restore_block();
	}

	void restore_container(){
			_container.clear();	
			for(size_t i=0;i<_backup_vec.size();i++){
				insert(_backup_vec[i].getId(),_backup_vec[i].getBlock(),0);
			}
	}
	void restore_block(){
			while(_backup_block.size()>0){
				_backup_block.front()->rotate();
				_backup_block.pop();
			}
			
	}
	
   BSTree<BSTreeObj>::iterator getPos(size_t pos) {
         size_t i = 0;
         BSTree<BSTreeObj>::iterator li = _container.begin();
         BSTree<BSTreeObj>::iterator lj = _container.end();
         while ((li != lj) && (i++ != pos)) ++li;
         return li;
   }
	//*OLD COST FUNCTION*//
/*   float balanced_tree_cost(){
   		
		BSTree<BSTreeObj>::iterator it1=_container.root();
  		return balancedRecTraverse(it1,1); 
   }
   float balancedRecTraverse(BSTree<BSTreeObj>::iterator& it,float level){
		 BSTree<BSTreeObj>::iterator it1 = it;
		 BSTree<BSTreeObj>::iterator it2 = it;
		 float cost=level*level;
	//	 cout<<setw((int)level)<<level<<":"<<*it<<endl;
		 if(it1.to_left_child()){
			cost+=balancedRecTraverse(it1,level+1);
		 }
		 if(it2.to_right_child()){
			cost+=balancedRecTraverse(it2,level+1);
		 }
		 return cost;
   }*/
	//*END OLD COST FUNCTION*//

		

	void get_block_cost(){
		_yheight.clear();
		//unsigned xpos=0;
		BSTree<BSTreeObj>::iterator it=_container.root();
		blockRecTraverse(it,0);	
	}
	void blockRecTraverse(BSTree<BSTreeObj>::iterator& it,unsigned xpos){
		Block* b=(*it).getBlock();
		unsigned ypos=_yheight.insert(xpos,xpos+b->getW(),b->getH());
		b->setXY(xpos,ypos);
		 BSTree<BSTreeObj>::iterator it1 = it;
		 BSTree<BSTreeObj>::iterator it2 = it;
		 if(it1.to_left_child()){
			blockRecTraverse(it1,xpos+b->getW());
		 }
		 if(it2.to_right_child()){
			blockRecTraverse(it2,xpos);
		 }
	}


	float get_penalty(){
		float tempp=0;
		  //size_t idx = 0;
		  BSTree<BSTreeObj>::iterator li = _container.begin();
		  for (; li != _container.end(); ++li){
			 	if(! (*li).getBlock()->inRange(unsigned(_min_box_x),unsigned(_min_box_y)) ){
			 		tempp++;	
				}
			 }

		return tempp/_container.size();
	}

	float getCost(){
		get_block_cost();
		//balanced_tree_cost();
		//_cost=float(_yheight.find_max(0,_yheight.find_max_x())*_yheight.find_max_x());
		//float block_cost=pow(float(_yheight.find_max(0,_yheight.find_max_x())),2)+pow(_yheight.find_max_x(),2);
		float block_x=float(_yheight.find_max_x());
		float block_y=float(_yheight.find_max(0,unsigned(block_x)));
		 block_cost=block_x*block_y;
		 penalty=pow((block_x/block_y)-1,2)+get_penalty(); 
		 net_cost=get_net_cost();
		 pos_cost=get_pos_cost();
//		cout<<"block_cost:"<<block_cost<<" normalize:"<<(block_cost/_min_block_cost)<<" x:"<<block_x<<" y:"<<block_y<<endl;
//		cout<<"net_cost:"<<net_cost<<" normalize:"<<(net_cost/_min_net_cost)<<endl;
//		cout<<"penalty:"<<penalty<<endl;

		cn=
		COST_NORMALIZE*( (block_cost/_min_block_cost)+(net_cost/_min_net_cost)*0+(pos_cost/_min_pos_cost)*0.01 + penalty*10)/3  ;
//		cout<<"normalize cost:"<<cn<<endl;
	/*	if(_rnGen(unsigned(1200))%1119==1){
			cn=0;
			cout<<"distrub"<<endl;
		}*/
		return cn;
	}
	
	void printCost(){
		cout<<"block_cost:"<<block_cost<<" normalize:"<<(block_cost/_min_block_cost)<<endl;
		cout<<"net_cost:"<<net_cost<<" normalize:"<<(net_cost/_min_net_cost)<<endl;
		cout<<"pos_cost:"<<pos_cost<<" normalize:"<<(pos_cost/_min_pos_cost)<<endl;
		cout<<"penalty:"<<penalty<<endl;
		cout<<"normalize cost:"<<cn<<endl;
//		return cn;
	}

	float getRandom(float f){
		return _rnGen(f);
	}
/*	void setSize(size_t s){
		_setted_size=s;
	}*/
	void setNetVec(vector<Net* >& nv){
		_netvec.clear();
		for(size_t i=0;i<nv.size();i++){
		_netvec.push_back(nv[i]);
		}
	}
	float get_pos_cost() {
		float pos_cost=0;
		BSTree<BSTreeObj>::iterator li = _container.begin();
		for (; li != _container.end(); li++){
			pos_cost+=(*li).getBlock()->getPosX();
			pos_cost+=(*li).getBlock()->getPosY();	
		}
		return pos_cost;
	}
	float get_net_cost(){
		float cost=0;
//		for(size_t i=0; i<_netvec.size();i++){
//			cout<<"get_net_cost"<<cost<<endl;
//			cost+=float(_netvec[i]->getLength());
//		}
		return cost;
	}

private:
   BSTree<BSTreeObj>   _container;
   //BSTree<BSTreeObj>*  _backup_container;
		
	YHeight _yheight;	
//	float _cost;
//	size_t _setted_size;
	float _min_block_cost;
	float _min_net_cost;	
	float _min_pos_cost;

	float block_cost;
	float net_cost;
	float pos_cost;
	float penalty;
	float cn;

	unsigned* _weight_random;

   	vector<BSTreeObj> _backup_vec; // EXCHANGE_TREE BACKUP
	
	vector<Net*> _netvec;
	float _min_box_x;
	float _min_box_y;

	bool _backup_right; //ROTATE TREE BACKUP
	BSTree<BSTreeObj>::iterator _backup_it; //ROTATE BACKUP 
	queue<Block*> _backup_block;

	enum {
		EXCHANGE_TREE=0,
		EXCHANGE_BLOCK=0,
		ROTATE_TREE,
		ROTATE_BLOCK
	}_random_state;

	RandomNumGen _rnGen;
   // private functions
   // return end() if 'pos' passes the end
	
   size_t getContainerSize() {
      size_t idx = 0;
      BSTree<BSTreeObj>::iterator li = _container.begin();
      for (; li != _container.end(); ++li){
         idx++;
		}
		return idx;
   }


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
      //cout << "[" << setw(3) << right << idx << "] = "
        //   << setw(3) << right << *li << "   ";
	  //cout<< *li<<endl;
//	  cout<<*li<<endl;
      //if (idx % 5 == r) cout << endl;
   }
};

#endif // ADT_TEST_H
