#version 300 es

precision mediump float;

layout(location = 0) out float fragmentDepth;

void main()
{
    fragmentDepth = gl_FragCoord.z;
}