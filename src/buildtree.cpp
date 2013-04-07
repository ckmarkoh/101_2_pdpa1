#include "pdpa1.h"
#include "bstreeMgr.h"
#include "bstree.h"
#include "rnGen.h"
#include<iostream>
using namespace std;

void PDPA1::build_tree(){
	assert(_block.size()>=3);
	RandomNumGen rnGen(_block.size());
	BSTreeObj obj0(float(_block.size())*0.5,_block[0]);
	BSTreeObj obj1(float(_block.size())*0.15,_block[1]);
	BSTreeObj obj2(float(_block.size())*0.85,_block[2]);
	_treemgr->insert(obj0);
	_treemgr->insert(obj1);
	_treemgr->insert(obj2);
	for(size_t i=3;i<_block.size();i++){
		BSTreeObj obj3(rnGen(_block.size()),_block[i]);
		_treemgr->insert(obj3);
	}
	_treemgr->print(0,1);
}

