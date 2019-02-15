#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uTexture;
uniform int uId;

void main() {
    float uIdF = float(uId) / 255.0f;
    fFragColor = vec4(uIdF, uIdF, uIdF, 1);
}
