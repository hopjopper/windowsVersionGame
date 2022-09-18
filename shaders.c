#include <GL/glew.h>
#include <stdio.h>
#include "shaders.h"

//string concatenation occurs and becomes all one string
char const * vertShad = 
//[VERTEX SHADER]
"#version 330 core\n"
"layout(location = 0)in vec3 pos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(pos, 1.0);\n"
"}\n";

char const * fragShad =
//[FRAGMENT SHADER]
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(1.0, 0.0, 0.0, 0.7);\n"
"}\n"
;

void createShaders(){

   GLuint vertex_shader;
   GLuint fragment_shader;

   vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(vertex_shader, 1, &vertShad, NULL);
   glShaderSource(fragment_shader, 1, &fragShad, NULL);

   glCompileShader(vertex_shader);

   //get compilation results

   GLint success = -1;
   GLint maxLength = 0;

   glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

   if(success==GL_FALSE){
      printf("error in vertex shader\n");
      maxLength = 0;
      glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);
      char infoLog[maxLength]; 
      glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &infoLog[0]);
      printf("%s", infoLog);
   }
   
   success = -1;
   glCompileShader(fragment_shader);

   glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

   if(success==GL_FALSE){
      printf("error in fragment shader\n");
      maxLength = 0;
      glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);
      char infoLog2[maxLength];
      glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &infoLog2[0]);
      printf("%s", infoLog2);
   }
   
   //if(glGetShaderiv(fragment_shader,GL_COMPILE_STATUS)!=GL_TRUE)
   //   printf("error in fragment shader");

   //get compilation results with glGetShaderiv(GL_COMPILE_STATUS) if GL_TRUE returned then successfull compilation
   //If the compilation
   //failed, you can determine what the error was by retrieving the compilation
   //log. glGetShaderInfoLog() will return an implementation-specific set of
   //messages describing the compilation errors. The current size of the error
   //log can be queried by calling glGetShaderiv() with an argument of
   //GL_INFO_LOG_LENGTH

   program = glCreateProgram();

   glAttachShader(program, vertex_shader);
   glAttachShader(program, fragment_shader);
   glLinkProgram(program);

   GLint isLinked = 0;
   glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
   if(isLinked == GL_FALSE){
      printf("did not link\n");   
   }
}