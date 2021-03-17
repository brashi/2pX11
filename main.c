#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

//X11 libs.
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "2p11.h"

#define d_side 285

void close_x(Display *dis, Window win, GC gc)
{
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(0);				
}

void redraw(Display *dis, Window win, GC gc, short* mat)
{
    XClearWindow(dis, win);
    char str[4];
    XDrawString(dis, win, gc, 10, 9, "Press Esc to quit", 17);
    for(int i = 10, x = 0; i < 265; i += 67, x++) {
        for(int j = 10, y = 0; j < 275; j += 67, y++) {
            XDrawRectangle(dis, win, gc, i, j, 64, 64);
            //printf("x: %d\ny: %d\n", x, y);
            printf("%d ", *(mat + x*4 + y));
            sprintf(str, "%d", *(mat + x*4 + y));
            XDrawString(dis, win, gc, 32 + (j), 32 + (i), str, strlen(str));
        }
        printf("\n");
    }
    
}

void keyhandler(XKeyEvent *e, Display *dis, Window win, GC gc, short* mat)
{
    char buff[32];
    size_t len;
    KeySym ksym;

    ksym = XLookupKeysym(e, 0);
    //XLookupString(e, buff, sizeof buff, &ksym, NULL);
    //printf("%s", buff);
    switch (tolower(ksym))
    {
        case XK_Escape:
            printf("Programa Fechado");
            close_x(dis, win, gc);
            /* code */
            break;
        
        case XK_Left:
            printf("move left");
            move(mat, 'L');
            redraw(dis, win, gc, mat);
            fflush(stdout);
            break;

        case XK_Right:
            printf("move right");
            move(mat, 'R');
            redraw(dis, win, gc, mat);
            fflush(stdout);
            break;

        case XK_Up:
            printf("move up");
            move(mat, 'U');
            redraw(dis, win, gc, mat);
            fflush(stdout);
            break;

        case XK_Down:
            printf("move down");
            move(mat, 'D');
            redraw(dis, win, gc, mat);
            fflush(stdout);
            break;

        default:
            break;
    }
}

void main()
{
    Display *dis = XOpenDisplay(None);
    int screen = DefaultScreen(dis);
    XSetWindowAttributes watt;
    watt.background_pixel = WhitePixel(dis, screen);
    watt.background_pixmap = ParentRelative;

    
    int x = 800;
    int y = 450;
    Window win = XCreateWindow(dis, RootWindow(dis, screen), x, y, d_side, d_side, 3,
                                DefaultDepth(dis, screen), InputOutput,
                                DefaultVisual(dis, screen), 
                                None, &watt);

    XSetWindowBackground(dis, win, WhitePixel(dis, screen));
    XClassHint *w_class = XAllocClassHint();
    w_class->res_class = "no-tile";
    w_class->res_name = "no-tile";
    XSetClassHint(dis, win, w_class);

    short *mat = m_init();

    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
    XMapWindow(dis, win);
    GC gc = XCreateGC(dis, win, 0, 0);
    redraw(dis, win, gc, mat);
    XFlush(dis);


    XEvent e;
    while(1)
    {
        XNextEvent(dis, &e);

        switch(e.type)
        {
            case Expose:
                if(e.xexpose.count == 0)
                    redraw(dis, win, gc, mat);
                break;
            case KeyPress:
                keyhandler(&e.xkey, dis, win, gc, mat);
                //XFlush(dis);
                break;
            default:
                break;
        }

    }

}