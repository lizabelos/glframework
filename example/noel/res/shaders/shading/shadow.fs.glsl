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
uniform float uShadowPower;

uniform vec4 uLightPosition;
uniform vec4 uCameraPosition;

uniform float uLightShadowMapBias;
uniform float uFarPlane;

uniform mat4 uGeometryMVPMatrix;
uniform mat4 uGeometryMVMatrix;
uniform mat4 uGeometryNormalMatrix;

in vec2 vPosition;
in vec2 vTexCoord;

vec3 sampleOffsetDirections[20] = vec3[]
(
    vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1),
    vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
    vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
    vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
    vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);


out vec4 fFragColor;

float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - uLightPosition.xyz;

    float viewDistance = length(uCameraPosition.xyz - fragPos);

    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);

    float shadow = 0.0;
    int samples  = 20;
    float diskRadius = (1.0 + (viewDistance / uFarPlane)) / 25.0;

    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(uGShadow, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= uFarPlane;   // Undo mapping [0;1]
        if(currentDepth - uLightShadowMapBias > closestDepth) shadow += 1.0;
    }
    shadow /= float(samples);

    return shadow;
}


void main() {
    // Read the GBuffers
    vec2 texPosition = vTexCoord;

    vec3 positionAsIt = texture2D(uGPosition, texPosition).xyz;
    vec3 position = (uGeometryMVPMatrix * vec4(positionAsIt,1)).xyz;

    vec3 normalAsIt = texture2D(uGNormal, texPosition).xyz;
    vec3 normal = (uGeometryNormalMatrix * vec4(normalAsIt,0)).xyz;

    vec3 ambientColor = texture2D(uGAmbient, texPosition).xyz;
    vec3 diffuseColor = texture2D(uGDiffuse, texPosition).xyz;
    vec4 specularColor = texture2D(uGlossyShininess, texPosition);

    // Compute the light
    vec3 lightDirection = normalize(uLightPosition.xyz - positionAsIt);
    vec3 viewDirection = normalize(uCameraPosition.xyz - positionAsIt);
    vec3 reflectDirection = reflect(-lightDirection, normalAsIt);

    vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * diffuseColor;
    vec3 ambient = ambientColor;

    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), specularColor.a);
    vec3 specular = spec * specularColor.rgb;

    // Compute the shadow
    float shadow = 1.0 - ShadowCalculation(positionAsIt);

    // The final color
    vec3 lighting = (ambient * uAmbientPower + diffuse * uDiffusePower + specular * uSpecularPower) * (shadow / 2.0 + 0.5);
    fFragColor = vec4(shadow, shadow, shadow, 1.0);

}