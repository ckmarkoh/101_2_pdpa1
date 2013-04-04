#include "pdpa1.h"


static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}


vector<string> PDPA1::parse_line(string line){
	vector<string> vstr;
	string  whitespace = " \t\r\n\v\f";
	line.erase(line.find_last_not_of(whitespace.c_str()) + 1);
	line.erase(line.find_last_not_of(whitespace.c_str()) + 1);
	char * str=const_cast<char*>(line.c_str());
	char*	pch = strtok (str," \t");
		while (pch != NULL)
		{
			string sstr(pch);
			sstr=trim(sstr);//.erase(sstr.find_last_not_of(whitespace.c_str()) + 1);
		//	sstr.erase(sstr.find_first_of(whitespace.c_str()),sstr.find_last_of(whitespace.c_str()));
			if(sstr.size()>0){
				vstr.push_back(sstr);
		//		cout<<"sstr:"<<sstr<<endl;
			}	
			pch = strtok (NULL, " \t");
		}
	return vstr;
}

bool PDPA1::store_line(ifstream& myfile,queue<string>& q,size_t s,vector<string>& vstr2){
	while(q.size()<s){
		string line;
		getline (myfile,line);
		vector<string> vstr;
	//	cout<<"line:"<<line<<endl;
		if(!myfile.eof()){
			vstr=parse_line(line);
			//cout<<"vstr[0]:"<<vstr[0]<<endl;	
		}
		else{
		//	cout<<"end_of_file"<<endl;
			return true;
		}
		for(size_t i=0;i<vstr.size();i++){
		//	cout<<"i:"<<i<<" vstr[i]"<<vstr[i]<<endl;
			q.push(vstr[i]);
		}
	}
	vstr2.clear();
	for(size_t i=0;i<s;i++){
		vstr2.push_back(get_queue_front(q));
	}
	return false;
}
string PDPA1::get_queue_front(queue<string>& q){
	string vstr=q.front();
	q.pop();
	return vstr;
}


bool PDPA1::parser(char *block_file_name,char* net_file_name){
	ifstream block_file (block_file_name);
	if (block_file.is_open()){
		if(!parse_block(block_file)){
			cout<< "Unable to parse block file"<<endl;
			return false;
		}
	}else{
		cout << "Unable to open block file"<<endl;
		return false;
	}


	ifstream net_file (net_file_name);
	if (net_file.is_open()){
		if(!parse_net(net_file)){
			cout<< "Unable to parse net file"<<endl;
			return false;
		}
	}else{
		cout << "Unable to open net file"<<endl;
		return false;
	}
	return true;

}
bool PDPA1::parse_block(ifstream & block_file){
		string line_in;
		vector<string> line_out;
		queue<string> rqueue;
		int num_block=0;
		int num_terminal=0;
		enum Read_state{
			READ_OUTLINE=0,
			READ_NUM_BLOCK,
			READ_NUM_TERMINAL,
			READ_BLOCK,
			READ_TERMINAL,
		};
		Read_state rstate=READ_OUTLINE;
		while(true){
				switch(rstate){
		//		cout<< "rstate2:" <<rstate<<endl;
				case READ_OUTLINE:{
					if( (!store_line(block_file,rqueue,3,line_out)) && (line_out[0].find("Outline")!=string::npos) ) {
						_outline[0]=atoi(line_out[1].c_str());
						_outline[1]=atoi(line_out[2].c_str());			
						rstate=READ_NUM_BLOCK;
					}
					else{
						return false;
					}
				}break;
				case READ_NUM_BLOCK:{
					if( (!store_line(block_file,rqueue,2,line_out)) &&  (line_out[0] .find("NumBlocks")!=string::npos) ){
						num_block=atoi(line_out[1].c_str() );
						rstate=READ_NUM_TERMINAL;
					}
					else{
						return false;
					}
				}break;
				case READ_NUM_TERMINAL:{
					if( (!store_line(block_file,rqueue,2,line_out)) && (line_out[0].find("NumTerminals")!=string::npos) ){
						num_terminal=atoi(line_out[1].c_str());
						rstate=READ_BLOCK;
					}
					else{
						return false;
					}
				}break;
				case READ_BLOCK:{
	//				cout<< "num_block:"<<num_block<<endl;
					if(--num_block>=0){
						if(store_line(block_file,rqueue,3,line_out)){
							return false;
						}
						Block* b= new Block(line_out[0], atoi(line_out[1].c_str()), atoi(line_out[2].c_str()) );
						//assert(_block.find(line_out[0])==_block.end());
						//_block[line_out[0]]=b;
						assert(vector_find(_block,line_out[0])==_block.size());
						_block.push_back(b);
						//b->print();
					}else{
						rstate=READ_TERMINAL;
					}
				}break;
				case READ_TERMINAL:{
	//				cout<< "num_terminal:"<<num_terminal<<endl;
					if(--num_terminal>=0){
						if(store_line(block_file,rqueue,4,line_out)){
							return false;
						}
						Terminal* t= new Terminal(line_out[0], atoi(line_out[2].c_str()), atoi(line_out[3].c_str()) );
		//				cout<<"line_out[0]:"<<line_out[0]<<endl;
						//assert(_terminal.find(line_out[0])==_terminal.end());
						//_terminal[line_out[0]]=t;
						assert(vector_find(_terminal,line_out[0])==_terminal.size());
						_terminal.push_back(t);
						//t->print();
					}else{
						return true;
						//rstate=READ_TERMINAL;
					}
				}break;
				default:{
					assert(0);
				}break;
			}
		/*	}
			else{
				return true;
			}*/
		}
	return true;
}
bool PDPA1::parse_net(ifstream & net_file){
	string line_in;
	vector<string> line_out;
	queue<string> rqueue;
	int num_net=0;
	int num_degree=0;
	enum Read_state{
		READ_NUM_NET=0,
		READ_NUM_DEGREE,
		READ_NET,
	};
	Net* n=0;
	Read_state rstate=READ_NUM_NET;
	while(true){
		switch(rstate){
			case READ_NUM_NET:{
				if( (!store_line(net_file,rqueue,2,line_out) ) &&  (line_out[0] .find("NumNets")!=string::npos))  {
					num_net=atoi(line_out[1].c_str());
					rstate=READ_NUM_DEGREE;
				}else{
			//		cout<<"f0"<<endl;
					return false;
				}
			}break;
			case READ_NUM_DEGREE:{
				if( (!store_line(net_file,rqueue,2,line_out) ) &&  (line_out[0] .find("NetDegree")!=string::npos))  {
					num_degree=atoi(line_out[1].c_str());
					n=new Net(_net.size());	
					rstate=READ_NET;		
				}else{
				//	cout<<"f1"<<endl;
					return false;
				}
			}break;
			case READ_NET:{
				if(num_net > 0){
					if(--num_degree>=0){
					//	cout<<"num_degree"<<num_degree<<endl;
						if(store_line(net_file,rqueue,1,line_out)){
					//		cout<<"f2"<<endl;
							return false;
						}
						size_t pos=vector_find(_block,line_out[0]);
					//	cout<<"line_out[0]:"<<line_out[0]<<endl;
						if(pos!=_block.size()){
							n->add_terminal(_block[pos]);
						}else{
							pos=vector_find(_terminal,line_out[0]);
							if(pos!=_terminal.size()){
								n->add_terminal(_terminal[pos]);
							}
							else{
								assert(0);
							}
						}
						//n->print();
					}
					else{
						_net.push_back(n);
						if(--num_net>0){
							rstate=READ_NUM_DEGREE;
						}
						else{
							return true;
						}
					}
				}
				else{
					//cout<<"f3"<<endl;
					return true;
				}
			}break;
		}

	}
	return true;
}

void PDPA1::parser_debug(bool b,bool t,bool n){
	if(b){
		cout<<"block_count:"<<_block.size()<<endl;
		for (size_t i=0;i<_block.size();i++){
			_block[i]->print();
		}
	}
	if(t){
		cout<<"terminal_count:"<<_terminal.size()<<endl;
			for (size_t i=0;i<_terminal.size();i++){
			_terminal[i]->print();
		}
	}
	if(n){
		cout<<"net_count:"<<_net.size()<<endl;
		for (size_t i=0;i<_net.size();i++){
			_net[i]->print();
		}
	}
}

template <class T> size_t 
PDPA1::vector_find(vector<T*>& v,string e ){
	for(size_t i=0;i< v.size();i++){
		if(v[i]->get_name()==e){
			return i;	
		}
	}
	return v.size();
}

void PDPA1::sort_block(){
	for(unsigned j=1 ;j<_block.size();j++)
		{
		Block* temp=_block[j];
		int i=j-1;
		while(( i>=0) && (_block[i]->area() > temp->area()))
			{
			_block[i+1]=_block[i];
			i=i-1;
			}
		_block[i+1]= temp;
		}
}

