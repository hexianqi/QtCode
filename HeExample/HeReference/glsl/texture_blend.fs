#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // linearly interpolate between both textures (80% texture1, 20% texture2)
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
//    // 第2张材质翻转
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
