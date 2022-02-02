#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colorValue;
layout(location = 2) in vec3 normal;

out vec2 TexCoord;
out vec3 v_normal;
out vec3 FragPos;
out vec3 viewPos;
out vec3 lightDir;

uniform float angle;
uniform mat4 modelm;

void main() {
 const float PI_2 = 1.57079632679489661923;

 viewPos = vec3(0, -2, -5);

 mat4 view = mat4 (
 	1.0, 0.0, 0.0, 0.0, 
 	0.0, 1.0, 0.0, 0.0, 
 	0.0, 0.0, 1.0, 0.0, 
 	0.0, -2.0, -5.0, 1.0
 	);

 mat4 view2 = mat4 (
 	1.0, 0.0, 0.0, 0.0, 
 	0.0, 1.0, 0.0, 0.0, 
 	0.0, 0.0, 1.0, 0.0, 
 	0.2* cos(7*(position.y  + angle) ), -2.0, -5.0, 1.0
 	);


 mat4 rotation = mat4 (
 	cos(angle), 0.0, sin(angle), 0.0,
	0.0, 1.0, 0.0, 0.0, 
 	-sin(angle), 0.0, cos(angle), 0.0, 
 	0.0, 0.0, 0.0, 1.0
 	);

 float n = 0.1;
 float f = -100;

 float scale = tan(90 * PI_2 /180) * n;

 float r = 1 * scale;
 float l = -r;

 float t = scale;
 float b = -t;

 mat4 projection = mat4 (
 	2 * n / ( r - l ), 0.0, 0.0, 0.0, 
 	0.0, 2 * n / ( t- b), 0.0, 0.0, 
 	(r + l) / (r -l ), (t + b)/ (t-b), -(f +n)/(f -n), -1, 
 	0.0, 0.0, - 2 * f * n / (f - n ), 0.0
	);
 gl_Position = projection * view * rotation * modelm * vec4(position, 1); // position sur l'ecran
 TexCoord = position.yz;
 v_normal = vec3(rotation * modelm * vec4(normal, 1));
 FragPos = vec3(rotation * modelm * vec4(position, 1));
 lightDir = normalize(vec3(-4, 4, 0) - FragPos);
}
