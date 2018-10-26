#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 ourColor;
uniform vec4 lightColor;
void main()
{
    FragColor = lightColor;
}