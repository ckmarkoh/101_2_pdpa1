#ifndef YHEIGHT_H
#define YHEIGHT_H
#include<iostream>
#include<vector>
using namespace std;

class YHeight{
public:

	YHeight(){}
	
	unsigned insert(unsigned start,unsigned end,unsigned height){
		assert(start<end);
		check_array_size(end);	
		unsigned y=find_max(start,end);
		unsigned newy=y+height;
		for(unsigned i=start; i<end;i++){
				_height_list[i]=newy;
		}		
		return y;
	}
	unsigned find_max(unsigned start,unsigned end){
		assert( end<=_height_list.size());
		unsigned max=_height_list[start];
		for(unsigned i=start; i<end;i++){
			if(_height_list[i] > max){
				max=_height_list[i];
			}
		}
		return max;
	}
	void check_array_size(unsigned end){
		while( _height_list.size()<end ){
			_height_list.push_back(0);
		}
	}
	void clear(){
		_height_list.clear();
	}

	void debug(){
		for(unsigned i=0;i<_height_list.size();i++){
		cout<<"i:"<<i<<" height:"<<_height_list[i]<<endl;
		}
	}
	unsigned find_max_x(){
		return _height_list.size();
	}
private:
	vector<unsigned> _height_list;

};



#endif
