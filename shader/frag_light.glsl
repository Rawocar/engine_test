///////////////////////////////////////////
///////////////////////////////////////////
// Fragment Shader
///////////////////////////////////////////
///////////////////////////////////////////

#version 130

varying vec4 _color;				// in

out vec4 color;							// out

void main(void)
{
	color = vec4(_color);
}
