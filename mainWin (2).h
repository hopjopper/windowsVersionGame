#define true 1
#define false 0
#define WIDTH 480
#define HEIGHT 480

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/wglew.h>

//global variables holding rendering context and device context
//which initialization functions manipulate as well as main program
//must be available to main program and init functions
HDC hDC;
HGLRC hRC;
HWND hWndMain;
int numberCounter;
int running;



