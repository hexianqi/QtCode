#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube texture1;

void main()
{
    FragColor = texture(texture1, TexCoords);
    //FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
