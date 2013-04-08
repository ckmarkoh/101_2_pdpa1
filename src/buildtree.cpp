#include "pdpa1.h"
#include "bstreeMgr.h"
#include "rnGen.h"
#include<iostream>
using namespace std;
void PDPA1::tree_debug(){
	_treemgr.print(0,1);
}
void PDPA1::build_tree(){
	assert(_block.size()>=3);
	_treemgr.insert(float(_block.size())*0.5,_block[0]);
	_treemgr.insert(float(_block.size())*0.15,_block[1]);
	_treemgr.insert(float(_block.size())*0.85,_block[2]);
	for(size_t i=3;i<_block.size();i++){
		_treemgr.insert(_block.size(),_block[i],1);
	}
	tree_debug();
		_treemgr.random_exchange();
	tree_debug();
}


