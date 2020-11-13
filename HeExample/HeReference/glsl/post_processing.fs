#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform vec2  offsets[9];
uniform int   edge_kernel[9];
uniform float blur_kernel[9];
uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main()
{
    // zero out memory since an out variable is initialized with undefined values by default
    vec4 result = vec4(0.0f);

    vec3 sample[9];
    // sample from texture offsets if using convolution matrix
    if(chaos || shake)
        for(int i = 0; i < 9; i++)
            sample[i] = vec3(texture(texture1, TexCoords.st + offsets[i]));

    // process effects
    if(chaos)
    {
        for(int i = 0; i < 9; i++)
            result += vec4(sample[i] * edge_kernel[i], 0.0f);
        result.a = 1.0f;
    }
    else if(confuse)
    {
        result = vec4(1.0 - texture(texture1, TexCoords).rgb, 1.0);
    }
    else if(shake)
    {
        for(int i = 0; i < 9; i++)
            result += vec4(sample[i] * blur_kernel[i], 0.0f);
        result.a = 1.0f;
    }
    else
    {
        result =  texture(texture1, TexCoords);
    }
    FragColor = result;
}
