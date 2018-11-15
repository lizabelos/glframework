#version 330

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec3 fFragColor;

// uniform sampler2D uTexture;

void main() {
    fFragColor = vec3(0, 0, 0);
    // fFragColor = texture2D(uTexture,vTexCoord).rgb;
}
