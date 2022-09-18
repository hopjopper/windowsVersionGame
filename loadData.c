//functions to deal with OpenGL

#include <GL/glew.h>

void loadTri(){

   // An array of 3 vectors which represents 3 vertices
   static const GLfloat verticies[] = {
     -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      0.0f,  1.0f, 0.0f,
   };

   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   // This will identify our vertex buffer
   GLuint vbo;
   // Generate 1 buffer, put the resulting identifier in vertexbuffer
   glGenBuffers(1, &vbo);
   // The following commands will talk about our 'vertexbuffer' buffer
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   // Give our vertices to OpenGL.
   glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

   // 1st attribute buffer : vertices
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
   );
   
   //glDisableVertexAttribArray(0);

}