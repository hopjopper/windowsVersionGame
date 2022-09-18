#include "mainWin.h"
#include "init.h"
#include "shaders.h"
#include "loadData.h"

//make an abstract data type ouf of this for controls
//either in character struct or separate control struct
int value = 0;

//main function, point of entry for windows application 
//must be present in a windows application

//pass argument hInstance to delcare an instnace of application created

//main enetry point for program
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow)
{
   MSG        Msg;  //variable for storing messages retrieved from operating system by using GetMessage/Peekmessage
   WNDCLASS   WndCls;
   numberCounter=0;

   //initialize window class must be initialized no default class 
   initWinClass(&WndCls, hInstance);
   //Register the application must register application to make it available to other controls 
   RegisterClass(&WndCls);
   
   //setup dummy context and initialize glew to get function pointers
   setupDummyContext(hInstance);
   
   //initialize the real window and setup some context state settings i.e glViewport
   initGL(hInstance);
   
   //same basic data(triangle) loading to server side(graphics memory)
   loadTri();

   //creating shaders and uploading to server side i.e grahics card
   createShaders();
   
   //setting graphics context settings
   glUseProgram(program);
   glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
   
   printf("FIRST FIRST FIRST\n");
   running = 1;
   
   while (true)
   { 
       //printf("in loop\n");
      while (PeekMessage (&Msg, NULL, 0, 0, PM_REMOVE) > 0) //Or use an if statement
      {
          //translates a virtual key message to a character message
          //TranslateMessage (&Msg);
          //Msg.message == WM_QUIT
         
          if(running == 1)
             DispatchMessage (&Msg);
          else   
             break;
      }

      //what causes the loop to end and window to get destroyed
      if(running == 0){
         printf("at msg quit\n"); 
         break;
      }
      else
        // printf("Not equal\n");

    
         

     //Here is were all the "animation thats occurs when user does nothing" code will go.
      
     //default GL_CODE for swapping buffers to draw-redraw animation
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
      SwapBuffers(hDC);
      
   }

   
   
   //printf("wParam is %u\n", Msg.wParam);
   return Msg.wParam;
}


//two ways a message is dispatched 
//one is if message is sent by message dispatch 
//and two is if certain interactions with window or function calls are made (which send window messages to window procedure) 

//callback function deals with message queue
//sets state of game dealing with inputs and messages sent to the window
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg ,WPARAM wParam, LPARAM lParam)
{
   //printf("the message %d memory address is %x\n", Msg, hWnd);   
   //printf("in wnd procedure function\n");
   numberCounter++; 
   printf("in winprocedure %d and the message is %d\n", numberCounter, Msg);

   switch(Msg)
   {
    //this is the favourite message you can use to perform any early processing that you want to make 
    //sure happens before most things show up you can use this message to initialize anything in your application
    //The window procedure of the new window receives this message after the window is created, 
    //but before the window becomes visible.
    //will only run once on creation
    case WM_CREATE:
       printf("in WM_CREATE\n");
          
    break;

    case WM_CLOSE:
       printf("inside WM_CLOSE\n");
       SendMessage(hWndMain, WM_DESTROY,0,0);
       //PostQuitMessage(0);
    break;
    
    //minimum application needs to deal with: 
    //wm_destroy message to close window and default case for non registered default messaging processing
    //otherwise hanging or not reaching event queue  

    case WM_DESTROY: //Sent when a window is being destroyed. 
       printf("inside WM_DESTROY\n");
    //It is sent to the window procedure of the window being destroyed after the window is removed from the screen.
    //you can use this message to deconstruct the window once the user requests to destroy the window
       
       
       //printf("in wnd prcd %x\n", hWnd);
       //condition set here make sure which window sent the close message
       //make it terminate the main loop by closing of the correct window 
       //or make it terminate main loop by being any window other then the 
       //dummy window by keeping a copy of its pointer
       if(hWndMain==hWnd){
          wglMakeCurrent(hDC,NULL);	//deselect rendering context
          wglDeleteContext(hRC);		//delete rendering context
          //PostQuitMessage(0);
          running = 0;

       }
       else{
           //printf("not equal\n");
       }
       //The PostQuitMessage function posts a WM_QUIT message to the thread's message queue and returns immediately
       //send wm_quit message

       //Indicates a request to terminate an application, and is generated when the application calls the PostQuitMessage function. 
       //This message causes the GetMessage function to return zero.
       //printf("Window destroyed goodbye...bye\n");
    break;

    case WM_QUIT:
       printf("inside WM_QUIT\n");
    break;

    case WM_KEYDOWN:

       switch(wParam){

           

          case VK_UP:
             if(!(lParam & 0x40000000)) //check if the bit for repeat button is not active
             {
                //initial 0;   
                printf("up was pressed\n");
                value = 0;  
             }
             else{
                 value++;
                 printf("value is %d\n", value);
             }
             
          break;

          case VK_LEFT:
             if(!(lParam & 0x40000000))
             {
                printf("left was pressed\n");
             }
             
          break;

          case VK_RIGHT:
             if(!(lParam & 0x40000000))
             {
                printf("right was pressed\n");
             }
             
          break;

          case VK_DOWN:
             if(!(lParam & 0x40000000))
             {
                printf("down was pressed\n");
             }
             
          break; 

       }

    break;

    case WM_KEYUP:

       switch(wParam){

          case VK_UP:
             {
                printf("up released\n");
                value = 0;
             }
          break;

          case VK_LEFT:
             printf("left released\n");
          break;

          case VK_RIGHT:
             printf("right released\n");
          break;

          case VK_DOWN:
             printf("down released\n");
          break;

          case VK_ESCAPE: case 'q': case 'Q':
             SendMessage(hWndMain, WM_DESTROY,0,0);
          break;   

       }

    

    //this must exist to process left over messages or the application will hang or will not go forward through the 
    //event queue and the while loop will 
    default:
       printf("in default processes\n");
        // Process the left-over messages and messages that are not dealt with
       return DefWindowProc(hWnd, Msg, wParam, lParam);
    break;
    }
    // If something was not done, let it go
    return 0;
}


