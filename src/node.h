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
	string getName(){
		return _name;	
	}
	void setX(unsigned x){
		_x=x;
	}
	void setY(unsigned y){
		_y=y;
	}
	void setXY(unsigned x,unsigned y){
		_x=x;
		_y=y;
	}
	unsigned getX(){
		return _x;
	}
	unsigned getY(){
		return _y;
	}
	unsigned getPosX(){
		return _x;
	}
	unsigned getPosY(){
		return _y;
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
	unsigned getW(){
		return _w;
	}
	unsigned getH(){
		return _h;
	}
	unsigned getPosX(){
		return _x+(_w/2);
	}
	unsigned getPosY(){
		return _y+(_h/2);
	}
	bool inRange(unsigned x,unsigned y){
		return ( ((_x+_w)<x) && ((_y+_h)<y) ); 
	}
	bool lie_or_stand(){
		return (_w/_h) > 1;
	}
	/*void setW(unsigned w){
		_w=w;
	}
	void setH(unsigned h){
		_h=h;
	}*/
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
			cout<<_tm[i]->getName()<<" ";		
		}
		cout<<endl;
	}
	unsigned getLength(){
		unsigned min_x=_tm[0]->getPosX();
		unsigned min_y=_tm[0]->getPosY();
		unsigned max_x=_tm[0]->getPosX();
		unsigned max_y=_tm[0]->getPosY();
		assert(_tm.size()>1);
		for(size_t i=1;i<_tm.size();i++){
			min_x = ( min_x >_tm[i]->getPosX() ) ? _tm[i]->getPosX()	: min_x	;
			min_y = ( min_y >_tm[i]->getPosY() ) ? _tm[i]->getPosY()	: min_y	;
			max_x = ( max_x <_tm[i]->getPosX() ) ? _tm[i]->getPosX()	: max_x	;
			max_y = ( max_y <_tm[i]->getPosY() ) ? _tm[i]->getPosY()	: max_y	;
		}
		//cout<<"return cost:"<<(max_x-min_x)+(max_y-min_y)<< endl;
		return (max_x-min_x)+(max_y-min_y);
	}
private:
	vector<Terminal*> _tm;
	unsigned _id;	
};
#endif
