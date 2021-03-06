#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 U_LightPosition;
uniform vec4 U_LightDiffuse;
uniform vec4 U_LightDiffuseMaterial;
uniform vec4 U_LightAmbient;
uniform vec4 U_LightAmbientMaterial;
uniform vec4 U_LightSpecular;
uniform vec4 U_LightSpecularMaterial;
uniform vec4 U_CameraPosition;
uniform vec4 U_LightOpt;

uniform sampler2D U_Texture;
uniform sampler2D U_TextureNormal;
in vec4 V_Color;
in vec4 V_TexCoord;
in vec4 V_Normal;
in vec4 V_WorldPosition;

void main() {
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	// compute normal
	vec3 texture_normal = texture2D(U_TextureNormal, V_TexCoord.xy).rgb;
    // convert normal range to [-1,1]
    texture_normal = normalize(texture_normal * 2.0 - 1.0);   
	vec3 n = texture_normal.xzy;
	// compute ambient color
	vec4 ambien_color  = U_LightAmbient * U_LightAmbientMaterial;
	// compute diffuse color 
	vec3 light_position = U_LightPosition.xyz;
	vec3 light_position_copy = light_position;
	light_position_copy = normalize(light_position_copy);
	//vec3 n = normalize(V_Normal.xyz);
	float diffuse_intensity = max(0.0, dot(light_position_copy, n));
	vec4 diffuse_color = U_LightDiffuse * U_LightDiffuseMaterial * diffuse_intensity;
	// compute specular color
	vec4 specular_color = vec4(0.0, 0.0, 0.0, 0.0);
	if (diffuse_intensity > 0.0) {
		vec3 refect_direction = normalize(reflect(- light_position_copy, n));
		vec3 view_direction = normalize(U_CameraPosition.xyz - V_WorldPosition.xyz);
		specular_color = U_LightSpecular * U_LightSpecularMaterial * 
			pow(max(0.0, dot(view_direction, refect_direction)), U_LightOpt.x);
			
	}
	// consider the color of texture...
	// vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
	color = ambien_color * texture2D(U_Texture, V_TexCoord.xy) + diffuse_color * texture2D(U_Texture, V_TexCoord.xy) + specular_color; 
	//vec4 color = texture2D(U_Texture, V_TexCoord.xy);
	gl_FragColor = color;
}