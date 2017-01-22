uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)

uniform float peilaus;

uniform float offset1;

float lineDist(vec2 p, vec2 start, vec2 end, float width)
{
   float iGlobalTime = time;
   vec2 dir = start - end;
   float lngth = length(dir*distance(p.x*iGlobalTime*0.03, cos(iGlobalTime)*p.y*0.1));
   dir /= lngth + (cos(p.y*cos(iGlobalTime*0.1)*10. + p.x*cos(iGlobalTime*0.1)*10.)*0.4);
   vec2 proj = max(0.0, min(lngth, dot((start - p), dir))) * dir;
   return length((start - p) - proj) - (width / 2.0);
}

void main()
{
   vec2 uv = gl_FragCoord.xy / resolution.xy;
   vec2 uvo = uv;

   float iGlobalTime = time;

   float t = offset1 + iGlobalTime*0.01;

   vec4 c = vec4(0.0);
   for (float i = 0.; i < 40.; i += 10.0) {
	   uv = uvo;
	   if (uv.x < 0.5) uv.x = 1.0 - uv.x;
	   uv.x += cos(i*iGlobalTime*0.01 + t*0.1 + uv.y)*1.1;
	   uv.y *= 1.1;



	   vec2 st = vec2(0.5 + cos(i*1. + t*1.)*0.1*uv.y*1000., 0.5 + tan(i*0.1));
	   vec2 st2 = vec2(0.5 + cos(i*1. + t*2.)*0.1*uv.y*1., 0.5*cos(i*10.1 + t*0.1)*cos(iGlobalTime*0.1 + i*1.)*1.);

	   vec2 en = vec2(0.5 + sin(t*0.3 + i)*cos(t + i), 1.0*distance(cos(i*4. + t*20.*uv.x*0.01 + st.x*0.1)*sin(t), st.x*uv.y*0.0001));

	   float px = abs(cos(iGlobalTime + i)*sin(iGlobalTime*0.1)*1.1);

	   vec3 cc = vec3(lineDist(uv, st - vec2(0.0, sin(t)*1.0), en, cos(i*10. + t*10.)*.1))*0.02;
	   vec3 cc2 = px*vec3(lineDist(uv, st2 - vec2(0.0, sin(t)*1.0), en, sin(i*10. + t*10.)*.1))*0.03;
	   vec3 cc3 = vec3(lineDist(uv, st - vec2(0.0, sin(t)*1.0), en, cos(i*10. + t*10.)*.1))*0.04;
	   vec3 cc4 = px*vec3(lineDist(uv, st2 - vec2(0.0, sin(t)*1.0), en, sin(i*10. + t*10.)*.1))*0.05;

	   c -= vec4((cc + cc2 + cc3 + cc4) / ((i + 1.)*1.001)*(0.9 + iGlobalTime*0.01), 1.0);
	   if (i > 15.)
		   c += 100.*vec4((cc + cc2 + cc3 + cc4) / ((i*3. + 0.)*80.001), 1.0);

   }

   float fade = 1.0;

   if (peilaus == 1.0) {
	   if (uv.y > 0.0) fade -= (uv.y - 0.0)*2.;
   }

   gl_FragColor = clamp(c*vec4(c.g*1.5, c.b*1.3, c.r*1.9, 1.0)*fade, 0.0, 1.0);
}

