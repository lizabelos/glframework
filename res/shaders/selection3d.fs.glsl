#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uTexture;
uniform int uId;

void main() {
    fFragColor = vec4(uId / 255.0f, uId / 255.0f, uId / 255.0f, 1);
}
