#version 120

varying vec4 v_color;
uniform float u_alpha;

void main()
{
   gl_FragColor = v_color;
}