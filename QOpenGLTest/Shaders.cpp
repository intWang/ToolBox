#include "Shaders.h"


const char* shaders::vertexShader = R"(#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";




const char* shaders::fragmentShader = R"(#version 330 core
out vec4 fragColor;
void main()
{
    fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)";
