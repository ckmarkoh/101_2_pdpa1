#include "pdpa1.h"
#include "bstreeMgr.h"
#include "rnGen.h"
#include<iostream>
#include <math.h>
#include<iomanip>
#define E 2.71828182845

#define R 0.99
#define T 1000
#define FROZEN 100

/*R5*/
//#define R 0.999
//#define T 100
//#define FROZEN 10


/*R9*/
//#define R 0.99
//#define T 1000
//#define FROZEN 30

unsigned sa_total_time=0;
//#define R 0.9999
using namespace std;
void PDPA1::tree_debug(const char* filename){
	cout<<"cost:"<<_treemgr.getCost()<<endl;
	_treemgr.print(0,1,filename);
}

unsigned Block::B_Range_x=10;
unsigned Block::B_Range_y=10;
float Block::B_Alpha=0;

void PDPA1::test_tree_nrestsore(){
		cout<<"tree1"<<endl;
		tree_debug("tree1.out");
//		draw_block("tree1.raw");
		_treemgr.getCost();
		_treemgr.optimize_backup();//container_backup
		for(size_t i=0;i<10000;i++){
			_treemgr.test_random_disturb();
		}
//		_treemgr.getCost();
		cout<<"tree2"<<endl;
		tree_debug("tree2.out");
//		draw_block("tree2.raw");
		_treemgr.optimize_restore();
		cout<<"tree3"<<endl;
		tree_debug("tree3.out");
//		draw_block("tree3.raw");
//		_treemgr.printCost(1);
	//	_treemgr.test_block_area();
}


void PDPA1::build_tree(){

	Block::B_Range_x=_outline[0];
	Block::B_Range_y=_outline[1];
	
	float min_block_cost=0;
	float min_net_cost=0;
	float min_pos_cost=0;
	assert(_block.size()>=3);
	for(size_t i=0; i<_block.size();i++){
		min_block_cost+=float(_block[i]->area());
	}
	/*_treemgr.insert(float(_block.size())*0.5,_block[0]);
	_treemgr.insert(float(_block.size())*0.20,_block[1]);
	_treemgr.insert(float(_block.size())*0.80,_block[2]);*/
	for(size_t i=0;i<_block.size();i++){
		//_treemgr.insert(float(_block.size()),_block[i],1);
		while(!_treemgr.insert(_block.size(),_block[i],1));
	}
	min_net_cost=sqrt(min_block_cost)*float(_net.size());
//	cout<<"min_block_cost:"<<min_block_cost<<endl;
//	cout<<"min_net_cost:"<<min_net_cost<<endl;
	min_pos_cost=(_outline[0]+_outline[1])*0.5*_net.size();
	_treemgr.setMinCost(min_block_cost,min_net_cost,min_pos_cost);
	_treemgr.get_block_cost();
	_treemgr.setNetVec(_net);
}


void PDPA1::simu_anneal(){
	float r=R;
	float t=T;
	float frozen=FROZEN;
	int i=0;
	_myusage.reset();

//	_treemgr.printCost();
	while(!simu_anneal_sub(r,t,frozen)){
		r=sqrt(r);
		t*=0.1;
		frozen*=0.1;
		int val =i++;
//		cout<<"val: "<<val<<endl;
		if(unsigned(i)%7==0){
			r=R;
			t=T;
			frozen=FROZEN;
			RandomNumGen::change_seed();
		}
		if(unsigned(i)%21==0){
//			cout<<"shuffle"<<endl;
			for(size_t i=0;i<_block.size()*20;i++){
				_treemgr.test_random_disturb();
			}
		}	
		string imgstate=_imgname+"_"+string_to_int(val)+".raw";
		//draw_block(imgstate.c_str());
		if(i>2100){
//			cout<<"timeout"<<endl;
			cerr<<"timeout"<<endl;
			break;
		}
	}
	
/*	cout<<sa_total_time<<endl;*/
//	cout<<"overall times:"<<sa_total_time<<endl;
/*	
	float r=R1;
	float t=T1;
	float frozen=FROZEN1;
	float i=0;
	while(!simu_anneal_sub(r,t,frozen)){
		t*=0.03;
		frozen*=0.03;
		r=sqrt(r);
		float val =i++;
		stringstream ss (stringstream::in | stringstream::out);
		ss << val;
		string test = ss.str();
		string imgstate=_imgname+"_"+string(test)+".raw";
		draw_block(imgstate.c_str());
	}*/
}
bool PDPA1::simu_anneal_sub(float r,float t,float frozen){
//	cout<<"**********************start sa:************************8"<<endl;
//	cout<<"R:"<<r<<endl;
//	cout<<"T:"<<t<<endl;
//	cout<<"FROZEN"<<frozen<<endl;
	unsigned times=0;
	bool complete=false;
	unsigned fall_time=0;
	unsigned restore_time=0;
	unsigned climb_time=0;
	float tempture=t;
	while((tempture*=r)>frozen){
		times++;
		float origin_cost=_treemgr.getCost();
//		cout<<"before random_neighbor"<<endl;
		_treemgr.random_neighbor();
//		cout<<"after random_neighbor"<<endl;
		float after_cost=_treemgr.getCost();
		if(after_cost==-1){
			complete=true;
	//		cout<<"complete!!!"<<endl;
			break;
		}
		float delta_cost=after_cost-origin_cost;
		if(delta_cost>0){
			if(_treemgr.getRandom( pow(E,(delta_cost/tempture)) ) >= 1.0){
		//		cout<<"  restore"<<endl;
				restore_time++;
				_treemgr.restore_backup();
			}
			else
			{
				climb_time++;
			}
		}
		else{
			fall_time++;
		}
	}
	_treemgr.getCost();
//	cout<<"stage_complete"<<endl;
//	cout<<"times:"<<times<<endl;
//	cout<<"fall_times:"<<fall_time<<endl;
//	cout<<"climb_times:"<<climb_time<<endl;
//	cout<<"restore_times:"<<restore_time<<endl;

//	_treemgr.printCost(1);
	
//	cout<<"========report=========="<<endl;
//	_myusage.report(1,1);
//	cout<<"**********************end sa:************************8"<<endl;
	sa_total_time+=times;
	return complete;
}
void PDPA1::print_result(const char* filename ){
	string fname(filename);
	ofstream fout(fname.c_str());
	vector<float> outv=_treemgr.get_result();
	fout<<setprecision(12)<<	outv[0]<<endl;
	fout<<setprecision(12)<<	outv[1]<<endl;
	fout<<setprecision(12)<<	outv[2]<<endl;
	fout<<setprecision(12)<<	outv[3]<<" "<< outv[4] <<endl;
	fout<< setprecision(12)<<_myusage.getTotalTime()<<endl;
	for(size_t i=0;i<_block.size();i++){
		_block[i]->print_pos(fout);
	}
}
