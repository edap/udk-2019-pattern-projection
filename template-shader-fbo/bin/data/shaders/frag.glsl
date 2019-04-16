#version 150

uniform sampler2D tex0;
in vec2 vTexCoord;

uniform vec2 uMousePos;
uniform vec2 uResolution;
uniform float uTime;
out vec4 outputColor;


void main(){
    vec4 finalColor;
    // draw texture
    vec2 coord = vTexCoord;
    outputColor = texture(tex0, coord);

    // 1 swizzling
    //outputColor = outputColor.brga;

    // 2 edit single channel colors
    //outputColor.r += sin(uTime);

    // 3 sampling the texture on different coordinates.
    //coord.x += sin(uTime+gl_FragCoord.x)* 0.0001;
    //coord.y += cos(uTime+gl_FragCoord.y)* 0.0001;
    // outputColor = texture(tex0, coord);
    // 4 sum colors from different coord?
//    vec2 secondCoords = coord;
//    secondCoords.x += sin(uTime+gl_FragCoord.x)* 0.001;
//    secondCoords.y += cos(uTime+gl_FragCoord.y)* 0.1;
//    vec4 secondColor = texture(tex0, secondCoords);
//    outputColor = (outputColor+secondColor) / 2.0;

    // 5 use those edited coords to affect the colors
    //outputColor.g = abs(secondCoords.y);


}
