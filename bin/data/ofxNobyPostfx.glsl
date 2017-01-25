uniform vec2      resolution;
uniform int       frame;
uniform sampler2D tex0;
uniform sampler2D texp;

void main()
{
	if(mod(float(frame), 2.0) < 1.0){
		if(mod(gl_FragCoord.y, 2.0) < 1.0){
			gl_FragColor = texture2D(texp, gl_TexCoord[0].st);
			return;
		}
	} else {
		if(mod(gl_FragCoord.y, 2.0) > 1.0){
			gl_FragColor = texture2D(texp, gl_TexCoord[0].st);
			return;
		}
	}
   gl_FragColor = texture2D(tex0, gl_TexCoord[0].st);
}
