#include "pdpa1.h"
#include<iostream>
using namespace std;




void PDPA1::draw_block(const char * filename){

	string fname(filename);
	ofstream fout(fname.c_str());


	fout<<"Vertices"<<endl;
	fout<<_block.size()*4+8<<endl;
	for(size_t i=0;i<_block.size();i++){
		Block* b=_block[i];
		fout<<b->getX()			<<" "	<<b->getY()			<<" 1"<<endl;
		fout<<b->getX()+b->getW()<<" "	<<b->getY()			<<" 1"<<endl;
		fout<<b->getX()			<<" "	<<b->getY()+b->getH()<<" 1"<<endl;
		fout<<b->getX()+b->getW()<<" "	<<b->getY()+b->getH()<<" 1"<<endl;
	}
		fout<<"0"			<<" 0"					<<" 1"<<endl;//0
		fout<<_outline[0]/2	<<" 0"					<<" 1"<<endl;//1
		fout<<_outline[0]	<<" 0"					<<" 1"<<endl;//2
		fout<<"0"			<<" "<<_outline[1]/2	<<" 1"<<endl;//3
		fout<<"0"			<<" "<<_outline[1]		<<" 1"<<endl;//4
		fout<<_outline[0]/2	<<" "<<_outline[1]		<<" 1"<<endl;//5
		fout<<_outline[0]	<<" "<<_outline[1]/2	<<" 1"<<endl;//6
		fout<<_outline[0]	<<" "<<_outline[1]		<<" 1"<<endl;//7
	fout<<"Triangle_list"<<endl;
	fout<<_block.size()*3+4<<endl;
	for(size_t i=0;i<_block.size();i++){
		fout<<4*i	<<" "	<<4*i+1	<<"	"<<	4*i+3	<<endl;
		fout<<4*i	<<" "	<<4*i+2	<<"	"<<	4*i+3	<<endl;
		fout<<4*i	<<" "	<<4*i+1	<<"	"<<	4*i+2	<<endl;
	}
	unsigned outidx=_block.size()*4;
		fout<<outidx	<<" "<<outidx+1	<<" "<<outidx+2	<<endl;
		fout<<outidx	<<" "<<outidx+3	<<" "<<outidx+4	<<endl;
		fout<<outidx+4	<<" "<<outidx+5	<<" "<<outidx+7	<<endl;
		fout<<outidx+2	<<" "<<outidx+6	<<" "<<outidx+7	<<endl;
fout.close();   // 關閉檔案

}





