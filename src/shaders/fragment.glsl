#version 330 core

out vec4 color;

in vec2 TexCoord;
in vec3 v_color;

uniform sampler2D ourTexture;
uniform float red_value;

void main() {
 //color = texture(ourTexture, TexCoord);
 color = vec4(v_color.x, v_color.y, v_color.z, 1.0);
}
