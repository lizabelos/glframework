#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uRingAlplha;
uniform sampler2D uRingColor;
uniform vec4 uLightPosition;
uniform float uDiffuseMin;

void main() {
    vec3 lightDirection = normalize(uLightPosition.xyz - vPosition);
    vec3 normal = normalize(vNormal);

    float diffuse = max(dot(normal, lightDirection), uDiffuseMin);

    vec4 ringAlpha = texture2D(uRingAlplha,vTexCoord);
    vec4 ringColor = texture2D(uRingColor,vTexCoord);
    fFragColor = vec4(ringColor.rgb * diffuse, ringAlpha.a);
}
