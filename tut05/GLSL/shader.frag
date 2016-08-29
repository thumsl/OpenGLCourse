#version 330

in vec3 colorOut;
in vec2 textureOut;

out vec4 fragColor;

uniform sampler2D sampler;

void main() {
    fragColor = texture2D(sampler, textureOut);
}
