#version 330 core

layout(location = 0) in vec3 coord;
layout(location = 1) in vec3 color;

out vec3 fragColor;

void main(){
	gl_Position.xyz = coord;
	gl_Position.w = 1;
	fragColor = color;
}
