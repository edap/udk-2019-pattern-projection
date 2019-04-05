#version 150

uniform vec2 uMousePos;
uniform vec2 uResolution;
out vec4 outputColor;

void main(){
    vec4 finalColor;
    vec2 st = gl_FragCoord.xy / uResolution.xy;
    outputColor = vec4(st.x, st.y, 0.0, 1.0);
}
