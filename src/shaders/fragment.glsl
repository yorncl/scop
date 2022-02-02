#version 330 core
out vec4 color;
in vec2 TexCoord;
in vec3 v_color;
in vec3 v_normal;
in vec3 FragPos;
in vec3 lightDir;
in vec3 viewPos;

uniform sampler2D ourTexture;
uniform float red_value;

void main() {

 //color = texture(ourTexture, TexCoord);
 //color = vec4(v_color.x, v_color.y, v_color.z, 1.0);
 float diff = max(dot(v_normal, lightDir), 0.0);
 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, v_normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = 0.5 * spec *  vec3(1,1,1);  


 vec3 result = (0.25 + specular) * vec3(1, 0.0, 0.0) * 0.7;
 color = vec4(result, 1.0);
 //color = vec4(abs(v_normal), 1.0);
}
