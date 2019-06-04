// Author: Davide Prati
// Title: Boolean operation intro
// Credits: https://www.shadertoy.com/view/4dfXDn

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float sdfCircle(vec2 p, float radius)
{
	return length(p) - radius;
}


float smoothMerge(float d1, float d2, float k)
{
    float h = clamp(0.5 + 0.5*(d2 - d1)/k, 0.0, 1.0);
    return mix(d2, d1, h) - k * h * (1.0-h);
}


float merge(float d1, float d2)
{
	return min(d1, d2);
}


float mergeExclude(float d1, float d2)
{
	return min(max(-d1, d2), max(-d2, d1));
}


float substract(float d1, float d2)
{
	return max(-d1, d2);
}


float intersect(float d1, float d2)
{
	return max(d1, d2);
}



void main() {
    // remap to center
    vec2 st = (2. * gl_FragCoord.xy - u_resolution.xy ) / u_resolution.y;
    
    //
    float circle1 = sdfCircle(st + vec2(.3, 0.), 0.5);
    float circle2 = sdfCircle(st - vec2(.3, 0.), 0.5);
    vec3 color = vec3(1.000,0.621,0.505);
    
    // subtraction
    //float operationResult = substract(circle1, circle2);
    
    // merge
    float operationResult = merge(circle1, circle2);
    
    // smooth merge
    //float operationResult = smoothMerge(circle1, circle2, 0.1);
    
    // merge exclude
    //float operationResult = mergeExclude(circle1, circle2);
    
    // intersect
    //float operationResult = intersect(circle1, circle2);
    
    
    // smooth the distance field
	//operationResult = smoothstep(0.1, 0.2, operationResult);
    gl_FragColor = vec4(color * operationResult, 1.0);
}