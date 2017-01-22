uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)

uniform sampler2D tex0;

float iGlobalTime = 0.0;

const mat3 Ai = mat3(
   1.0, 0.0, 1.402,
   1.0, -0.34414, -0.71414,
   1.0, 1.772, 0.0
);

vec3 pastelizer(float h) {
   h = fract(h + 0.3018004736777463) * 6.2831853071796;
   float s = 0.5;
   float y = 0.5;
   float r = 0.5620378938567432 * y * s;
   vec3 yc = vec3(y, r * vec2(cos(h), sin(h))) * Ai;
   return clamp(yc * yc, 0.0, 1.0);
}

void main()
{
   iGlobalTime = cos(time)*18.;
   vec2 U = gl_FragCoord.xy / resolution.xy*1000.1;
   vec4 O = vec4(0.0);
   vec4 fb = texture2D(tex0, U);
   vec4 fb2 = texture2D(tex0, U*vec2(cos(iGlobalTime*0.01), tan(-iGlobalTime*0.01)));
   U += fb.xy*0.1*vec2(cos(U.y*0.01 + fb.z*0.1)*fb.y - fb.x);
   U.x += iGlobalTime*100.;
   O += (cos(U.y + fb.r*0.01 + iGlobalTime*0.001)*0.1 + cos(iGlobalTime*0.05)*0.2) / fract(tan(iGlobalTime*0.1 + length(ceil(U /= (14. - iGlobalTime*0.01 + fb.g*0.01)))) < 0. ? fb.r - U.x + iGlobalTime*0.01 : U.y + tan(iGlobalTime*0.2)) - O - fb*0.0001;
   O += vec4(pastelizer(fb.r - fb.g + U.y)*cos(U.x + fb.z), 0.0);
   O -= fb2*O.r;

   gl_FragColor = O;
}
