uniform float time;
uniform vec2 resolution;
/*
#define FIELD 16.0
#define ITERATION 10
#define CHANNEL bvec3(true,true,true)
#define PI4 0.7853981633974483
#define TONE vec3(0.499,0.617,0.094)
*/
vec2 wolfFaceEQ(vec3 p, float t) {
	vec2 fx = p.xy;
	p = (abs(p*2.0));
	const float j = float(10);
	vec2 ab = vec2(2.0 - p.x);
	for (float i = 0.0; i<j; i++) {
		//ab+=(p.xy)-max(-30.0, min(30.0, tan(length(p) )));
		ab += (p.xy) - max(-25.0, min(3.0, tan(length(0.25*p))));
		//p.y+=atan( 50.0+50.0*sin(ab.x-p.z) )*0.5;
		p.y += atan(ab.x - 8.0 + 8.0*sin(p.z))*0.5;
		p.x += sin(ab.y)*0.5;
		p -= (p.x + p.y);
		p += (fx.y + cos(fx.x));
		ab += 1.5*vec2(p.y) - pow(i / abs(p.x), 2.0)*0.1;
	}
	p /= 16.;
	fx.x = (p.x + p.x + p.y);
	return fx;
}

vec3 computeColor(vec2 fx) {
	vec3 color = vec3(0.499, 0.617, 0.094);
	color -= (fx.x);
	color.b += color.g*1.5;
	return clamp(color, (0.0), (1.0));
}

void main() {
	float ratio = resolution.y / resolution.x;
	gl_FragCoord.y *= ratio;
	vec2 position = (gl_FragCoord.xy / resolution.xy) - vec2(0.5, 0.5*ratio);
	vec3 p = position.xyx*16.;
	p.z = 16. + 1.5 + time*0.5;

	vec2 off = 4.5 / resolution.xy;
	p *= 0.8;
	vec2 value = vec2(0);
	value += wolfFaceEQ(p + vec3(0.0, 1.0, 0.0), time);
	value += wolfFaceEQ(p + vec3(off.x, 1.0, 0.0), time);
	value += wolfFaceEQ(p + vec3(0.0, 1.0 + off.y, 0.0), time);
	value += wolfFaceEQ(p + vec3(vec2(0, 1) + off, 0.0), time);

	value /= 4.0;
	vec3 color = computeColor(value);
	gl_FragColor = vec4(color, 1.0);
}
