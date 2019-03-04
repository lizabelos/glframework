#version 330 core

uniform sampler2D uGPosition;
uniform sampler2D uGNormal;
uniform sampler2D uGAmbient;
uniform sampler2D uGDiffuse;
uniform sampler2D uGlossyShininess;
uniform samplerCube uGShadow;

uniform float uAmbientPower;
uniform float uDiffusePower;
uniform float uSpecularPower;

uniform vec4 uLightPosition;
uniform vec4 uCameraPosition;

uniform float uLightShadowMapBias;
uniform float uFarPlane;
uniform mat4 uLightInverseMatrix;

in vec2 vPosition;
in vec2 vTexCoord;


out vec4 fFragColor;

float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - uLightPosition.xyz;
    // use the light to fragment vector to sample from the depth map
    float closestDepth = texture(uGShadow, fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= uFarPlane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
    float shadow = currentDepth -  uLightShadowMapBias > closestDepth ? 1.0 : 0.0;

    return shadow;
}


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
    vec3 ambient = ambientColor;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularColor.a);
    vec3 specular = spec * specularColor.rgb;

    // vec3 finalColor = diffuse * uDiffusePower + ambient * uAmbientPower + specular * uSpecularPower;
    // fFragColor = vec4(finalColor * dirLightVisibility, 1.0);

    // calculate shadow
   vec4 positionAsIt = uLightInverseMatrix * vec4(position, 1);

       float shadow = ShadowCalculation(positionAsIt.xyz);

    fFragColor = vec4(shadow, shadow, shadow, 1.0);





}