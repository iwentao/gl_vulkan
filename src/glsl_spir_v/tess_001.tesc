#version 450 core
layout (vertices = 1) out;

void main(void)
{
    gl_TessLevelInner[0] = 7.0f;
    gl_TessLevelInner[1] = 8.0f;

    gl_TessLevelOuter[0] = 3.0f;
    gl_TessLevelOuter[0] = 4.0f;
    gl_TessLevelOuter[0] = 5.0f;
    gl_TessLevelOuter[0] = 6.0f;
}