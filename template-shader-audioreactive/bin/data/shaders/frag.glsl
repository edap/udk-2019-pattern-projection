#version 150

uniform vec2 uMousePos;
uniform vec2 uResolution;
uniform float uTime;

uniform float uLowBand;
uniform float uMiddleBand;
uniform float uHighBand;

out vec4 outputColor;


float sdCircle( vec2 p, float r ){
    return length(p) - r;
}

void main(){
    vec3 color = vec3(0.);
    vec3 colorLow = vec3(1.,0.0, 0.0);
    vec3 colorMiddle = vec3(0.,1.0, 0.0);
    vec3 colorHigh = vec3(0.,0.0, 1.0);

    vec2 st = gl_FragCoord.xy / uResolution.xy;
    // remap to the center
    st *= vec2(2.,2.0);
    st -= vec2(1.0, 1.0);
    // keep the ratio
    st.x *= uResolution.x/uResolution.y;


    float circleLow = smoothstep(0.1,0.098,sdCircle(st, uLowBand));

    float circleMiddle = smoothstep(0.1,0.098,sdCircle(st-vec2(0.3,0.3), uMiddleBand));

    float circleHigh = smoothstep(0.1,0.098,sdCircle(st+vec2(0.3, 0.3), uHighBand));

    // use sdf to create the colors
    colorLow *= circleLow;
    colorMiddle *= circleMiddle;
    colorHigh *= circleHigh;

    // add the 3 circles together
    color = colorLow + colorMiddle + colorHigh;
    outputColor = vec4(color, 1.0);
}
