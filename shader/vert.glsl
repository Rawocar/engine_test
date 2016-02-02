///////////////////////////////////////////
///////////////////////////////////////////
// Vertex Shader
///////////////////////////////////////////
///////////////////////////////////////////

layout (location = 0) attribute vec3 in_pos;		// in
layout (location = 1) attribute vec4 in_color;	// in
layout (location = 2) attribute vec2 in_uv;

varying vec4 out_color;					// out
varying vec2 out_uv;						// out
uniform mat4 mvp;
uniform mat4 model;

void main(void)
{
	// gl_Position legt die Position für einen Vertex fest

  gl_Position = mvp * model * vec4(in_pos, 1.0f);

	// übergibt die Eingabefarbe

  out_color = in_color;
	out_vu = in_vu;
}
