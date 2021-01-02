#version 330 core

layout(location = 0) in vec3 coord;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTex;

void main(){
	gl_Position.xyz = coord;
	gl_Position.w = 1;

	fragColor = color;
	fragTex = texCoord;
}