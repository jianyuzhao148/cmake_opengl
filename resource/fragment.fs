#version 330 core
out vec4 fragcolor;
in vec3 ourcolor;
void main()
{
    fragcolor = vec4(ourcolor, 1.0f);
}