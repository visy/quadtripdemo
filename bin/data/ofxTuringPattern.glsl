uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)
uniform sampler2D tex0;          // BufB

float hash(float c) { return fract(sin(dot(c, 12.9898))*43758.5453); }
float rand(vec2 co) {
   return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

// linear white point
const float W = 10.0;
const float T2 = 1.25; // old: 0.75

float filmic_reinhard_curve(float x) {
   float q = (T2*T2 + 1.0)*x*x;
   return q / (q + x + T2*T2);
}

vec3 filmic_reinhard(vec3 x) {
   float w = filmic_reinhard_curve(W);
   return vec3(
	   filmic_reinhard_curve(x.r),
	   filmic_reinhard_curve(x.g),
	   filmic_reinhard_curve(x.b)) / w;
}

const int N = 12;

vec2 co(vec2 uv) {
   return 0.5 - uv*0.5;
}

vec3 ca(sampler2D t, vec2 UV, vec4 sample) {
   vec2 uv = 1.0 - 2.0 * UV;
   vec3 c = vec3(0);
   float rf = 1.0;
   float gf = 1.0;
   float bf = 1.0;
   float f = 1.0 / float(N);
   for (int i = 0; i < N; ++i) {
	   c.r += f*texture2D(t, co(uv*rf)).r;
	   c.g += f*texture2D(t, co(uv*gf)).g;
	   c.b += f*texture2D(t, co(uv*bf)).b;
	   rf *= 0.9972;
	   gf *= 0.998;
	   bf *= 0.9988;
	   //c = clamp(c, 0.0, 1.0);
   }
   return c;
}

void main()
{
   const float brightness = 1.5;

   vec2 pp = gl_FragCoord.xy / resolution.xy;
   vec2 r = resolution.xy;
   vec2 p = 1. - 2.*gl_FragCoord.xy / r.xy;
   p.y *= r.y / r.x;

   // a little chromatic aberration
   vec4 sample = texture2D(tex0, pp);
   vec3 color = ca(tex0, pp, sample).rgb*vec3(1.6, 1.5, 1.4);

   //vec3 color = sample.rgb;

   // final output
   color = pow(color, vec3(1.0 / 2.2));
   //float vignette = 1.25 / (1.1 + 1.1*dot(p, p));
   float noise = .02*vec3(hash(length(p)*time)).x;
   color = filmic_reinhard(brightness*color);
   gl_FragColor = vec4(clamp(color + noise, 0.0, 1.0), 1.0);
}
