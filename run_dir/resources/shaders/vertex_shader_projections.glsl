#version 330 core

uniform mat4 transform;
uniform mat4 projection;

layout(location = 0) in vec3 coord;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 fragColor;
out vec2 fragTex;

void main(){
	gl_Position = projection * transform * vec4(coord.xyz, 1);

	fragColor = color;
	fragTex = texCoord;
}