#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0) * texture(texture1, TexCoords);
}
