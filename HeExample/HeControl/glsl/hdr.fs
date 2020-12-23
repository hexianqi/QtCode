#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform bool hdr;
uniform float exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(texture1, TexCoords).rgb;
    vec3 result = hdrColor;
    if (hdr)
    {
//       // reinhard
//       result = hdrColor / (hdrColor + vec3(1.0));
        // exposure
        result = vec3(1.0) - exp(-hdrColor * exposure);
    }
    else
        result = hdrColor;
    // gamma correct while we're at it
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}
