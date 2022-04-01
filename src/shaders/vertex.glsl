#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colorValue;
layout(location = 2) in vec3 normal;

uniform float angle;
uniform mat4 modelm;
uniform mat4 viewm;
uniform mat4 projm;

out vec2 TexCoord;
out vec3 v_normal;
out vec3 FragPos;


void main() {
 const float PI_2 = 1.57079632679489661923;


 mat4 rotation = mat4 (
 	cos(angle), 0.0, sin(angle), 0.0,
	0.0, 1.0, 0.0, 0.0, 
 	-sin(angle), 0.0, cos(angle), 0.0, 
 	0.0, 0.0, 0.0, 1.0
 	);

 gl_Position = projm * viewm * rotation * modelm * vec4(position, 1); // position sur l'ecran
 TexCoord = position.yz;
 v_normal = vec3(rotation * modelm * vec4(normal, 1));
 FragPos = vec3(rotation * modelm * vec4(position, 1));
}
