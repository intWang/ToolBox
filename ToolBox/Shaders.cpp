#include "Shaders.h"


const char* shaders::passThroughVertSrc =
"attribute highp vec4 position;\n"
"attribute mediump vec4 texturepos;\n"
"uniform mediump mat4 matrix;\n"
"uniform mediump vec4 texturesize;\n"
"varying mediump vec4 coord;\n"
"varying mediump vec4 size;\n"
"void main(void)\n"
"{\n"
"   gl_Position = matrix * position;\n"
"   coord = texturepos;\n"
"   size = texturesize;\n"
"}\n";

const char* shaders::passThroughFragSrc =
"uniform sampler2D texture;\n"
"varying mediump vec4 coord;\n"
"varying mediump vec4 size;\n"
"void main(void)\n"
"{\n"
"   gl_FragColor = texture2D(texture, coord.st);\n"
"}\n";

const char* shaders::bgr2rgbFragSrc =
"uniform sampler2D texture;\n"
"varying mediump vec4 coord;\n"
"varying mediump vec4 size;\n"
"void main(void)\n"
"{\n"
"   gl_FragColor.r = texture2D(texture, coord.st).b;\n"
"   gl_FragColor.g = texture2D(texture, coord.st).g;\n"
"   gl_FragColor.b = texture2D(texture, coord.st).r;\n"
"   gl_FragColor.a = 1.0; \n"
"}\n";

const char* shaders::yuv2rgbFragSrc =
"uniform sampler2D ytexture;\n"
"uniform sampler2D utexture;\n"
"uniform sampler2D vtexture;\n"
"varying mediump vec4 coord;\n"
"varying mediump vec4 size;\n"
"void main(void)\n"
"{\n"
"   mediump float color_y = 1.1643 * (texture2D(ytexture, coord.st).x - 0.0625); \n"
"   mediump float color_u = texture2D(utexture, coord.st).x - 0.5; \n"
"   mediump float color_v = texture2D(vtexture, coord.st).x - 0.5; \n"
"   \n"
"   gl_FragColor.x = color_y + 1.5958 * color_v; \n"
"   gl_FragColor.y = color_y - 0.39173 * color_u - 0.81290 * color_v; \n"
"   gl_FragColor.z = color_y + 2.017 * color_u; \n"
"   gl_FragColor.w = 1.0; \n"
"}\n";

const char* shaders::yuy2rgbFragSrc =
"uniform sampler2D ytexture;\n"
"uniform sampler2D uvtexture;\n"
"varying mediump vec4 coord;\n"
"varying mediump vec4 size;\n"
"void main(void)\n"
"{\n"
"   mediump float color_y = 1.1643 * (texture2D(ytexture, coord.st).r - 0.0625); \n"
"   mediump float color_u = texture2D(uvtexture, coord.st).g - 0.5; \n"
"   mediump float color_v = texture2D(uvtexture, coord.st).a - 0.5; \n"
"   gl_FragColor.x = color_y + 1.5958 * color_v; \n"
"   gl_FragColor.y = color_y - 0.39173 * color_u - 0.81290 * color_v; \n"
"   gl_FragColor.z = color_y + 2.017 * color_u; \n"
"   gl_FragColor.w = 1.0; \n"
"}\n";
