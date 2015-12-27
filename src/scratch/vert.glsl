#version 100
attribute vec2 a_coord;
attribute vec3 a_colour;
varying vec4 v_colour;

void main()
{
  v_colour = vec4(a_colour, 1.0);
  gl_Position = vec4(a_coord, 0.0, 1.0);
  gl_PointSize = 1.0;
}
