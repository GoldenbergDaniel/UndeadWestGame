// @Vertex ///////////////////////////////////////////////////////////////////////////////
#version 410 core \n

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_tex_coord;

out vec4 color;
out vec2 tex_coord;

uniform mat3 u_xform;

void main()
{
  gl_Position = vec4(a_pos * u_xform, 1.0);
  color = a_color;
  tex_coord = a_tex_coord;
}

// @Fragment /////////////////////////////////////////////////////////////////////////////
#version 410 core \n

in vec4 color;
in vec2 tex_coord;

layout (location = 0) out vec4 frag_color;

uniform vec4 u_color = vec4(0);
uniform sampler2D u_tex;

void main()
{
  vec4 tex_color = texture(u_tex, tex_coord) * (u_color + color);
  frag_color = tex_color;
}
