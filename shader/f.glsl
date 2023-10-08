#version 330 core
out vec4 FragColor;
in vec2 text;
uniform sampler2D coords;
void main()
{
 FragColor=texture(coords,text);
}