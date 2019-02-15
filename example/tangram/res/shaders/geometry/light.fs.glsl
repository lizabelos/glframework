#version 300 es

precision mediump float;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

layout(location = 0) out vec3 fPosition;
layout(location = 1) out vec3 fNormal;
layout(location = 2) out vec3 fAmbient;
layout(location = 3) out vec3 fDiffuse;
layout(location = 4) out vec4 fGlossyShininess;

uniform vec4 uAmbient;
uniform vec4 uDiffuse;
uniform vec4 uSpecular;
uniform float uShininess;
uniform vec4 uLightPosition;
uniform vec4 uCameraPosition;

uniform sampler2D uAmbientTexture; 
uniform sampler2D uDiffuseTexture;
uniform sampler2D uSpecularTexture;
uniform sampler2D uShininessTexture;
uniform sampler2D uNormalTexture;

uniform bool uAmbientHasTexture;
uniform bool uDiffuseHasTexture;
uniform bool uSpecularHasTexture;
uniform bool uShininessHasTexture;
uniform bool uNormalHasTexture;

uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

vec4 getDiffuseColor() {
    if (!uDiffuseHasTexture) {
        return uDiffuse;
    } else {
        return texture2D(uDiffuseTexture,vTexCoord);
    }
}

vec4 getAmbientColor() {
    if (!uAmbientHasTexture) {
        return uAmbient;
    } else {
        return texture2D(uAmbientTexture,vTexCoord);
    }
}

vec4 getSpecularColor() {
    if (!uSpecularHasTexture) {
        return uSpecular;
    } else {
        return texture2D(uSpecularTexture,vTexCoord);
    }
}

float getShininessNumber() {
    if (!uShininessHasTexture) {
        return uShininess;
    } else {
        return texture2D(uShininessTexture,vTexCoord).r;
    }
}

vec3 getNormal() {
    return normalize(vNormal);
    /*if (!uNormalHasTexture) {
        return normalize(vNormal);
    } else {
        float textureHeight = texture2D(uNormalTexture,vTexCoord).x;
        float textureHeightX = texture2D(uNormalTexture,vTexCoord + vec2(1.0 / 512.0, 0)).x;
        float textureHeightY = texture2D(uNormalTexture,vTexCoord + vec2(0, 1.0 / 512.0)).x;
        vec3 normal = normalize(vec3(textureHeight - textureHeightX, 0.5, textureHeight - textureHeightY));
        return vec3(uNormalMatrix * vec4(normalize((vec4(normal, 0.0)).xyz * normalize(vNormal)), 0.0));
    }*/
}

void main() {

    fPosition = vPosition;
    fNormal = getNormal();
    fAmbient = getAmbientColor().rgb;
    fDiffuse = getDiffuseColor().rgb;
    fGlossyShininess = vec4(getSpecularColor().rgb, getShininessNumber());

}
