#version 330 core

uniform sampler2D uGPosition;
uniform sampler2D uGNormal;
uniform sampler2D uGAmbient;
uniform sampler2D uGDiffuse;
uniform sampler2D uGlossyShininess;

uniform vec4 uLightPosition;
uniform vec4 uCameraPosition;

in vec2 vPosition;

out vec4 fFragColor;

void main() {
    vec2 texPosition = (vPosition + vec2(1.0, 1.0)) / 2.0;

    vec3 position = texture2D(uGPosition, texPosition).xyz;
    vec3 normal = texture2D(uGNormal, texPosition).xyz;
    vec3 ambientColor = texture2D(uGAmbient, texPosition).xyz;
    vec3 diffuseColor = texture2D(uGDiffuse, texPosition).xyz;
    vec4 specularColor = texture2D(uGlossyShininess, texPosition);

    vec3 lightDirection = normalize(uLightPosition.xyz - position);
    vec3 viewDirection = normalize(uCameraPosition.xyz - position);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffuseColor;
    vec3 ambient = ambientColor;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularColor.a);
    vec3 specular = 0.1 * spec * specularColor.rgb;

    // fFragColor = vec4(diffuse + ambient + specular, 1.0);
    // fFragColor = vec4(normal, 1.0);
    fFragColor = vec4(ambient, 1.0);
}