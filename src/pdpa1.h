#ifndef PDPA1_H
#define PDPA1_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>   
#include <sstream>
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
#include"myUsage.h"
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
	void tree_debug(const char* filename=0);
	void simu_anneal();
	bool simu_anneal_sub(float r,float t,float frozen);
	void draw_block(const char* filename);
	void test_tree_nrestsore();
	void set_alpha(float f){
		f= (f>1) ? 1 : f;
		f= (f<0) ? 0 : f;
		Block::B_Alpha=f;
	}
	void setImgName(string s){
		_imgname=s;
	}
	string string_to_int(int val){
		stringstream ss (stringstream::in | stringstream::out);
		ss << val;
		string test = ss.str();
		return test;
	}
	void print_result(const char* filename);
	void draw_window();

	unsigned transfer(unsigned i,unsigned max);



private:

	struct DrawRect {  
	   pair<unsigned,unsigned> p1;  
	   pair<unsigned,unsigned> p2;  
	   pair<unsigned,unsigned> p3; 
	   pair<unsigned,unsigned> p4;
	   string n; 
	};

	string _imgname;
	MyUsage _myusage;
	unsigned* _outline;
	vector<Block*> _block;
	vector<Terminal*> _terminal;
	vector<Net*> _net;
	BSTreeMgr _treemgr;
};



#endif
