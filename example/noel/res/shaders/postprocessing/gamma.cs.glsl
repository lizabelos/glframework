#version 430

layout(local_size_x = 1, local_size_y = 1) in;

layout(rgba32f, binding = 0) uniform readonly image2D uInputImage;
layout(binding = 1) uniform writeonly image2D uOutputImage;

uniform float uGammaExponent;

void main() {
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);
    vec4 pixelValue = imageLoad(uInputImage, pixelCoords);
    float exp = 1.0 / uGammaExponent;
    imageStore(uOutputImage, pixelCoords, pow(pixelValue, vec4(exp, exp, exp, exp)));
}