#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 pos;

uniform float startX;
uniform float startY;
uniform float cubeSize;

void main()
{
    float lineWidth = cubeSize / 50;
    float x = floor((pos.x - startX) / cubeSize);
    float xLocal = pos.x - (startX + cubeSize * x);
    float y = floor((pos.y - startY) / cubeSize);
    float yLocal = pos.y - (startY + cubeSize * y);

    if (xLocal < lineWidth || yLocal < lineWidth || xLocal > cubeSize - 2 * lineWidth || yLocal > cubeSize - 2 * lineWidth) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(ourColor, 1.0);
    }
}