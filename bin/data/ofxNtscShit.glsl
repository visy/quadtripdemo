uniform vec2      resolution;
uniform float     time;
uniform sampler2D tex0;

float hash12(vec2 p){
	vec3 p3  = fract(vec3(p.xyx) * 0.1031);
	p3 += dot(p3, p3.yzx + 9.0);
	return fract((p3.x + p3.y) * p3.z);
}

float rand(vec2 x){
	vec2 f = fract(x)*fract(x)*(3.0-2.0*fract(x));
	return mix(mix(hash12(floor(x)),hash12(floor(x)+vec2(1,0)),f.x),mix(hash12(floor(x)+vec2(0,1)),hash12(floor(x)+vec2(1)),f.x),f.y);
}

vec4 ntsc(sampler2D src){
	float frameTime = time;
	vec2 uv = gl_TexCoord[0].st;
		
	float u_vhs  = pow(rand(vec2(frameTime*0.013)), 20.0);
	float u_sync = 0.5*rand(vec2(frameTime*0.05));
	
	mat3 rgbtoyuv = mat3(0.299, -0.147,  0.615, 0.587, -0.289, -0.515, 0.114, 0.436, -0.100);
	mat3 yuvtorgb = mat3(1.000, 1.000, 1.000, 0.000, -0.395, 2.032, 1.140, -0.581, 0.000);
	
	vec2 uv_q = uv;
	float syncfuck = mod(u_sync * 3.9238472, 1.0);
	float syncfuck2 = syncfuck + 0.2;
	
	uv_q.y += u_sync;
	float shade = 1.1;
	shade -= rand( vec2(uv_q.x * 0.1 + uv_q.y * 50.0 + frameTime ) ) * 0.5;
	
	vec2 uv_n = uv_q;
	vec3 yuv = vec3(0.0);
	float fix = 0.3;
	float lumadelay = -0.002;

	if (u_vhs > 0.05){
		fix = 0.5;
		fix += sin(frameTime * 5.3) * 0.12;
		fix += sin(frameTime * 9.52) * 0.05;
		fix += sin(frameTime * 30.0) * 0.05;
		fix += rand( vec2(uv_q.y*59.0+frameTime * 30.0) ) * 0.4;
		fix *= 0.5;
	}
	
	float tv = 213.7*frameTime;
	for (int xint = 10; xint >= 0; xint -= 1){
		float x = float(xint) / 10.0 ;
		float x1 = (x * -0.08) * fix + lumadelay;
		float x2 = (x *  0.06) * fix + lumadelay;

		vec3 mult = (vec3(1.0) - pow(vec3(x), vec3(0.2, 1.0, 1.0))) * 0.2;
		vec2 uv1 = uv_n + vec2(x1,0.0);
		vec2 uv2 = uv_n + vec2(x2,0.0);
		vec2 uv1b = uv_n + vec2(x1, 1.0/486.0);
		vec2 uv2b = uv_n + vec2(x2, 1.0/486.0);
		
		float vn = 0.005*pow(rand(vec2(x+tv+uv2.x*0.35343, x+tv+uv1.y*1.5235123))*0.95, 5.0);
		uv1.x += vn;
		uv2.x -= vn;
		yuv += rgbtoyuv * (texture2D(src, uv1).rgb) * mult;
		yuv += rgbtoyuv * (texture2D(src, uv2).rgb) * mult;
		yuv.r += 2.5*vn;
	}
	
	if (u_vhs > 0.0){
		float rr = pow( rand( vec2( frameTime * 0.002) ), 24.0);
		yuv.gb = mix(yuv.gb, vec2(0), rr);
		
		float na = 1.0;
		float noiseenable = max(0.0, rand( vec2( frameTime * 44.0 + uv.y * 440.0)));
		na = (0.5 + sin(uv.y * 3.0 - frameTime * 6.0) * 0.5) * noiseenable;
		yuv.g = mix(yuv.g, rand( vec2( frameTime * 9.0 + uv_n.x * 13.0 + uv_n.y * 12.0)), pow(na, 5.5));
	}
	
	return vec4(yuvtorgb * yuv * shade, 1.0);
}

void main()
{
	gl_FragColor = ntsc(tex0);
}
