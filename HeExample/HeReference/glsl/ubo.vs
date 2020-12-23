#version 330 core

// #version 420 core
// layout(std140, binding = 2) uniform Lights { ... };

layout (location = 0) in vec3 aPos;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
