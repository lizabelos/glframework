#version 300 es

precision mediump float;

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec3 aVertexTexCoord;

out vec3 vPosition;
out vec3 vNormal;
out vec3 vTexCoord;

uniform mat4 uMVPMatrix;


void main() {
	vPosition = aVertexPosition;
	vNormal = aVertexNormal;
	vTexCoord = aVertexTexCoord;
    gl_Position = (uMVPMatrix * vec4(vPosition, 1));
}
