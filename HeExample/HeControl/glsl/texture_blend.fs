#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (70% texture1, 30% texture2)
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);
//    // 第2张材质翻转
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
