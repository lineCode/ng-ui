#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 transform;
uniform mat4 model;
void main(){
gl_Position = transform * vec4(aPos, 1.0);
FragPos = vec3(model * vec4(aPos, 1.0));
vertexColor = aColor;
TexCoord = aTexCoord;
Normal = mat3(transpose(inverse(model))) * aNormal;
}