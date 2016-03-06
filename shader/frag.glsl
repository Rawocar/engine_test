///////////////////////////////////////////
///////////////////////////////////////////
// Fragment Shader
///////////////////////////////////////////
///////////////////////////////////////////

#version 130

///////////////////////////////////////////
///////////////////////////////////////////
// Strukturen
///////////////////////////////////////////
///////////////////////////////////////////

struct En_Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shine;
};

struct En_Light
{
	vec3 direction;
  vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	int light_kind;							// 1 Directional Light, 2 Pointing Light, 3 Spotlight
	int light_switcher;					// 0 aus, 1 an
	float constant;
	float linear;
	float quadratic;
};

///////////////////////////////////////////
///////////////////////////////////////////
// Globals
///////////////////////////////////////////
///////////////////////////////////////////

in vec2 _uv; 														// in
in vec3 _normal;												// in
in vec3 _frag;													// in

uniform vec3 camera;													// Kameraposition
uniform En_Material material;									// Material
uniform int number_lights;										// Anzahl an Lichtern insgesamt
uniform En_Light light[100];									// Lichtstruktur / maximal 100 Lichtquellen!

out vec4 color;

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsprototypen
///////////////////////////////////////////
///////////////////////////////////////////

vec4 calc_dir_light(int);
vec4 calc_plight(int);

///////////////////////////////////////////
///////////////////////////////////////////
// Hauptprogramm
///////////////////////////////////////////
///////////////////////////////////////////

void main(void)
{
	// output
	
	vec4 sum_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 ret_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if((texture(material.diffuse, _uv).a < 0.1f) || (texture(material.specular, _uv).a < 0.1f))
		{discard;}
	else
	{
		for(int i = 0 ; i < number_lights ; i++)
		{
			if(light[i].light_switcher == 1)		// Licht an?
			{
				switch(light[i].light_kind)
				{
					case 1:		// directional Light
					{
						ret_color = calc_dir_light(i);
						sum_color += ret_color;
					} break;
					case 2:		// pointing Light
					{
						ret_color = calc_plight(i);
						sum_color += ret_color;
					} break;
				};
			}
		}
	}

	color = sum_color;
}

///////////////////////////////////////////
///////////////////////////////////////////
// Funktionsdefinition
///////////////////////////////////////////
///////////////////////////////////////////

vec4 calc_dir_light(int i)
{
	// Ambient

	vec4 ambient = vec4(light[i].ambient, 1.0f) * texture(material.diffuse, _uv);

	// Diffuse

	vec3 norm = normalize(_normal);
	vec3 light_dir = normalize(-(light[i].direction));
	float diff = max(dot(norm, light_dir), 0.0f);
	vec4 diffuse = vec4(light[i].diffuse, 1.0f) * diff * texture(material.diffuse, _uv);

	// Specular

	vec3 view_dir = normalize(camera - _frag);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shine);
	vec4 specular = vec4(light[i].specular, 1.0f) * spec * texture(material.specular, _uv);

	return (ambient + diffuse + specular);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

vec4 calc_plight(int i)
{
	// Ambient

	vec4 ambient = vec4(light[i].ambient, 1.0f) * texture(material.diffuse, _uv);

	// Diffuse

	vec3 norm = normalize(_normal);
	vec3 light_dir = normalize(light[i].position - _frag);
	float diff = max(dot(norm, light_dir), 0.0f);
	vec4 diffuse = vec4(light[i].diffuse, 1.0f) * diff * texture(material.diffuse, _uv);

	// Specular

	vec3 view_dir = normalize(camera - _frag);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), material.shine);
	vec4 specular = vec4(light[i].specular, 1.0f) * spec * texture(material.specular, _uv);

	// Pointing Light

	float distance = length(light[i].position - _frag);
	float attenuation = 1.0f / (light[i].constant + light[i].linear * distance + light[i].quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}
