///////////////////////////////////////////
///////////////////////////////////////////
// Vertex Shader
///////////////////////////////////////////
///////////////////////////////////////////

#version 130

in vec3 in_vpos;						// in
in vec2 in_uv;							// in
in vec3 in_normal;					// in

out vec2 _uv;											// out	Texturkoordinaten
out vec3 _normal;									// out	Normalenvektor
out vec3 _frag;										// out	Fragmentposition

uniform mat4 mvp;
uniform mat4 model;

void main(void)
{
	// gl_Position legt die Position für einen Vertex fest

  gl_Position = mvp * model * vec4(in_vpos, 1.0f);

	// übergibt die Texturkoordinaten

	_uv = in_uv;
	_normal = mat3(transpose(inverse(model))) * in_normal;
	_frag = vec3(model * vec4(in_vpos, 1.0f));
}
