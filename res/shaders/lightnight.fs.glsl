#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uTexture;
uniform sampler2D uNightTexture;
uniform vec4 uLightPosition;
uniform float uDiffuseMin;

void main() {
    vec3 lightDirection = normalize(uLightPosition.xyz - vPosition);
    vec3 normal = normalize(vNormal);

    float diffuse = max(dot(normal, lightDirection), uDiffuseMin);

    vec4 colorDay = texture2D(uTexture,vTexCoord);
    vec4 colorNight = texture2D(uNightTexture,vTexCoord);
    fFragColor = vec4(colorDay.rgb * diffuse + colorNight.rgb * (1.0 - diffuse), colorDay.a);
}
