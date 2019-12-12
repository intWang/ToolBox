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
uniform vec4 uniColor;
void main()
{
    fragColor = uniColor;
}
)";

const char* shaders::vertexShader1 = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec4 outColor;
void main()
{
    gl_Position = vec4(-aPos.x, aPos.y, aPos.z, 1.0);
    outColor = vec4(aColor, 1.0);
}

)";


const char* shaders::fragmentShader1 = R"(#version 330 core
out vec4 fragColor;
in vec4 outColor;
void main()
{
    fragColor = outColor;
}
)";


const char* shaders::fragmentShader2 = R"(#version 330 core
out vec4 fragColor;
void main()
{
    fragColor = vec4(0.5f, 0.7f, 0.9f, 1.0f);
}
)";

const char* shaders::vertexShaderT = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec4 outColor;
out vec2 outTexture;
void main()
{
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    outColor = vec4(aColor, 1.0);
    outTexture = aTexture;
}
)";

const char* shaders::fragmentShaderT = R"(#version 330 core
out vec4 fragColor;

in vec4 outColor;
in vec2 outTexture;

uniform sampler2D ourTexture;

void main()
{
    fragColor = mix(texture(ourTexture, outTexture),outColor,0.3);
}
)";
