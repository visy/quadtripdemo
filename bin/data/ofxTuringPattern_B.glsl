uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)
uniform sampler2D tex0;          // Video
uniform sampler2D tex1;          // BufA

void main()
{
   vec2 uv = gl_FragCoord.xy / resolution.xy;

   int sample = 0;

   if (time > 1.0) sample = 1;

   gl_FragColor = vec4(texture2D(tex1, uv*vec2(1.0, 1.0)).bgr*texture2D(tex1, uv).rbg, 1.0) - vec4(texture2D(tex1, uv*vec2(1.022, 1.0 + 0.01*cos(time))).rgb*0.3*texture2D(tex0, uv).rgr, 0.2);
}

