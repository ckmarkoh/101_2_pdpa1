#ifndef PDPA1_H
#define PDPA1_H
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cstdlib>
#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
class Block;
class Terminal;
class Net;

class Terminal{
public:
	Terminal(string n,unsigned x,unsigned y):_name(n),_x(x),_y(y){}

	void add_net(Net* n){
		_nt.push_back(n);
	}
	void print(){
		cout<<"n:"<<_name <<" _x:"<<_x<<" _y:"<< _y<<endl;
	}
	string get_name(){
		return _name;	
	}

protected:
	vector<Net*> _nt; //net
	string _name; //name
	unsigned _x;
	unsigned _y;
};

class Block : public Terminal{
public:
	Block(string n,unsigned h, unsigned w):Terminal(n,h,w){}//,_h(h),_w(w){}

/*	void print(){
		//cout<<"n:"<<_name <<" _x:"<<_x<<" _y:"<< _y<<" _h"<<h<<"_w"<<w<<endl;
		cout<<"n:"<<_name <<" _x:"<<_x<<" _y:"<<_y<<endl;//<< _y<<" _h"<<h<<"_w"<<w<<endl;
	}*/
private:
//	unsigned _h;
//	unsigned _w;
};


class Net{
public:
	Net(unsigned i):_id(i){}
	void add_terminal(Terminal* t){
		t->add_net(this);
		_tm.push_back(t);
	}
	void print(){
		cout<<"net:"<<_tm.size()<<endl;;
		for(size_t i=0;i<_tm.size();i++){
			cout<<_tm[i]->get_name()<<" ";		
		}
		cout<<endl;
	}
private:
	vector<Terminal*> _tm;
	unsigned _id;	
};

class PDPA1{
public:
	PDPA1(){
		_outline=new unsigned[2];
	}
	vector<string> parse_line(string line);
	bool parser(char *block_file_name,char* net_file_name);	
	bool parse_block(ifstream& block_file);
	bool parse_net(ifstream& net_file);
	bool store_line(ifstream& myfile,queue<string>& q,size_t s,vector<string>& vstr2);
	//bool store_line(ifstream& myfile,queue<string>& q,size_t s);
	string get_queue_front(queue<string>& q);
	void parser_debug();
private:
	unsigned* _outline;
	map<string,Block*> _block;
	map<string,Terminal*> _terminal;

	vector<Net*> _net;

};





#endif
