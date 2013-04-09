#ifndef PDPA1_H
#define PDPA1_H
#include <stdio.h>
#include <string.h>

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<queue>
#include <algorithm>    
#include"bstree.h"
#include"bstreeMgr.h"
#include"node.h"
using namespace std;


class PDPA1{
public:
	PDPA1(){
		_outline=new unsigned[2];
	}
	~PDPA1(){
		delete _outline;
	}
	vector<string> parse_line(string line);
	bool parser(char *block_file_name,char* net_file_name);	
	bool parse_block(ifstream& block_file);
	bool parse_net(ifstream& net_file);
	bool store_line(ifstream& myfile,queue<string>& q,size_t s,vector<string>& vstr2);
	//bool store_line(ifstream& myfile,queue<string>& q,size_t s);
	string get_queue_front(queue<string>& q);
	void parser_debug(bool b=1,bool t=1,bool n=1);
	template <class T> size_t vector_find(vector<T*>& v,string e );//TODO
	void sort_block();//TODO
	void build_tree();
	void tree_debug();
	void simu_anneal();
	void draw_block(char* filename);
private:
	unsigned* _outline;
	vector<Block*> _block;
	vector<Terminal*> _terminal;
	vector<Net*> _net;
	BSTreeMgr _treemgr;
};



#endif
