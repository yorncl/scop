#version 330 core

out vec4 color;

in vec2 TexCoord;
in float v_color;

uniform sampler2D ourTexture;
uniform float red_value;

void main() {
 //color = texture(ourTexture, TexCoord);
 color = vec4(v_color, v_color, v_color, 1.0);
}
