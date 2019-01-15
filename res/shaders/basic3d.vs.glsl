#version 300 es

precision mediump float;

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec3 aVertexTexCoord;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 uMVPMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;


void main() {
	vPosition = (uModelMatrix * vec4(aVertexPosition,1)).xyz;
	vNormal = (uModelMatrix * vec4(aVertexNormal,0)).xyz;
	vTexCoord = aVertexTexCoord.xy;
    gl_Position = (uMVPMatrix * vec4(aVertexPosition, 1));
}
