///////////////////////////////////////////
///////////////////////////////////////////
// Vertex Shader
///////////////////////////////////////////
///////////////////////////////////////////

#version 130

attribute vec3 in_pos;		// in
attribute vec4 in_color;	// in
attribute vec2 in_uv;

varying vec4 _color;			// out
varying vec2 _uv;					// out
uniform mat4 mvp;
uniform mat4 model;

void main(void)
{
	// gl_Position legt die Position für einen Vertex fest

  gl_Position = mvp * model * vec4(in_pos, 1.0f);

	// übergibt die Eingabefarbe

  _color = in_color;
	_uv = in_uv;
}
