#version 300 es

precision mediump float;

layout(location = 0) in vec2 aPosition;

out vec2 vPosition;

void main()
{
    vPosition = aPosition.xy;
    gl_Position =  vec4(aPosition, 0, 1);
}