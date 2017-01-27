uniform vec2      resolution;
uniform sampler2D tex0;

float sat( float t ) {
	return clamp( t, 0.0, 1.0 );
}
vec2 sat( vec2 t ) {
	return clamp( t, 0.0, 1.0 );
}
float remap  ( float t, float a, float b ) {
	return sat( (t - a) / (b - a) );
}
float linterp( float t ) {
	return sat( 1.0 - abs( 2.0*t - 1.0 ) );
}

vec3 spectrum_offset( float t ) {
	vec3 ret;
	float lo = step(t,0.5);
	float hi = 1.0-lo;
	float w = linterp( remap( t, 1.0/6.0, 5.0/6.0 ) );
	float neg_w = 1.0-w;
	ret = vec3(lo,1.0,hi) * vec3(neg_w, w, neg_w);
	return pow( ret, vec3(1.0/2.2) );
}

vec2 co(vec2 uv)
{
	// return sampler-compatible uv coords
    uv = -uv; // Remove this if image is upside down (tends to happen with video)
	return 0.5-uv*0.5;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec2 uv = -1.0+2.0*gl_TexCoord[0].st;
    vec4 sum = texture2D(tex0, co(uv));
    vec4 og = sum;
    const float amount = 4.0;
    for(float i = 0.0; i < amount; i++){
        //uv /= 1.005;
        sum = clamp(sum, 0.15, 1.0);
        sum /= 0.1+0.9*clamp(texture2D(tex0, co(uv)+vec2(i/resolution.x,i/resolution.y)),0.0,2.0);
    	sum *= 0.1+0.9*clamp(texture2D(tex0, co(uv)+vec2(i/resolution.x,-i/resolution.y)),0.0,2.0);
    	sum *= 0.1+0.9*clamp(texture2D(tex0, co(uv)+vec2(-i/resolution.x,i/resolution.y)),0.0,2.0);
    	sum /= 0.1+0.9*clamp(texture2D(tex0, co(uv)+vec2(-i/resolution.x,-i/resolution.y)),0.0,2.0);
        sum.xyz /= 1.01-0.01*spectrum_offset( 1.0-length(sum.xyz) );
    	sum.xyz *= 0.99+0.01*spectrum_offset( length(sum.xyz) );
    }
    sum = 0.1+0.9*sum;
    sum /= length(sum);
    sum = (-0.2+2.0*sum)*0.9;
	gl_FragColor = mix(og, sum, 0.14);
	
}
