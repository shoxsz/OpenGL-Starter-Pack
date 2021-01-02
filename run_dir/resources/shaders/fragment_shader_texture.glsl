#version 330 core

uniform sampler2D tex;

in vec3 fragColor;
in vec2 fragTex;

out vec4 pixelColor;

void main(){
	pixelColor = texture(tex, fragTex);
}