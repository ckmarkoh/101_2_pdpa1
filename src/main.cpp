#include "pdpa1.h"

using namespace std;
int main (int argc, char *argv[]){
	PDPA1* pdpa1= new PDPA1();
	string imgname="file";
	if(argc>=5){
		imgname=string(argv[4]);
	}
	pdpa1->setImgName(imgname);
	string imgin=imgname+"_in.raw";
	string imgout=imgname+"_out.raw";
	if( pdpa1->parser(argv[2],argv[3]) ){
		//pdpa1->parser_debug(1,0,0);
		pdpa1->sort_block();
	//	pdpa1->parser_debug(1,0,0);	
		pdpa1->build_tree();
//		cout<<"parser_debug"<<endl;
//		pdpa1->parser_debug(1,1,1);

		#ifdef TEST_PARSER
		pdpa1->draw_block(imgin.c_str() );
		#endif
		
		#ifdef SIMU_ANNEAL 
		pdpa1->draw_block(imgin.c_str() );
//		pdpa1->tree_debug();
		pdpa1->simu_anneal();
//		pdpa1->tree_debug();
		pdpa1->draw_block(imgout.c_str() );
		#endif

		#ifdef TEST_NRESTORE
		pdpa1->test_tree_nrestsore();
		#endif
	}
}
