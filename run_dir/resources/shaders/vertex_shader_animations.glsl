#version 330 core

uniform mat4 view;
uniform mat4 projection

layout(location = 0) in vec3 coord;
layout(location = 1) in vec2 uv;

out vec2 texUV;

void main(){
	gl_Position = projection * view * vec4(coord, 1.0);
	texUV = uv;
}