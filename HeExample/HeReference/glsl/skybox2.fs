#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform samplerCube texture1;

void main()
{
    vec3 envColor = texture(texture1, WorldPos).rgb;

    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));

    FragColor = vec4(envColor, 1.0);
}
