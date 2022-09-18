#include <windows.h>
#include <GL/glew.h>
#include "init.h"
#include "mainWin.h"
LPCTSTR ClsName = "OpenGL App";
LPCTSTR WndName = "My Game";

void initWinClass(PWNDCLASS WndCls, HINSTANCE hInstance){

   // Create the application window
   //WndCls.cbSize        = sizeof(WNDCLASSEX); wndclassex
   WndCls->style         = CS_HREDRAW | CS_VREDRAW |CS_OWNDC;  
   //the style member variable specifies the primary operations applied on the window class
   //if user moves or changes its size, you would need the window redrawn to get its characteristics 
   //CS_HREDRAW CS_VREDRAW draw the window vertically and horizontally  
   WndCls->lpfnWndProc   = WndProcedure;
   WndCls->cbClsExtra    = 0;
   WndCls->cbWndExtra    = 0;
   WndCls->hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   WndCls->hCursor       = LoadCursor(NULL, IDC_ARROW);
   WndCls->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //cast to HBRUSH 
   WndCls->lpszMenuName  = NULL;
   WndCls->lpszClassName = ClsName;
   WndCls->hInstance     = hInstance;
   //WndCls.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); wndclassex

}

void setupDummyContext(HINSTANCE hInstance){

   HWND hWndF = CreateWindow(ClsName, "FAKE" ,WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                       0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

   //printf("in setup dummy context %x\n", hWndF);
   //create a dummy context
   HDC hDC = GetDC(hWndF);	
   //get the device context for window
   //An application can only set the pixel format of a window one time. 
   //note that the pixel format can be set only once for a window, 
   //so if you decide to change it, you must destroy and re-create the window using createWindow function
   //Once a window's pixel format is set, it cannot be changed
   setupPixelFormat(hDC); //call our pixel format setup function

   //in order to use ARB context creation you create a dummy rendering context
   HGLRC tempContext = wglCreateContext(hDC);
   wglMakeCurrent(hDC, tempContext);

   //only once a dummy context has been created can you load function pointers
   initGlew();

   wglMakeCurrent(NULL,NULL);
   wglDeleteContext(tempContext);
   DestroyWindow(hWndF);

}

void setupPixelFormat(HDC hDC){

   PIXELFORMATDESCRIPTOR pfd;

   memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)); 
   pfd.nSize= sizeof(PIXELFORMATDESCRIPTOR); 
   pfd.nVersion   = 1; 
   pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW; 
   pfd.iPixelType = PFD_TYPE_RGBA; 
   pfd.cColorBits = 32; 
   pfd.cDepthBits = 32; 
   pfd.iLayerType = PFD_MAIN_PLANE;

   int nPixelFormat;

   /*      Choose best matching format*/
   nPixelFormat = ChoosePixelFormat(hDC, &pfd);

   if (nPixelFormat == 0) printf("Error in choose pixel format\n");

   /*      Set the pixel format to the device context of the window which cannot be changed afterwards*/
   BOOL bResult = SetPixelFormat(hDC, nPixelFormat, &pfd);

   if (!bResult) printf("Error in set pixel format\n");


}

//uses extension function which require a opengl context to be present either default or dummy
void setupPixelFormatARB(){
   
   PIXELFORMATDESCRIPTOR pfd;

   //framebuffer pixel format attribs
   const int attribList[] =
   {
     WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
     WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
     WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
     WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
     WGL_COLOR_BITS_ARB, 32,
     WGL_DEPTH_BITS_ARB, 24,
     WGL_STENCIL_BITS_ARB, 8,
     0,        //End
   };

   //context attribs
   int attribs[] =
   {
     WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
     WGL_CONTEXT_MINOR_VERSION_ARB, 3,
     WGL_CONTEXT_PROFILE_MASK_ARB,
     WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
     //WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
     0
   };

   int pixelFormat;
   UINT numFormats;

   wglChoosePixelFormatARB(hDC, attribList, NULL, 1, &pixelFormat, &numFormats);
   SetPixelFormat(hDC, pixelFormat, &pfd); //redundant pfd no use here but must be present

   hRC = wglCreateContextAttribsARB(hDC, 0, attribs); 
}
void initGlew(){

   //set experimental value to true so that all functions can be used
   glewExperimental = GL_TRUE;
   
   //initialize glew and get result , check result is not a failure 
   GLenum err = glewInit();
       if(err!=GLEW_OK){
          printf("glew failed!!!....");     
       }

   printf("Glew version is %s\n", glewGetString(GLEW_VERSION));  

   
   
   //glClearColor(0,0,0,0); default

}

void initGL(HINSTANCE hInstance){

   //adjust the screen to the required size accounting for including borders/styles 
   RECT r = {0,0,WIDTH,HEIGHT};
   DWORD dwstyle = WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
   AdjustWindowRect(&r, dwstyle, false );

   printf("width needed for %d client area is %ld ,height needed for %d client area is %ld\n",WIDTH, r.right-r.left, HEIGHT,r.bottom-r.top );

   //to create windowless and borderless set style (third option) to WS_BORDER and then use SetWindowLong(hWndMain, GWL_STYLE, 0); //remove all window styles, check MSDN for details
   hWndMain = CreateWindow(ClsName, WndName ,dwstyle/*(WS_BORDER )*/,
                       600, 200, r.right-r.left, r.bottom-r.top, NULL, NULL, hInstance, NULL);

   //SetWindowLong(hWndMain, GWL_STYLE, 0); //remove all window styles, check MSDN for details                    
   
   //printf("in initGL now %x\n", hWndMain);                    
   // Display the window to the user
   ShowWindow(hWndMain, SW_SHOW);
   //??? not sure yet its use not compulsory
   UpdateWindow(hWndMain);

   hDC = GetDC(hWndMain);

   setupPixelFormatARB();

   // If everything went OK
   if(hRC) wglMakeCurrent(hDC, hRC);
   else printf("did not complete\n");

   //printf("client size of window is width %ld and height %ld\n",r.right - r.left, r.bottom - r.top);

   printf("OpenGL version string is %s\n", glGetString(GL_VERSION));

   GLint OpenGLVersion[3];
   
   glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
   glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

   
   printf("GL Major version %d\nGL Minor Version %d\n", OpenGLVersion[0], OpenGLVersion[1]);
   printf("GLSL version is %s \nVendor of OpenGL is %s \nRenderer version is %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION), 
                                                                                    glGetString(GL_VENDOR) ,glGetString(GL_RENDERER));
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glViewport(0,0,WIDTH,HEIGHT);                                                                                                                                                   
}