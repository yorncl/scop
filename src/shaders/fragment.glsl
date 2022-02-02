#version 330 core
out vec4 color;
in vec2 TexCoord;
in vec3 v_color;
in vec3 v_normal;
in vec3 FragPos;
in vec3 lightDir;

uniform sampler2D ourTexture;
uniform float red_value;

void main() {

 //color = texture(ourTexture, TexCoord);
 //color = vec4(v_color.x, v_color.y, v_color.z, 1.0);
 float diff = max(dot(v_normal, lightDir), 0.0);
 vec3 result = (0.05 + diff) * vec3(1.0, 1.0, 1.0) * 0.7;
 color = vec4(result, 1.0);
}
