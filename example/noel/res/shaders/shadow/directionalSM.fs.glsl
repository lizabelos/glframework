#version 430

in vec4 FragPos;

uniform vec4 uLightPosition;
uniform float uFarPlane;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - uLightPosition.xyz);

    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / uFarPlane;

    // write this as modified depth
    gl_FragDepth = lightDistance;
}