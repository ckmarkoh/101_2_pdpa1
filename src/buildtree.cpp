#include "pdpa1.h"
#include "bstreeMgr.h"
#include "rnGen.h"
#include<iostream>
#include <math.h>
#define E 2.71828182845
#define R 0.999
#define T 10000
#define FROZEN 1000
using namespace std;
void PDPA1::tree_debug(){
	cout<<"cost:"<<_treemgr.getCost()<<endl;
	_treemgr.print(0,1);
}
void PDPA1::build_tree(){
	assert(_block.size()>=3);
	_treemgr.insert(float(_block.size())*0.5,_block[0]);
	_treemgr.insert(float(_block.size())*0.15,_block[1]);
	_treemgr.insert(float(_block.size())*0.85,_block[2]);
	_treemgr.setSize(_block.size());
	for(size_t i=3;i<_block.size();i++){
		_treemgr.insert(float(_block.size()),_block[i],1);
	}
	
//	tree_debug();
	/*for(size_t i=0;i<50;i++){
	_treemgr.random_exchange();
	}*/
//	simu_anneal();

//	tree_debug();
}
void PDPA1::simu_anneal(){
	float tempture=T;
	while((tempture*=R)>FROZEN){
		float origin_cost=_treemgr.getCost();
	//	cout<<"before random_neighbor"<<endl;
		_treemgr.random_neighbor();
	//	cout<<"after random_neighbor"<<endl;
		float delta_cost=_treemgr.getCost()-origin_cost;
		if(delta_cost>0){
		//		cout<<"temperature:"<<tempture<<endl;
		//		cout<<"delta_cost:"<<delta_cost<<endl;
			if(_treemgr.getRandom( pow(E,(delta_cost/tempture)) ) >= 1.0){
		//		cout<<"  restore"<<endl;
				_treemgr.restore_backup();
			}
		}
	}
}


