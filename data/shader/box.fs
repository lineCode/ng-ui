#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 ourColor;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(Normal, lightDir), 0.0);
    vec4 diffuse = diff * lightColor; 


    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec4 specular = specularStrength * spec * lightColor; 

    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * ourColor * (ambient + diffuse + specular);
    //FragColor = ourColor * (ambient + diffuse + specular);
}