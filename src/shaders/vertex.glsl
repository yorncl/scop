#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 modelm;
uniform mat4 viewm;
uniform mat4 projm;

out vec2 TexCoord;
out vec3 FragPos;

void main() {
 gl_Position = projm * viewm * modelm * vec4(position, 1); // position sur l'ecran
 TexCoord = position.yz;
}
