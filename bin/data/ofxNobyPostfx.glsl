uniform vec2      resolution;
uniform int       frame;
uniform sampler2D tex0;
uniform sampler2D texp;

float hash12(vec2 p){
	vec3 p3  = fract(vec3(p.xyx) * 0.1031);
	p3 += dot(p3, p3.yzx + 9.0);
	return fract((p3.x + p3.y) * p3.z);
}

float rand(vec2 x){
	vec2 f = fract(x)*fract(x)*(3.0-2.0*fract(x));
	return mix(mix(hash12(floor(x)),hash12(floor(x)+vec2(1,0)),f.x),mix(hash12(floor(x)+vec2(0,1)),hash12(floor(x)+vec2(1)),f.x),f.y);
}

void main(){
	vec2 uv = gl_TexCoord[0].st;
	vec4 nv = 0.025*vec4(vec3(rand(uv*vec2(220.,440.)+float(frame*43))),1.0);
	if(mod(float(frame), 2.0) < 1.0){
		if(mod(gl_FragCoord.y, 2.0) < 1.0){
			gl_FragColor = texture2D(texp, uv)*0.975+nv;
			return;
		}
	} else {
		if(mod(gl_FragCoord.y, 2.0) > 1.0){
			gl_FragColor = texture2D(texp, uv)*0.975+nv;
			return;
		}
	}
	gl_FragColor = texture2D(tex0, uv)*0.975+nv;
}
