#version 330 core
in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = (texture(texture1, TexCoords) * ParticleColor);
}
