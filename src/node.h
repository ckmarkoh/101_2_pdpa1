#ifndef NODE_H
#define NODE_H
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
	Block(string n,unsigned w, unsigned h):Terminal(n,0,0),_w(w),_h(h){}
	void print(){
		cout<<"n:"<<_name <<" _w:"<<_w<<" _h:"<< _h<<endl;
	}
	void rotate(){
		unsigned temp=_w;
		_w=_h;
		_h=temp;
	}
	unsigned area(){
		return _w*_h;
	}
/*	void print(){
		//cout<<"n:"<<_name <<" _x:"<<_x<<" _y:"<< _y<<" _h"<<h<<"_w"<<w<<endl;
		cout<<"n:"<<_name <<" _x:"<<_x<<" _y:"<<_y<<endl;//<< _y<<" _h"<<h<<"_w"<<w<<endl;
	}*/
private:
	unsigned _w;
	unsigned _h;
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
#endif
