// File: "cube.vert"
// Caution: Use UNIX EOL-format
#version 130



in vec4 vPosition;
in vec4 vColor;
out vec4 color;
void main()
{
color = vColor;
gl_Position = vPosition;
}