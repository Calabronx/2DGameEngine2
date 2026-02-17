#version 330 core
out vec4 FragColor;
uniform float uTime;
in vec2 fragPos;

void main()
{
    float slow = uTime * 0.001;
    float r = 0.5 + 0.5 * sin(slow + fragPos.x * 2.0);
    float g = 0.5 + 0.5 * sin(slow + fragPos.y * 2.0 + 2.0);
    float b = 0.5 + 0.5 * sin(slow + (fragPos.x + fragPos.y) * 1.5 + 4.0);

    FragColor = vec4(r, g, b, 1.0);
}
