#include "pdpa1.h"
#define WIDTH 800
#define OFFSET 10
using namespace std;


unsigned PDPA1::transfer(unsigned i,unsigned max){
	return OFFSET+unsigned(WIDTH*(float(i)/float(max))); 
}



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


void PDPA1::draw_window(){

/* first include the standard headers that we're likely to need */
	int screen_num, width, height;
	unsigned long background, border;
	Window win;
	XEvent ev;
	Display *dpy;
	
	/* First connect to the display server */
	dpy = XOpenDisplay(NULL);
	if (!dpy) {fprintf(stderr, "unable to connect to display\n");return;}

	/* these are macros that pull useful data out of the display object */
	/* we use these bits of info enough to want them in their own variables */
	screen_num = DefaultScreen(dpy);
	background = BlackPixel(dpy, screen_num);
	border = WhitePixel(dpy, screen_num);
	//width = 40; /* start with a small window */
	//height = 40;
	width=WIDTH+2*OFFSET;
	height=width;
	
	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), /* display, parent */
		0,0, /* x, y: the window manager will place the window elsewhere */
		width, height, /* width, height */
		2, border, /* border width & colour, unless you have a window manager */
		background); /* background colour */
	
	

	/* tell the display server what kind of events we would like to see */
	XSelectInput(dpy, win, ButtonPressMask|StructureNotifyMask|ExposureMask );

	/* okay, put the window on the screen, please */
	XMapWindow(dpy, win);
	

	unsigned max_val=max(_outline[0],_outline[1]);


	vector<DrawRect> draw_rect;
	
		unsigned ox1=transfer(0,max_val);
		unsigned oy1=transfer(0,max_val);
		unsigned ox2=transfer(_outline[0],max_val);
		unsigned oy2=transfer(_outline[1],max_val);
		pair <unsigned,unsigned> op1=make_pair(ox1,oy1);
		pair <unsigned,unsigned> op2=make_pair(ox1,oy2);
		pair <unsigned,unsigned> op3=make_pair(ox2,oy1);
		pair <unsigned,unsigned> op4=make_pair(ox2,oy2);
		DrawRect r0={op1,op2,op3,op4};
		draw_rect.push_back(r0);

	for(size_t i=0;i<_block.size();i++){
		Block* b=_block[i];
		unsigned x1=transfer(b->getX(),max_val);
		unsigned x2=transfer(b->getX()+b->getW(),max_val);
		unsigned y1=transfer(b->getY(),max_val);
		unsigned y2=transfer(b->getY()+b->getH(),max_val);
		pair <unsigned,unsigned> p1=make_pair(x1,y1);
		pair <unsigned,unsigned> p2=make_pair(x1,y2);
		pair <unsigned,unsigned> p3=make_pair(x2,y1);
		pair <unsigned,unsigned> p4=make_pair(x2,y2);
		DrawRect r1={ p1,p2,p3,p4,b->getName()  };
		draw_rect.push_back(r1);
	}

		
	/* as each event that we asked about occurs, we respond.  In this
	 * case we note if the window's shape changed, and exit if a button
	 * is pressed inside the window.  We also draw lines whenever a part
	 * of a window becomes viewable. */
/*	
	XColor green_col;
	Colormap colormap;
	char green[] = "#AAAAAA";
	XParseColor(dpy, colormap, green, &green_col);
	XAllocColor(dpy, colormap, &green_col);
*/

	/* create the pen to draw lines with */
	GC pen;
	XGCValues values;
	values.foreground = WhitePixel(dpy, screen_num);
	values.line_width = 2;
	values.line_style = LineSolid;
	pen = XCreateGC(dpy, win, GCForeground|GCLineWidth|GCLineStyle,&values);


/* create the pen to draw lines with */
	GC pen2;
	XGCValues values2;
	values.foreground = WhitePixel(dpy, screen_num);
	values2.line_width = 1;
	values2.line_style = LineOnOffDash;
	pen2 = XCreateGC(dpy, win, GCForeground|GCLineWidth|GCLineStyle,&values2);


	while(1){
		XNextEvent(dpy, &ev);
		switch(ev.type){
		case Expose:

			for(size_t i=0; i<draw_rect.size();i++){
				DrawRect r=draw_rect[i];
				unsigned x1=r.p1.first;
				unsigned x2=r.p2.first;
				unsigned x3=r.p3.first;
				unsigned x4=r.p4.first;
				unsigned y1=height-r.p1.second;
				unsigned y2=height-r.p2.second;
				unsigned y3=height-r.p3.second;
				unsigned y4=height-r.p4.second;
				XDrawLine(dpy, win, pen, x1,y1,x2,y2);
				XDrawLine(dpy, win, pen, x1,y1,x3,y3);
				XDrawLine(dpy, win, pen, x2,y2,x4,y4);
				XDrawLine(dpy, win, pen, x3,y3,x4,y4);
				if(i>=1){
				//	unsigned xc=r.pc.first;
				//	unsigned yc=r.pc.second;
					XDrawLine(dpy, win, pen2, x1,y1,x4,y4);
					XDrawLine(dpy, win, pen2, x2,y2,x3,y3);
					XDrawString ( dpy, win, pen, x1+5 , y1-5 , r.n.c_str(), r.n.size() );
				}			
			}
		//	XDrawString ( dpy, win, pen, 200, 200, text.c_str(), text.size() );

		//	XDrawLine(dpy, win, pen, 0, 0, width, height);
		//	XDrawLine(dpy, win, pen, width, 0, 0, height);
		break;
		//case ConfigureNotify:
		//	break;
		//case ButtonPress:
		//	XCloseDisplay(dpy);
		default:
			break;
		}
	}
}
