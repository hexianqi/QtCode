#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;
uniform int processing;

void main()
{
    if (processing == 1)        // Inversion
    {
        FragColor = vec4(vec3(1.0 - texture(texture1, TexCoords)), 1.0);
    }
    else if (processing == 2)   // Grayscale
    {
        FragColor = texture(texture1, TexCoords);
        float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
        FragColor = vec4(average, average, average, 1.0);
    }
    else if (processing == 3)   // Weighted
    {
        FragColor = texture(texture1, TexCoords);
        float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
        FragColor = vec4(average, average, average, 1.0);
    }
    else if (processing == 4)   // Kernel
    {
        const float offset = 1.0 / 300.0;
        vec2 offsets[9] = vec2[](
            vec2(-offset,  offset), // 左上
            vec2( 0.0f,    offset), // 正上
            vec2( offset,  offset), // 右上
            vec2(-offset,  0.0f),   // 左
            vec2( 0.0f,    0.0f),   // 中
            vec2( offset,  0.0f),   // 右
            vec2(-offset, -offset), // 左下
            vec2( 0.0f,   -offset), // 正下
            vec2( offset, -offset)  // 右下
        );
    //    // Sharpen
    //    float kernel[9] = float[](
    //        -1, -1, -1,
    //        -1,  9, -1,
    //        -1, -1, -1);
    //    // Blur
    //    float kernel[9] = float[](
    //        1.0 / 16, 2.0 / 16, 1.0 / 16,
    //        2.0 / 16, 4.0 / 16, 2.0 / 16,
    //        1.0 / 16, 2.0 / 16, 1.0 / 1);
        // Edge-detection
        float kernel[9] = float[](
                1, 1, 1,
                1,-8, 1,
                1, 1, 1);
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++)
            col += vec3(texture(texture1, TexCoords.st + offsets[i])) * kernel[i];
        FragColor = vec4(col, 1.0);
    }
    else
    {
        FragColor = texture(texture1, TexCoords);
    }
}

