#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct XInfo {
    Display *dis;
    Window win;
    GC gc;
    int screen;
};

struct XInfo init_x();
void close_x(Display *dis, GC gc, Window win);
void redraw(Display *dis, Window win);


int main(){
    XEvent event;
    char text[255];
    char tstr[16];
    KeySym key;
	time_t clr = time(NULL);

    struct XInfo xinf = init_x();

	while(1) {
        time_t result = time(NULL);
        struct tm *lt = localtime(&result);
        sprintf(tstr, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);
		if(difftime(result, clr) >= 1){
			clr = time(NULL);
			redraw(xinf.dis, xinf.win);
		}
        XDrawString(xinf.dis, xinf.win, xinf.gc, 120, 120, tstr, strlen(tstr));
		if (event.type==Expose && event.xexpose.count==0) {
			redraw(xinf.dis, xinf.win);
		}
		if (event.type==KeyPress && XLookupString(&event.xkey,text,255,&key,0)==1) {
			if (text[0]=='q') {
				close_x(xinf.dis, xinf.gc, xinf.win);
			}
		}
	}
    return 0;
}

struct XInfo init_x() {       
	unsigned long black,white;
    struct XInfo x;
	x.dis=XOpenDisplay((char *)0);
   	x.screen=DefaultScreen(x.dis);
	black=BlackPixel(x.dis, x.screen),
	white=WhitePixel(x.dis, x.screen);
   	x.win=XCreateSimpleWindow(x.dis,DefaultRootWindow(x.dis),0, 0, 300, 300, 5, black, white);
	XSetStandardProperties(x.dis,x.win,"TimeC","TimeC",None,NULL,0,NULL);
	XSelectInput(x.dis, x.win, ExposureMask|KeyPressMask|ButtonPressMask);
    x.gc=XCreateGC(x.dis, x.win, 0,0);
	XSetBackground(x.dis,x.gc,white);
	XSetForeground(x.dis,x.gc,black);
	XClearWindow(x.dis, x.win);
	XMapRaised(x.dis, x.win);
    return x;
};

void close_x(Display *dis, GC gc, Window win) {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

void redraw(Display *dis, Window win) {
	XClearWindow(dis, win);
};