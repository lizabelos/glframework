#version 300 es

precision mediump float;

in vec2 vPosition;
in vec2 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform vec4 uColor;

void main() {
    fFragColor = uColor;
}
