#version 330 core

out vec4 color;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float textCoeff;

void main() {

 color = texture(ourTexture, TexCoord) * textCoeff + 
 	(1.0 - textCoeff) *vec4((vec3(1.0, 1.0, 1.0) / 16) * (gl_PrimitiveID % 4), 1.0);
}
