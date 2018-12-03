#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 pos;

//uniform startX;
//uniform startY;
//uniform cubeSize;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}