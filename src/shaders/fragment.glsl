#version 330 core
out vec4 color;
in vec2 TexCoord;
in vec3 v_color;
in vec3 v_normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform float textCoeff;

void main() {

 color = texture(ourTexture, TexCoord) * textCoeff +  (1.0 - textCoeff) * vec4(abs(v_normal), 1.0);
}
