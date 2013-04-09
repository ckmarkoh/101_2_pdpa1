#include "pdpa1.h"
#include<iostream>
using namespace std;

void PDPA1::draw_block(char * filename){

	string fname(filename);
	ofstream fout(fname.c_str());


	fout<<"Vertices"<<endl;
	fout<<_block.size()*4<<endl;
	for(size_t i=0;i<_block.size();i++){
		Block* b=_block[i];
		fout<<b->getX()			<<" "	<<b->getY()			<<" 1"<<endl;
		fout<<b->getX()+b->getW()<<" "	<<b->getY()			<<" 1"<<endl;
		fout<<b->getX()			<<" "	<<b->getY()+b->getH()<<" 1"<<endl;
		fout<<b->getX()+b->getW()<<" "	<<b->getY()+b->getH()<<" 1"<<endl;
	}
	fout<<"Triangle_list"<<endl;
	fout<<_block.size()*3<<endl;
	for(size_t i=0;i<_block.size();i++){
		fout<<4*i	<<" "	<<4*i+1	<<"	"<<	4*i+3	<<endl;
		fout<<4*i	<<" "	<<4*i+2	<<"	"<<	4*i+3	<<endl;
		fout<<4*i	<<" "	<<4*i+1	<<"	"<<	4*i+2	<<endl;
	}

fout.close();   // 關閉檔案
}





