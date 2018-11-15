#version 330

layout(location = 3) in vec3 aVertexPosition;
layout(location = 4) in vec3 aVertexNormal;
layout(location = 5) in vec2 aVertexTexCoord;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 uMVPMatrix;


void main() {
	vPosition = aVertexPosition;
	vNormal = aVertexNormal;
	vTexCoord = aVertexTexCoord;
    gl_Position = (uMVPMatrix * vec4(vPosition, 1));
}
