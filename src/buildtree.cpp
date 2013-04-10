#include "pdpa1.h"
#include "bstreeMgr.h"
#include "rnGen.h"
#include<iostream>
#include <math.h>
#define E 2.71828182845
#define R 0.99
#define T 300
#define FROZEN 0.1
using namespace std;
void PDPA1::tree_debug(){
	cout<<"cost:"<<_treemgr.getCost()<<endl;
	_treemgr.print(0,1);
}
void PDPA1::build_tree(){
	float min_block_cost=0;
	float min_net_cost=0;
	assert(_block.size()>=3);
/*	min_block_cost+=float(_block[1]->area());
	min_block_cost+=float(_block[2]->area());
	min_block_cost+=float(_block[3]->area());
	_treemgr.insert(float(_block.size())*0.5,_block[0]);
	_treemgr.insert(float(_block.size())*0.20,_block[1]);
	_treemgr.insert(float(_block.size())*0.80,_block[2]);*/
	for(size_t i=0;i<_block.size();i++){
		//_treemgr.insert(float(_block.size()),_block[i],1);
		min_block_cost+=float(_block[i]->area());
		while(!_treemgr.insert(_block.size(),_block[i],1));
	}
	min_block_cost*=2;
	min_net_cost=sqrt(min_block_cost)*float(_net.size())*0.25;
	cout<<"min_block_cost:"<<min_block_cost<<endl;
	cout<<"min_net_cost:"<<min_net_cost<<endl;
	_treemgr.setMinCost(min_block_cost,min_net_cost);
	_treemgr.get_block_cost();
	_treemgr.setNetVec(_net);
//	_treemgr.test_yheight();	
//	tree_debug();
/*	for(size_t i=0;i<5;i++){
		cout<<"tree1:"<<i<<endl;
		tree_debug();
		_treemgr.random_neighbor();
		cout<<"tree2:"<<i<<endl;
		tree_debug();
		_treemgr.restore_backup();
		cout<<"tree3:"<<i<<endl;
		tree_debug();
	}
//	simu_anneal();
//		cout<<"tree1"<<endl;
//		tree_debug();

		cout<<"tree1"<<endl;
		tree_debug();
		_treemgr.random_neighbor();
		cout<<"tree2"<<endl;
		tree_debug();

		_treemgr.restore_backup();
		cout<<"tree3"<<endl;
		tree_debug();
*/	
//		simu_anneal();
//		cout<<"tree4"<<endl;
//		tree_debug();
		
//	tree_debug();
}
void PDPA1::simu_anneal(){
	float tempture=T;
	while((tempture*=R)>FROZEN){
		float origin_cost=_treemgr.getCost();
//		cout<<"before random_neighbor"<<endl;
		_treemgr.container_backup();
		_treemgr.random_neighbor();
//		cout<<"after random_neighbor"<<endl;
		float delta_cost=_treemgr.getCost()-origin_cost;
		if(delta_cost>0){
		//		cout<<"temperature:"<<tempture<<endl;
		//		cout<<"delta_cost:"<<delta_cost<<endl;
			cout<<"probability:"<<pow(E,(delta_cost/tempture))<<endl; 
			if(_treemgr.getRandom( pow(E,(delta_cost/tempture)) ) >= 1.0){
				cout<<"  restore"<<endl;
				_treemgr.restore_backup();
			}
		}
	}
}

