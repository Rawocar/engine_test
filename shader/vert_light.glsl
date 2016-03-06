///////////////////////////////////////////
///////////////////////////////////////////
// Vertex Shader
///////////////////////////////////////////
///////////////////////////////////////////

#version 130

attribute vec3 in_vpos;						// in
attribute vec4 in_color;					// in

varying vec4 _color;			// out
uniform mat4 mvp;
uniform mat4 mlight;

void main(void)
{
	// gl_Position legt die Position für einen Vertex fest

  gl_Position = mvp * mlight * vec4(in_vpos, 1.0f);

	// übergibt die Eingabefarbe

  _color = in_color;
}
