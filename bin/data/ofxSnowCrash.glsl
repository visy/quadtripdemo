uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)

uniform float speed;
uniform float offset;

uniform sampler2D tex0;

float effutime = 0.0;

vec4 A2(vec2 fragCoord)
{
   vec2 uv = fragCoord.xy;

   uv += vec2(effutime*0.0001, sin(effutime*0.1*speed + uv.y*0.1 + cos(uv.x*0.1))*0.01);

   vec3 sound = vec3(cos(effutime)*0.01);

   uv.y += sound.y*0.1;

   uv += vec2(effutime*0.00001*cos(effutime*0.1), uv.x*0.1*cos(effutime)*effutime*speed*0.02 + uv.x*0.1);
   if (uv.x > 0.9*tan(effutime*10. + uv.y*1000000.)) uv.xy *= 0.1*effutime*0.01*cos(uv.y*10. + effutime*speed)*cos(1.0 - uv.y + uv.x + effutime*speed) + effutime*0.00001;


   vec4 co = vec4(0.0);
   co += sound.x*effutime*0.001*vec4(sound.x*1.*sin(effutime*2.1*speed), sound.y*0.1*cos(effutime*speed), sound.z, 1.0)*0.01*cos(effutime*0.01*speed);

   co *= vec4(100000.001 - effutime*0.01);
   return co*uv.x - abs(cos(co.y*0.1*effutime*0.1)*0.1);
}

vec4 A(vec2 fragCoord)
{
   vec2 uv = fragCoord.xy;

   uv += vec2(effutime*0.00001, cos(effutime*0.1 + uv.y*0.1 + cos(uv.x*0.1))*0.01);

   vec3 sound = vec3(sin(effutime)*0.01);

   uv.y += sound.y*0.1;

   uv += vec2(effutime*0.01*cos(effutime*0.1*speed), uv.x*0.1*cos(effutime*speed)*effutime*0.02 + uv.x*0.1);
   if (uv.x > 0.9*cos(effutime*10. + uv.y*1000000.)) uv.xy *= 0.1*effutime*0.01*cos(uv.y*10. + effutime)*cos(1.0 - uv.y + uv.x + effutime) + effutime*0.00001;


   vec4 co = vec4(0.0);
   co -= A2(uv) + sin(1.9 + cos(uv.x - distance(uv.y + effutime*0.01, uv.y*10.)*0.1)*resolution.x*0.1 - A2(uv) / distance(uv.x + A2(uv).r*effutime*0.001, uv.y)*effutime*1.5)*effutime*0.0004;
   co += sound.x*effutime*0.1*vec4(sound.x*1.*sin(effutime*2.1), sound.y*0.1*cos(effutime), sound.z, 1.0)*0.01*cos(effutime*0.01);

   co -= vec4(0.2);
   return co;
}


vec4 B(vec2 fragCoord)
{
   vec2 uv = fragCoord.xy;

   if (uv.x < 0.0) uv.x += 0.01*cos(uv.y*10.) - cos(1.0 - uv.y + uv.x + effutime)*effutime*speed*0.00001;
   return vec4(3000.1 - abs(distance(uv.x, uv.y*300.*cos(uv.x + mod(uv.y, 0.2))*0.5)*10.));
}

void main()
{
   effutime = (time+offset)*2.;
   vec2 uvg = vec2(cos(gl_FragCoord.x + effutime) + gl_FragCoord.x, sin(gl_FragCoord.y + effutime*10.) + gl_FragCoord.y) / resolution.xy;
   vec2 uv = gl_FragCoord.xy / resolution.xy;
   float pp = 0.05 - abs(atan(effutime*1.1 + uv.y*10. + uvg.x*1.)*cos(uv.y));
   vec2 uv3 = gl_FragCoord.xy / resolution.xy*pp;
   if (uv.x > 0.5) uv.x = 1.0 - uv.x;
   vec4 color_g = A(uvg)*uv.y*effutime*0.0001;
   vec4 color = A(uv) - color_g.g*0.5;
   color = color*0.01*cos(effutime*0.1 + color.r + uv.x*1.)*0.4*vec4(color_g.r*effutime*0.2)*B(uvg)*2.9;

   vec4 color_g3 = 0.000001*A2(uv3 - color.rb)*1.;
   vec4 color3 = A(uvg) - color_g3.g*0.94;
   color += 0.1*color3*1.1 - cos(effutime*0.1 + color3.g*0.01 + uv.x*0.)*0.04*vec4(color_g3.r*effutime*0.2)*B(uv)*10.001;

   vec2 uv2 = gl_FragCoord.xy / resolution.xy;
   if (uv2.x > 0.5) uv2.x = 1.0 - uv2.x;
   uv2 += cos(effutime*0.01)*2.;
   vec4 color_g2 = A(uvg)*uv2.x*0.01;
   vec4 color2 = A(uv2) - color_g2.g*0.4;
   color2 -= color2*50.5 + cos(effutime*0.1 + color2.r + uv2.x*1.)*0.4*vec4(color_g2.r*effutime*0.2)*B(uv2)*0.2;



   gl_FragColor = (color2*0.01 + (color2*1.*pp / (color*effutime*0.1)*0.001))*(B(uv3 + uv.x + cos(uv.y + effutime*0.2))*0.0006);
}
