#version 300 es

precision mediump float;

uniform sampler2D uGPosition;
uniform sampler2D uGNormal;
uniform sampler2D uGAmbient;
uniform sampler2D uGDiffuse;
uniform sampler2D uGlossyShininess;
uniform sampler2DShadow uGShadow;

uniform vec4 uLightPosition;
uniform vec4 uCameraPosition;

uniform mat4 uLightMVPMatrix;

uniform float uLightShadowMapBias;

in vec2 vPosition;
in vec2 vTexCoord;


out vec4 fFragColor;

void main() {
    vec2 texPosition = vTexCoord;

    vec3 position = texture2D(uGPosition, texPosition).xyz;
    vec3 normal = texture2D(uGNormal, texPosition).xyz;
    vec3 ambientColor = texture2D(uGAmbient, texPosition).xyz;
    vec3 diffuseColor = texture2D(uGDiffuse, texPosition).xyz;
    vec4 specularColor = texture2D(uGlossyShininess, texPosition);

    vec3 lightDirection = normalize(uLightPosition.xyz - position);
    vec3 viewDirection = normalize(uCameraPosition.xyz - position);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffuseColor;
    vec3 ambient = ambientColor * 0.3;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularColor.a);
    vec3 specular = 0.1 * spec * specularColor.rgb;

    vec4 positionInDirLightScreen = uLightMVPMatrix * vec4(position, 1); // Compute fragment position in NDC space of light
    vec3 positionInDirLightNDC = vec3(positionInDirLightScreen / positionInDirLightScreen.w) * 0.5 + 0.5; // Homogeneize + put between 0 and 1
    float dirLightVisibility = textureProj(uGShadow, vec4(positionInDirLightNDC.xy, positionInDirLightNDC.z - uLightShadowMapBias, 1.0), 0.0);

    fFragColor = vec4(dirLightVisibility, dirLightVisibility, dirLightVisibility, 1.0);
}