#include "pdpa1.h"

using namespace std;
int main (int argc, char *argv[]){
	PDPA1* pdpa1= new PDPA1();
	if( pdpa1->parser(argv[2],argv[3]) ){
		pdpa1->parser_debug();	
	}
}
