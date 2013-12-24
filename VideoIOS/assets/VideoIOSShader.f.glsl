#version 100
precision highp float; 

varying vec2 f_texcoord;
uniform sampler2D luminanceTexture;
uniform sampler2D chrominanceTexture;
const mediump mat3 colorConversionMatrix = mat3(
    1.164,  1.164, 1.164,
    0.0, -0.213, 2.112,
    1.793, -0.533,   0.0
);

void main(void) {
    vec3 yuv;
    vec3 rgb;
    
    yuv.x = texture2D(luminanceTexture, f_texcoord).r;
    yuv.yz = texture2D(chrominanceTexture, f_texcoord).ra - vec2(0.5, 0.5);
    rgb = colorConversionMatrix * yuv;
    
    gl_FragColor = vec4(rgb, 1);
}

