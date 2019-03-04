#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec3 vTexCoord;

layout(location = 0) out vec3 fPosition;
layout(location = 1) out vec3 fNormal;
layout(location = 2) out vec3 fAmbient;
layout(location = 3) out vec3 fDiffuse;
layout(location = 4) out vec4 fGlossyShininess;

uniform samplerCube uCubemap;

void main (void) {
    fPosition = vPosition;
    fNormal = normalize(vNormal);
    fAmbient = vec3(0, 0, 0);
    fDiffuse = texture(uCubemap, vTexCoord).rgb;
    fGlossyShininess = vec4(0, 0, 0, 0);
}