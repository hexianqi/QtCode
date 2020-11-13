#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform vec3 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r);
    FragColor = vec4(color, 1.0) * sampled;
}
