#version 100
precision highp float;

varying vec2 texcoord;
uniform sampler2D tex;
 
void main(void) {
	gl_FragColor =texture2D(tex, texcoord);
}