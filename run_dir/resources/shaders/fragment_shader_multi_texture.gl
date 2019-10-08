#version 330 core

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec3 fragColor;
in vec2 fragTex;

out vec4 pixelColor;

void main(){
	pixelColor = mix(texture(texture1, fragTex), texture(texture2, fragTex), 0.5f);
}