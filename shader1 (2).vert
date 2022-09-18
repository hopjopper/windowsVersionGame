//[VERTEX SHADER]
#version 450 core

in vec3 InVertex;

smooth out vec4 Color;

void main()
{
	gl_Position = vec4(InVertex, 1.0);
}
