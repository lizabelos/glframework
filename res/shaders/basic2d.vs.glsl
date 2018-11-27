#version 330

precision mediump float;

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec3 aVertexTexCoord;

out vec2 vPosition;
out vec2 vNormal;
out vec2 vTexCoord;

uniform mat4 uMVPMatrix;


void main() {
	vPosition = aVertexPosition.xy;
	vNormal = aVertexNormal.xy;
	vTexCoord = aVertexTexCoord.xy;
    gl_Position = vec4(mat3(uMVPMatrix) * vec3(vPosition, 1), 1);
}