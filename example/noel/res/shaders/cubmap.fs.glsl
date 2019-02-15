#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec3 vTexCoord;

out vec4 fFragColor;

uniform samplerCube uCubemap;

void main (void) {
    fFragColor = texture(uCubemap, vTexCoord);
}