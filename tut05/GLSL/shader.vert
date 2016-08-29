#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

uniform mat4 MVP;

out vec3 colorOut;
out vec2 textureOut;
void main() {
	colorOut = vec3(1.0f, 0.0f, 1.0f);
	textureOut = texture;
	gl_Position = MVP * vec4(position, 1.0);
}
