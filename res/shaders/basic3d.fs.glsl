#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

// uniform sampler2D uTexture;

void main() {
    fFragColor = vec4(1, 1, 1, 1);
    // fFragColor = texture2D(uTexture,vTexCoord).rgb;
}
