#version 330

precision mediump float;

in vec2 vPosition;
in vec2 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform int uId;

void main() {
    fFragColor = vec4(uId / 255.0f, uId / 255.0f, uId / 255.0f, 1);
}
