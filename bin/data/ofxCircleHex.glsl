uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)

uniform sampler2D tex0;          // BufB


float iGlobalTime = 0.0;

vec2 squareFrame(vec2 screenSize, vec2 coord) {
   vec2 position = 2.0 * (coord.xy / screenSize.xy) - 1.0;
   position.x *= screenSize.x / screenSize.y;
   return position;
}

const float PI = 3.14159265359;

// r^2 = x^2 + y^2
// r = sqrt(x^2 + y^2)
// r = length([x y])
// 0 = length([x y]) - r
float shape_circle(vec2 p) {
   return length(p) - 0.5;
}

vec2 opRepeat(vec2 pos, vec2 c) {
   float i = cos(iGlobalTime + pos.y)*0.5;
   float vv = cos(iGlobalTime);
   return mod(pos, c + (cos(iGlobalTime*0.2 + pos.x*iGlobalTime*0.01 + pos.y*0.1)*0.1)) - 0.5*c + vv*distance(cos(pos.y + i), shape_circle(pos))*0.3*0.3;
}

float scene(vec2 p) {
   float sum = 0.0;
   sum += shape_circle(opRepeat(p, vec2(0.1, 0.1)));
   return sum;
}

// y = sin(5x + t) / 5
// 0 = sin(5x + t) / 5 - y
float shape_sine(vec2 p) {
   return p.y - sin(p.x * 5.0 + time) * 0.2;
}


vec3 draw_line(float d, float thickness) {
   const float aa = 3.0;
   return vec3(smoothstep(0.0, aa / resolution.y, max(0.0, abs(d) - thickness)));
}

vec3 draw_line(float d) {
   return draw_line(d, 0.0025);
}

float draw_solid(float d) {
   return smoothstep(0.0, 3.0 / resolution.y, max(0.0, d));
}

vec3 draw_distance(float d, vec2 p) {
   float t = clamp(d * 0.85, 0.0, 1.0);
   vec3 grad = mix(vec3(1, 0.8, 0.5), vec3(0.3, 0.8, 1), t);

   float d0 = 0.0;
   float d1 = abs(1.0 - draw_line(mod(d + 0.025, 0.05) - 0.015).x);
   float d2 = abs(1.0 - draw_line(d).x);
   vec3 rim = vec3(max(d2 * 0.85, max(d0 * 0.15, d1 * 0.06115)));

   grad -= rim*10.0;

   grad += scene(p + d2*1. + shape_sine(p))*0.5;
   return grad;
}

vec3 draw_trace(float d, vec2 p, vec2 ro, vec2 rd) {
   vec3 col = vec3(0);
   vec3 line = vec3(1, 1, 1);
   vec2 _ro = ro;

   for (int i = 0; i < 20; i++) {
	   float t = scene(ro);
	   col += 0.8 * line * (1.0 - draw_line(length(p.xy - ro) - abs(t), 0.));
	   col += 0.2 * line * (1.0 - draw_solid(length(p.xy - ro) - abs(t) + 0.02));
	   col += line * (1.0 - draw_solid(length(p.xy - ro) - 0.015));
	   ro += rd * t;
	   if (t < 0.01) break;
   }


   return col;
}

void main() {
   iGlobalTime = time;
   float t = iGlobalTime * 0.5;
   vec2 uv = squareFrame(resolution.xy, gl_FragCoord);
   float d;
   vec3 col;
   vec2 ro = vec2(vec2(0.0) / resolution.xy) * 2.0 - 1.0;
   ro.x *= squareFrame(resolution.xy, resolution.xy).x;

   vec2 rd = normalize(-ro);

   d = scene(uv + vec2(cos(iGlobalTime*0.1), sin(iGlobalTime*0.1)));


   col = vec3(draw_distance(d*0.3 + iGlobalTime*0.01, uv.xy));
//									   col -= (iMo > 0.0 ? 1.0 : 0.0) * vec3(draw_trace(d, uv.xy, ro, rd));


   col.rgb = mix(col.rgb*1.8, texture2D(tex0, col.xy*iGlobalTime*0.001).xyz*1.3, 0.9) -
	   mix(col.rgb*0.1, texture2D(tex0, col.xy*iGlobalTime*0.002).xyz*0.2, 0.2) -
	   mix(col.rgb*0.9, texture2D(tex0, col.xy*iGlobalTime*0.002).xyz*0.2, 0.2);

   
   gl_FragColor = vec4(col.b,col.g,col.r,1.0);
}

