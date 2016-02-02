///////////////////////////////////////////
///////////////////////////////////////////
// Fragment Shader
///////////////////////////////////////////
///////////////////////////////////////////

layout (location = 1) varying vec4 in_color;				// in
layout (location = 2) varying vec2 in_uv; 					// in

uniform sampler2D tex;
out vec3 out_color;

void main(void)
{
  gl_FragColor = vec4(in_color);
	out_color = texture(tex, in_uv);
}
