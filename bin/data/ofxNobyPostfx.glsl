uniform float     time;           // shader playback time (in seconds)
uniform vec3      mouse;
uniform vec2      resolution;           // viewport resolution (in pixels)
uniform int       frame;

uniform sampler2D tex0;
uniform sampler2D texp;
/*
void main()
{
	if(mod(float(frame), 2.0) < 1.0){
		if(mod(gl_FragCoord.y, 2.0) < 1.0) discard;
	} else {
		if(mod(gl_FragCoord.y, 2.0) > 1.0) discard;
	}
   gl_FragColor = texture2D(tex0, gl_TexCoord[0].st);
}
*/

void main()
{
	if(mod(float(frame), 2.0) < 1.0){
		if(mod(gl_FragCoord.y, 2.0) < 1.0){
			texture2D(texp, gl_TexCoord[0].st);
		}
	} else {
		if(mod(gl_FragCoord.y, 2.0) > 1.0){
			texture2D(texp, gl_TexCoord[0].st);
		}
	}
   gl_FragColor = texture2D(tex0, gl_TexCoord[0].st);
}
