#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fFragColor;

uniform sampler2D uTexture;
uniform vec4 uLightPosition;

void main() {
    vec3 lightDirection = normalize(uLightPosition.xyz - vPosition);
    vec3 normal = normalize(vNormal);

    float diffuse = max(dot(normal, lightDirection), 0.3);

    vec4 color = texture2D(uTexture,vTexCoord);
    fFragColor = vec4(color.rgb * diffuse, color.a);
}
