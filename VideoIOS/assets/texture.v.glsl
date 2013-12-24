#version 100
attribute vec4 coord;//posicio i coordenades de la textura
varying vec2 texcoord;
 
void main(void) {
  gl_Position = vec4(coord.xy, 1, 1);
  texcoord = coord.zw;
}