#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 viewPos;
uniform samplerCube texture1;

void main()
{
    // refract
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - viewPos);
    vec3 R = refract(I, normalize(Normal), ratio);
    FragColor = vec4(texture(texture1, R).rgb, 1.0);

//    // reflect
//    vec3 I = normalize(Position - viewPos);
//    vec3 R = reflect(I, normalize(Normal));
//    FragColor = vec4(texture(texture1, R).rgb, 1.0);
}
