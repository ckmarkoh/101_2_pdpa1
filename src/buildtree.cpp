#include "pdpa1.h"
#include "bstreeMgr.h"
#include "rnGen.h"
#include<iostream>
#include <math.h>
#define E 2.71828182845
#define R 0.9999
#define T 1000
#define FROZEN 0.0002

//#define FROZEN 0.0002
//#define R 0.9999
using namespace std;
void PDPA1::tree_debug(){
	cout<<"cost:"<<_treemgr.getCost()<<endl;
	_treemgr.print(0,1);
}



void PDPA1::build_tree(){
	cout<<"E:"<<E<<endl;
	cout<<"R:"<<R<<endl;
	cout<<"T:"<<T<<endl;
	cout<<"FROZEN"<<FROZEN<<endl;
	float min_block_cost=0;
	float min_net_cost=0;
	float min_pos_cost=0;
	assert(_block.size()>=3);
	min_block_cost+=float(_block[1]->area());
	min_block_cost+=float(_block[2]->area());
	min_block_cost+=float(_block[3]->area());
	_treemgr.insert(float(_block.size())*0.5,_block[0]);
	_treemgr.insert(float(_block.size())*0.20,_block[1]);
	_treemgr.insert(float(_block.size())*0.80,_block[2]);
	for(size_t i=3;i<_block.size();i++){
		//_treemgr.insert(float(_block.size()),_block[i],1);
		min_block_cost+=float(_block[i]->area());
		while(!_treemgr.insert(_block.size(),_block[i],1));
	}
	min_net_cost=sqrt(min_block_cost)*float(_net.size());
	cout<<"min_block_cost:"<<min_block_cost<<endl;
	cout<<"min_net_cost:"<<min_net_cost<<endl;
	min_pos_cost=(_outline[0]+_outline[1])*0.5*_net.size();
	_treemgr.setMinCost(min_block_cost,min_net_cost,min_pos_cost,_outline[0],_outline[1]);
	_treemgr.get_block_cost();
	_treemgr.setNetVec(_net);

//	_treemgr.test_unbalanced();
/*
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
/*
		draw_block("file1.raw");
		_treemgr.getCost();
		for(size_t i=1;i<100000;i++){
			_treemgr.smart_exchange_rotate();
		}
		_treemgr.getCost();
		draw_block("file2.raw");*/
}



void PDPA1::simu_anneal(){
	unsigned times=0;
	_treemgr.printCost();
	_myusage.reset();
	float tempture=T;
	while((tempture*=R)>FROZEN){
		times++;
		float origin_cost=_treemgr.getCost();
//		cout<<"before random_neighbor"<<endl;
		_treemgr.random_neighbor();
//		cout<<"after random_neighbor"<<endl;
		float delta_cost=_treemgr.getCost()-origin_cost;
		if(delta_cost>0){
		//		cout<<"temperature:"<<tempture<<endl;
		//		cout<<"delta_cost:"<<delta_cost<<endl;
		//	cout<<"probability:"<<pow(E,(delta_cost/tempture))<<endl; 
			if(_treemgr.getRandom( pow(E,(delta_cost/tempture)) ) >= 1.0){
		//		cout<<"  restore"<<endl;
				_treemgr.restore_backup();
			}
		}
	}
	cout<<"times:"<<times<<endl;
	_myusage.report(1,1);
	_treemgr.printCost();
}

