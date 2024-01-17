#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 acolor;
out vec3 ourcolor;
uniform mat4 model;
void main()
{
   gl_Position =model * vec4(apos, 1.0);
   ourcolor = acolor;
}