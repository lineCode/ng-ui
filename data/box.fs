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
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * ourColor * lightColor;
}