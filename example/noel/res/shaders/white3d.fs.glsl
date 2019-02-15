#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

void main() {
    fFragColor = vec4(1, 1, 1, 1);
}
